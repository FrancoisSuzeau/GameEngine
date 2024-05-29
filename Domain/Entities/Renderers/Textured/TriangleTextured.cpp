/******************************************************************************************************************************************/
// File : TriangleTextured.cpp
// Purpose : Implementing the TriangleTextured renderer
/******************************************************************************************************************************************/
#include "TriangleTextured.hpp"

namespace Renderers {
    TriangleTextured::TriangleTextured()
    {
        m_vbo = 0;
        m_vao = 0;
        m_bytes_vertices_size = 0;
        m_bytes_indices_size = 0;
        m_bytes_textcoord_size = 0;
        m_bytes_normals_size = 0;
    }
    TriangleTextured::~TriangleTextured()
    {
    }
    void TriangleTextured::Construct()
    {
        this->Load();
        this->Attach();
    }
    void TriangleTextured::Clean()
    {
        base::Clean();

    }
    void TriangleTextured::Draw(unsigned int const texture_id)
    {
        if (m_vao != 0)
        {
            glBindVertexArray(m_vao);
            if (glIsVertexArray(m_vao) == GL_TRUE)
            {
                if (texture_id != 0)
                {
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, texture_id);
                    if (glIsTexture(texture_id) == GL_TRUE)
                    {
                        glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);

                        glBindTexture(GL_TEXTURE_2D, 0);
                    }
                }
                else
                {
                    glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);
                }

                glBindVertexArray(0);
            }
        }
    }

    void TriangleTextured::Draw(unsigned int const texture_id, unsigned int const light_src_texture_id)
    {
        if (light_src_texture_id != 0)
        {
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, light_src_texture_id);
        }

        this->Draw(texture_id);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void TriangleTextured::Attach()
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
                glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size + m_bytes_normals_size + m_bytes_textcoord_size, 0, GL_STATIC_DRAW);

                glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, m_vertices.data());
                glBufferSubData(GL_ARRAY_BUFFER, m_bytes_vertices_size, m_bytes_normals_size, m_normals.data());
                glBufferSubData(GL_ARRAY_BUFFER, m_bytes_vertices_size + m_bytes_normals_size, m_bytes_textcoord_size, m_texture_coord.data());


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
                        if (m_ebo != 0)
                        {
                            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
                            if (glIsBuffer(m_ebo) == GL_TRUE)
                            {
                                glEnableVertexAttribArray(0);
                                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

                                glEnableVertexAttribArray(1);
                                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_bytes_vertices_size));

                                glEnableVertexAttribArray(2);
                                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_bytes_vertices_size + m_bytes_normals_size));

                                glBindVertexArray(0);
                                glBindBuffer(GL_ARRAY_BUFFER, 0);
                                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

                            }
                        }

                    }
                }

                glBindVertexArray(0);
            }
        }
    }
    void TriangleTextured::Load()
    {
        m_vertices = 
        {
            -1.0f, -1.0f, 0.f,
            1.0f, -1.0f, 0.f,
            0.f, 1.0f, 0.f
        };
     
        m_normals =
        {
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f
        };


        m_texture_coord = {
            0.0f, 0.0f,  // lower-left corner  
            1.0f, 0.0f,  // lower-right corner
            0.5f, 1.0f   // top-center corner
        };

        m_indices =
        {
            0,
            1,
            2
        };

        m_bytes_indices_size = (unsigned int)(m_indices.size() * sizeof(unsigned int));

        m_bytes_textcoord_size = (unsigned int)(m_texture_coord.size() * sizeof(GLfloat));
        m_bytes_vertices_size = m_vertices.size() * sizeof(GLfloat);
        m_bytes_normals_size = m_normals.size() * sizeof(GLfloat);
    }
}