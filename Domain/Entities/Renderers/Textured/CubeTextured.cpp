/******************************************************************************************************************************************/
// File : CubeTextured.cpp
// Purpose : Implementing the CubeTextured renderer
/******************************************************************************************************************************************/
#include "CubeTextured.hpp"

namespace Renderers {
    CubeTextured::CubeTextured()
    {
        m_vbo = 0;
        m_vao = 0;
        m_ebo = 0;
        m_bytes_vertices_size = 0;
        m_bytes_indices_size = 0;
    }
    CubeTextured::~CubeTextured()
    {
    }
    void CubeTextured::Construct()
    {
        this->Load();
        this->Attach();
    }
    void CubeTextured::Clean()
    {
        base::Clean();

    }
    void CubeTextured::Draw(unsigned int const texture_id)
    {
        if (m_vao != 0)
        {
            glBindVertexArray(m_vao);
            if (glIsVertexArray(m_vao) == GL_TRUE)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture_id);
                if (glIsTexture(texture_id) == GL_TRUE)
                {
                    glDrawArrays(GL_TRIANGLES, 0, 36);

                    glBindTexture(GL_TEXTURE_2D, 0);
                }

                glBindVertexArray(0);
            }
        }
    }

    void CubeTextured::Attach()
    {
        if (m_vbo == 0)
        {
            glGenBuffers(1, &m_vbo);
        }

        if (m_vao == 0)
        {
            glGenVertexArrays(1, &m_vao);
        }

        if (m_vbo != 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            if (glIsBuffer(m_vbo) == GL_TRUE)
            {
                glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size + m_bytes_textcoord_size, 0, GL_STATIC_DRAW);

                glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, m_vertices.data());
                glBufferSubData(GL_ARRAY_BUFFER, m_bytes_vertices_size, m_bytes_textcoord_size, m_texture_coord.data());


                glBindBuffer(GL_ARRAY_BUFFER, 0);

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
                        glEnableVertexAttribArray(0);
                        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

                        glEnableVertexAttribArray(1);
                        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_bytes_vertices_size));
                        glBindBuffer(GL_ARRAY_BUFFER, 0);

                    }
                }

                glBindVertexArray(0);
            }
        }
    }
    void CubeTextured::Load()
    {
        m_vertices = {
            // positions          
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
        };

        m_bytes_vertices_size = m_vertices.size() * sizeof(GLfloat);


        m_texture_coord = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,

            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,

            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,

            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,

            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f,

            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f

        };

        m_bytes_textcoord_size = (unsigned int) (m_texture_coord.size() * sizeof(GLfloat));
    }
}