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
		m_vertices.reserve(108);
		m_bytes_vertices_size = 108 * sizeof(GLfloat);
        m_texture_id = 0;
        m_type = Enums::SKYBOX;
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
	unsigned int Skybox::GetTextureId() const
	{
        return m_texture_id;
	}
	void Skybox::SetTextureID(unsigned int const texture_id)
	{
        m_texture_id = texture_id;
	}
	void Skybox::Attach()
	{
        glGenBuffers(1, &m_vbo);

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

        glGenVertexArrays(1, &m_vao);

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
        float skyboxVertices[108] = {
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

        
        for (int i = 0; i < 108; i++)
        {
            m_vertices.push_back(skyboxVertices[i]);
        }
		
	}
}