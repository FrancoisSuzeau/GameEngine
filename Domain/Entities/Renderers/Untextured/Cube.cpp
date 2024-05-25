/******************************************************************************************************************************************/
// File : Cube.cpp
// Purpose : Implementing the Cube renderer
/******************************************************************************************************************************************/
#include "Cube.hpp"

namespace Renderers {

	Cube::Cube()
	{
		m_vbo = 0;
		m_vao = 0;
        m_ebo = 0;
        m_bytes_vertices_size = 0;
        m_bytes_indices_size = 0;
	}

	Cube::~Cube()
	{
	}

	void Cube::Construct()
	{
		this->Load();
		this->Attach();
	}

	void Cube::Draw()
	{
        if (m_vao != 0)
        {
            glBindVertexArray(m_vao);
            if (glIsVertexArray(m_vao) == GL_TRUE)
            {
                glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);

                glBindVertexArray(0);
            }
        }
	}

	void Cube::Clean()
	{
		base::Clean();
	}

	void Cube::Attach()
	{
        if (m_vbo == 0)
        {
            glGenBuffers(1, &m_vbo);
        }

        if (m_ebo == 0)
        {
            glGenBuffers(1, &m_ebo);
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
                                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
                                glEnableVertexAttribArray(0);

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
	void Cube::Load()
	{
        m_vertices = {    
            -1.0f,  1.0f, -1.0f, //Front face
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f, //Back face
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f, //Top face
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f, //Bottom face
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f, //Left face
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f, //Right face
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
        };

        m_normals = 
        {
            0.0f,  0.0f, -1.0f,  // Front face
            0.0f,  0.0f, -1.0f,
            0.0f,  0.0f, -1.0f,
            0.0f,  0.0f, -1.0f,

            0.0f,  0.0f,  1.0f,  // Back face
            0.0f,  0.0f,  1.0f,
            0.0f,  0.0f,  1.0f,
            0.0f,  0.0f,  1.0f,

            0.0f,  1.0f,  0.0f,  // Top face
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,

            0.0f, -1.0f,  0.0f,  // Bottom face
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,

            -1.0f,  0.0f,  0.0f,  // Left face
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,
            -1.0f,  0.0f,  0.0f,

             1.0f,  0.0f,  0.0f,  // Right face
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f
        };


        for (int i = 0; i < m_vertices.size(); ++i)
        {
            m_indices.push_back(i);
        }

        m_bytes_indices_size = (unsigned int)(m_indices.size() * sizeof(unsigned int));
        m_bytes_normals_size = m_normals.size() * sizeof(GLfloat);
        m_bytes_vertices_size = m_vertices.size() * sizeof(GLfloat);
	}

}