/******************************************************************************************************************************************/
// File : Model.cpp
// Purpose : Implementing the Model renderer
/******************************************************************************************************************************************/
#include "Model.hpp"

namespace Renderers {
    Model::Model(std::vector<std::unique_ptr<Mesh>> meshes)
    {
        for (std::vector<std::unique_ptr<Mesh>>::iterator it = meshes.begin(); it != meshes.end(); ++it)
        {
            if (it[0])
            {
                m_meshes.push_back(std::move(it[0]));
            }
        }
    }

    Model::~Model()
    {
    }
    void Model::Construct()
    {
        this->Load();
        this->Attach();

        for (std::vector<std::unique_ptr<Mesh>>::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
        {
            if (it[0])
            {
                it[0]->Construct();
            }
        }
    }
    void Model::Clean()
    {
        base::Clean();

        for (std::vector<std::unique_ptr<Mesh>>::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
        {
            if (it[0])
            {
                it[0]->Clean();
                it->reset();
            }
        }

        m_meshes.clear();
    }

    void Model::Draw(size_t index)
    {
        if (index >= 0 && index < m_meshes.size() && m_meshes[index])
        {
            m_meshes[index]->Draw();
        }
    }

    void Model::Draw(size_t index, std::vector<unsigned int> light_textures_ids)
    {
        if (index >= 0 && index < m_meshes.size() && m_meshes[index])
        {
            m_meshes[index]->Draw(light_textures_ids);
        }
    }

    std::vector<Texturate> Model::GetMeshTextures(size_t index) const
    {
        if (index >= 0 && index < m_meshes.size())
        {
            return m_meshes[index]->GetMeshTextures();
        }

        return std::vector<Texturate>();
    }

    size_t Model::GetNbMeshes() const
    {
        return m_meshes.size();
    }


    void Model::Attach()
    {

    }
    void Model::Load()
    {
        
    }
}