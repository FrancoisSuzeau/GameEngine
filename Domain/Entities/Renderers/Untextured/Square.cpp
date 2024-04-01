/******************************************************************************************************************************************/
// File : Square.cpp
// Purpose : Implementing the Square renderer
/******************************************************************************************************************************************/
#include "Square.hpp"

namespace Renderers {

	Square::Square()
	{
		m_vbo = 0;
		m_vao = 0;
		m_ebo = 0;
		m_bytes_vertices_size = 0;
		m_bytes_indices_size = 0;
	}

	Square::~Square()
	{
	}

	void Square::Construct()
	{
		this->Load();
		this->Attach();
	}

	void Square::Clean()
	{
		base::Clean();
	}

	void Square::Draw()
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

	void Square::Attach()
	{
		if (m_vao == 0)
		{
			glGenVertexArrays(1, &m_vao);
		}

		if (m_vbo == 0)
		{
			glGenBuffers(1, &m_vbo);
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
			}
		}
		
	}
	void Square::Load()
	{
		//top right
		m_vertices.push_back(1.0f);
		m_vertices.push_back(1.0f);
		m_vertices.push_back(0.f);
		//bottom right
		m_vertices.push_back(1.0f);
		m_vertices.push_back(-1.0f);
		m_vertices.push_back(0.f);
		//bottom left
		m_vertices.push_back(-1.0f);
		m_vertices.push_back(-1.0f);
		m_vertices.push_back(0.f);
		//top left
		m_vertices.push_back(-1.0f);
		m_vertices.push_back(1.0f);
		m_vertices.push_back(0.f);

		m_indices.push_back(0);
		m_indices.push_back(1);
		m_indices.push_back(3);
		m_indices.push_back(1);
		m_indices.push_back(2);
		m_indices.push_back(3);

		m_bytes_vertices_size = m_vertices.size() * sizeof(GLfloat);
		m_bytes_indices_size = m_indices.size() * sizeof(unsigned int);
	}

}