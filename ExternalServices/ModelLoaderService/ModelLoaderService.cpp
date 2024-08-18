/******************************************************************************************************************************************/
// File : ModelLoaderService.cpp
// Purpose : Implementing shader loader service
/******************************************************************************************************************************************/
#include "ModelLoaderService.hpp"

namespace Services
{
	void ModelLoaderService::Init()
	{
        IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
        if (container)
        {
            m_texture_loader_service = container->GetReference<Services::TextureLoaderService>();
            if (!m_texture_loader_service)
            {
                SQ_APP_ERROR("Class {} in function {} : Texture loader service is not referenced yet", __FILE__, __FUNCTION__);
            }
        }
	}

	void ModelLoaderService::DeInit()
	{
        if (m_directory.size() > 0)
        {
            m_directory.clear();
        }
        if (m_textures_loaded.size() > 0)
        {
            m_textures_loaded.clear();
        }
	}

	ModelLoaderService::ModelLoaderService()
	{

	}

	ModelLoaderService::~ModelLoaderService()
	{

	}

    std::unique_ptr<Renderers::Model> ModelLoaderService::LoadModel(std::string const model_name)
	{
		std::string complete_path = Constants::MODELSPATH + model_name;
        std::unique_ptr<Renderers::Model> model = nullptr;

		std::ifstream file(complete_path.c_str());
		if (!file.is_open())
		{
			SQ_EXTSERVICE_ERROR("Class {} in function {} : Unable to open file for model : {} | FILE DOES NOT EXIST", __FILE__, __FUNCTION__, model_name);
		}
		else
		{
			file.close();

			Assimp::Importer import;
			const aiScene * scene = import.ReadFile(complete_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

            if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            {
                SQ_EXTSERVICE_ERROR("Class {} in function {} : Unable import model : {} |  IMPORTER ERROR : {}", __FILE__, __FUNCTION__, model_name, import.GetErrorString());
            }
            else
            {
                m_directory = complete_path.substr(0, complete_path.find_last_of('/'));

                this->ProcessNode(scene->mRootNode, scene);

                model = std::make_unique<Renderers::Model>(move(m_meshes));

                if (m_directory.size() > 0)
                {
                    m_directory.clear();
                }
                if (m_textures_loaded.size() > 0)
                {
                    m_textures_loaded.clear();
                }
            }
		}
		
        return model;
	}

	void ModelLoaderService::ProcessNode(aiNode* node, const aiScene* scene)
	{
		if ((node != nullptr) && (scene != nullptr))
		{
			for (unsigned int i = 0; i < node->mNumMeshes; i++)
			{

				if (node->mMeshes != nullptr)
				{
					aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
                    Renderers::Mesh tmp = this->ProcessMesh(mesh, scene);
					m_meshes.push_back(std::make_unique<Renderers::Mesh>(std::move(tmp)));
				}

			}

			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				this->ProcessNode(node->mChildren[i], scene);
			}

            
		}
	}
	Renderers::Mesh ModelLoaderService::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
        if ((mesh != nullptr) && (scene != nullptr))
        {

            std::vector<Renderers::Vertex> vertices;
            std::vector<unsigned int> indices;
            std::vector<Renderers::Texturate> textures;

            for (unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                Renderers::Vertex vertex;
                glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
                // positions
                vector.x = mesh->mVertices[i].x;
                vector.y = mesh->mVertices[i].y;
                vector.z = mesh->mVertices[i].z;
                vertex.position = vector;
                // normals

                if (mesh->HasNormals())
                {
                    vector.x = mesh->mNormals[i].x;
                    vector.y = mesh->mNormals[i].y;
                    vector.z = mesh->mNormals[i].z;
                    vertex.normal = vector;

                }


                // texture coordinates
                if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
                {

                    glm::vec2 vec;
                    // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                    // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                    vec.x = mesh->mTextureCoords[0][i].x;
                    vec.y = mesh->mTextureCoords[0][i].y;
                    vertex.texture_coords = vec;

                    // tangent
                    vector.x = mesh->mTangents[i].x;
                    vector.y = mesh->mTangents[i].y;
                    vector.z = mesh->mTangents[i].z;
                    vertex.tangent = vector;

                    // bitangent
                    vector.x = mesh->mBitangents[i].x;
                    vector.y = mesh->mBitangents[i].y;
                    vector.z = mesh->mBitangents[i].z;
                    vertex.bitangent = vector;
                }
                else
                {

                    vertex.texture_coords = glm::vec2(0.0f, 0.0f);
                }


                vertices.push_back(vertex);
            }

            for (unsigned int i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];
                // retrieve all indices of the face and store them in the indices vector
                for (unsigned int j = 0; j < face.mNumIndices; j++)
                {
                    indices.push_back(face.mIndices[j]);
                }

            }
            

            // process materials
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            // 1. diffuse maps
            std::vector<Renderers::Texturate> diffuseMaps = this->LoadModelMaterial(material, aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

            // 2. specular maps
            std::vector<Renderers::Texturate> specularMaps = this->LoadModelMaterial(material, aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

            // 3. normal maps
            std::vector<Renderers::Texturate> normalMaps = this->LoadModelMaterial(material, aiTextureType_HEIGHT, "texture_normal");
            textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

            // 4. height maps
            std::vector<Renderers::Texturate> heightMaps = this->LoadModelMaterial(material, aiTextureType_AMBIENT, "texture_height");
            textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

            // return a mesh object created from the extracted mesh data
            Renderers::Mesh new_mesh(vertices, indices, textures);

            vertices.clear();
            indices.clear();
            textures.clear();
            return new_mesh;
        }
		return Renderers::Mesh();
	}
    std::vector<Renderers::Texturate> ModelLoaderService::LoadModelMaterial(aiMaterial* mat, aiTextureType type, std::string typeName)
    {
        std::vector<Renderers::Texturate> textures;

        if (mat != nullptr && m_texture_loader_service)
        {

            for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
            {
                aiString str;
                mat->GetTexture(type, i, &str);

                GLboolean skip = false;

                for (unsigned int j = 0; j < m_textures_loaded.size(); j++)
                {
                    if (std::strcmp(m_textures_loaded[j].path.data(), str.C_Str()) == 0)
                    {

                        textures.push_back(m_textures_loaded[j]);
                        skip = true;
                        break;
                    }
                }

                if (!skip)
                {
                    Renderers::Texturate texture;
                    texture.id = m_texture_loader_service->BuildTexture(str.C_Str(), this->m_directory);
                    texture.type = typeName;
                    texture.path = str.C_Str();
                    textures.push_back(texture);
                    m_textures_loaded.push_back(texture);
                }

            }
        }

        return textures;
    }
}

