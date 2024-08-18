/******************************************************************************************************************************************/
// File : ModelLoaderService.hpp
// Purpose : A service loading 3D model files
/******************************************************************************************************************************************/
#ifndef MODELLOADERSERVICE_H
#define MODELLOADERSERVICE_H

#include "IService.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Constants/StringConstants.hpp"

#include "Renderers/Modelized/Mesh.hpp"
#include "Renderers/Modelized/Model.hpp"
#include "../TextureLoaderService/TextureLoaderService.hpp"
#include "Container/Container.hpp"



#include "Logger.hpp"

namespace Services {

	class ModelLoaderService : public IService
	{
	public:
		void Init() override;
		void DeInit() override;

		ModelLoaderService();

		~ModelLoaderService();

		std::unique_ptr<Renderers::Model> LoadModel(std::string const name);

		

	private:

		void ProcessNode(aiNode* node, const aiScene* scene);
		Renderers::Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Renderers::Texturate> LoadModelMaterial(aiMaterial* mat, aiTextureType type, std::string typeName);


		std::vector<std::unique_ptr<Renderers::Mesh>> m_meshes;
		std::vector<Renderers::Texturate>          m_textures_loaded;
		std::string                     m_directory;

		std::shared_ptr<TextureLoaderService> m_texture_loader_service;

	};
}

#endif