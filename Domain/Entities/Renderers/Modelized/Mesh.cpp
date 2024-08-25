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

        m_bytes_indices_size = 0;
        m_bytes_vertices_size = 0;

    }

    Mesh::Mesh()
    {
        m_vbo = 0;
        m_vao = 0;
        m_ebo = 0;

        m_bytes_indices_size = 0;
        m_bytes_vertices_size = 0;
    }

    Mesh::Mesh(Mesh& other)
    {
        m_vbo = other.m_vbo;
        m_vao = other.m_vao;
        m_ebo = other.m_ebo;

        for (std::vector<Vertex>::iterator it = other.m_mesh_vertices.begin(); it != other.m_mesh_vertices.end(); ++it)
        {
            m_mesh_vertices.push_back(it[0]);
        }

        for (std::vector<unsigned int>::iterator it = other.m_indices.begin(); it != other.m_indices.end(); ++it)
        {
            m_indices.push_back(it[0]);
        }

        for (std::vector<Texturate>::iterator it = other.m_mesh_textures.begin(); it != other.m_mesh_textures.end(); ++it)
        {
            m_mesh_textures.push_back(it[0]);
        }

        m_bytes_indices_size = other.m_bytes_indices_size;
        m_bytes_vertices_size = other.m_bytes_vertices_size;
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
            for (std::vector<Texturate>::iterator it = m_mesh_textures.begin(); it != m_mesh_textures.end(); ++it)
            {
                if (it[0].id != 0)
                {
                    glDeleteTextures(1, &it[0].id);
                }
            }
            this->m_mesh_textures.clear();
        }
    }

    void Mesh::Draw()
    {
        for (unsigned int i(0); i < m_mesh_textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, m_mesh_textures[i].id);
        }

        if (m_vao != 0)
        {
            glBindVertexArray(m_vao);
            if (glIsVertexArray(m_vao) == GL_TRUE)
            {
                glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);

                glBindVertexArray(0);
            }
        }

        for (unsigned int i(0); i < m_mesh_textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, 0);

        }
    }

    void Mesh::Draw(std::vector<unsigned int> light_textures_ids)
    {
        for (size_t i = 0; i < light_textures_ids.size(); i++)
        {
            if (light_textures_ids[i] != 0)
            {
                glActiveTexture(GL_TEXTURE2 + (GLenum)i);
                glBindTexture(GL_TEXTURE_2D, light_textures_ids[i]);
            }
        }

        this->Draw();

        for (size_t i = 0; i < light_textures_ids.size(); i++)
        {
            if (light_textures_ids[i] != 0)
            {
                glActiveTexture(GL_TEXTURE2 + (GLenum)i);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }
    }

    std::vector<Texturate> Mesh::GetMeshTextures() const
    {
        return m_mesh_textures;
    }
   

    void Mesh::Attach()
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

        if (m_vbo != 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            if (glIsBuffer(m_vbo) == GL_TRUE)
            {
                glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size, 0, GL_STATIC_DRAW);

                glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, m_mesh_vertices.data());

                glBindBuffer(GL_ARRAY_BUFFER, 0);

            }
        }

        if (m_ebo != 0)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
            if (glIsBuffer(m_ebo) == GL_TRUE)
            {
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_bytes_indices_size, 0, GL_STATIC_DRAW);
                glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_bytes_indices_size, m_indices.data());
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }
        }

        if (m_vao != 0)
        {
            glBindVertexArray(m_vao);

            if (glIsVertexArray(m_vao) == GL_TRUE)
            {
                if (m_vbo != 0)
                {
                    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                    if (glIsBuffer(m_vbo) == GL_TRUE)
                    {

                        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
                        if (glIsBuffer(m_ebo) == GL_TRUE)
                        {
                            glEnableVertexAttribArray(0);
                            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

                            glEnableVertexAttribArray(1);
                            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

                            // vertex texture coords
                            glEnableVertexAttribArray(2);
                            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture_coords));

                            glEnableVertexAttribArray(3);
                            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

                            glEnableVertexAttribArray(4);
                            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

                            // ids
                            glEnableVertexAttribArray(5);
                            glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_bone_ids));

                            // weights
                            glEnableVertexAttribArray(6);
                            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_weights));
                        }

                        glBindBuffer(GL_ARRAY_BUFFER, 0);
                    }
                }

                glBindVertexArray(0);
            }
        }
        
    }
    void Mesh::Load()
    {
        m_bytes_indices_size = (unsigned int)(m_indices.size() * sizeof(unsigned int));
        m_bytes_vertices_size = m_mesh_vertices.size() * sizeof(Vertex);
    }
}