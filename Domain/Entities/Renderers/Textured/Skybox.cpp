/******************************************************************************************************************************************/
// File : Skybox.cpp
// Purpose : Implementing the Skybox renderer
/******************************************************************************************************************************************/
#include "Skybox.hpp"

namespace Renderers {
	Skybox::Skybox()
	{
        m_vbo = 0;
        m_vao = 0;
        m_ebo = 0;
        m_bytes_vertices_size = 0;
        m_bytes_indices_size = 0;
	}
	Skybox::~Skybox()
	{
	}
	void Skybox::Construct()
	{
		this->Load();
		this->Attach();
	}
	void Skybox::Clean()
	{
		base::Clean();

	}
    void Skybox::Draw(unsigned int const texture_id)
    {
        if (m_vao != 0)
        {
            glBindVertexArray(m_vao);
            if (glIsVertexArray(m_vao) == GL_TRUE)
            {
                if (texture_id != 0)
                {
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
                    if (glIsTexture(texture_id) == GL_TRUE)
                    {
                        glDrawArrays(GL_TRIANGLES, 0, 36);

                        glActiveTexture(GL_TEXTURE0);
                        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
                    }
                }
                else
                {
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }

                glBindVertexArray(0);
            }
        }
    }
	
	void Skybox::Attach()
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
                glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size, 0, GL_STATIC_DRAW);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, m_vertices.data());

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
                        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
                        glEnableVertexAttribArray(0);

                        glBindBuffer(GL_ARRAY_BUFFER, 0);
                       
                    }
                }

                glBindVertexArray(0);
            }
        }
	}
	void Skybox::Load()
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
	}
}