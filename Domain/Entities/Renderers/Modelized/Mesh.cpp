/******************************************************************************************************************************************/
// File : Mesh.cpp
// Purpose : Implementing the Mesh renderer
/******************************************************************************************************************************************/
#include "Mesh.hpp"

namespace Renderers {
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texturate> textures)
    {
        m_vbo = 0;
        m_vao = 0;
        m_ebo = 0;

        for (std::vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); ++it)
        {
            m_mesh_vertices.push_back(it[0]);
        }

        for (std::vector<unsigned int>::iterator it = indices.begin(); it != indices.end(); ++it)
        {
            m_indices.push_back(it[0]);
        }

        for (std::vector<Texturate>::iterator it = textures.begin(); it != textures.end(); ++it)
        {
            m_mesh_textures.push_back(it[0]);
        }

    }

    Mesh::Mesh()
    {
        m_vbo = 0;
        m_vao = 0;
        m_ebo = 0;
    }

    Mesh::~Mesh()
    {
    }
    void Mesh::Construct()
    {
        this->Load();
        this->Attach();
    }
    void Mesh::Clean()
    {
        base::Clean();

        if (m_mesh_vertices.size() > 0)
        {
            this->m_mesh_vertices.clear();
        }

        if (m_mesh_textures.size() > 0)
        {
            this->m_mesh_textures.clear();
        }
    }
   

    void Mesh::Attach()
    {

        if (m_mesh_vertices.size() > 0 && m_indices.size() > 0 && m_mesh_textures.size() > 0)
        {
            if (m_vbo == 0)
            {
                glGenBuffers(1, &m_vbo);
            }

            if (m_vao == 0)
            {
                glGenVertexArrays(1, &m_vao);
            }

            if (m_ebo == 0)
            {
                glGenBuffers(1, &m_ebo);
            }
        }
        
    }
    void Mesh::Load()
    {
        
    }
}