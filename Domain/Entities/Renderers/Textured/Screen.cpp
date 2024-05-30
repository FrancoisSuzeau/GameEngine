/******************************************************************************************************************************************/
// File : Screen.cpp
// Purpose : Implementing the Screen renderer
/******************************************************************************************************************************************/
#include "Screen.hpp"

namespace Renderers {
	Screen::Screen() : base(), m_bytes_textcoord_size(0)
	{
		
	}
	Screen::~Screen()
	{
	}
	void Screen::Construct()
	{
		this->Load();
		this->Attach();
	}
	void Screen::Clean()
	{
		base::Clean();
		m_texture_coord.clear();
		m_bytes_textcoord_size = 0;

	}
	void Screen::Draw(unsigned int const texture_id, unsigned int const ping_pong_texture)
	{
		if (texture_id != 0 && ping_pong_texture != 0)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture_id);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, ping_pong_texture);
		}

		base::Draw();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
	}

	void Screen::Draw(bool first_it, unsigned int const texture_id, unsigned int const ping_pong_texture)
	{
		if (texture_id == 0 && ping_pong_texture == 0)
		{
			base::Draw();
		}
		else
		{
			if (first_it)
			{
				if (texture_id != 0)
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, texture_id);
				}

			}
			else
			{
				if (ping_pong_texture != 0)
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, ping_pong_texture);
				}
			}

			base::Draw();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glBindVertexArray(0);
	}

	void Screen::Draw(unsigned int texture_id)
	{
		if (texture_id != 0)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture_id);
		}

		base::Draw();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Screen::Attach()
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
				glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size + m_bytes_textcoord_size, 0, GL_STATIC_DRAW);

				glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, m_vertices.data());
				glBufferSubData(GL_ARRAY_BUFFER, m_bytes_vertices_size, m_bytes_textcoord_size, m_texture_coord.data());

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

								glEnableVertexAttribArray(2);
								glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_bytes_vertices_size));

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
	void Screen::Load()
	{
		m_vertices = {
			 1.0f,  1.0f, 0.0f,  // top right
			 1.0f, -1.0f, 0.0f,  // bottom right
			-1.0f, -1.0f, 0.0f,  // bottom left
			-1.0f,  1.0f, 0.0f,  // top left
		};

		m_indices =
		{
			0, 1, 3,
			1, 2, 3
		};

		m_texture_coord = {
			1.f, 1.f,
			1.f, 0.f,
			0.f, 0.f,
			0.f, 1.f
		};

		m_bytes_indices_size = (unsigned int)(m_indices.size() * sizeof(unsigned int));
		m_bytes_vertices_size = m_vertices.size() * sizeof(GLfloat);
		m_bytes_textcoord_size = (unsigned int)(m_texture_coord.size() * sizeof(GLfloat));
	}
}