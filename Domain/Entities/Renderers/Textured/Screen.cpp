/******************************************************************************************************************************************/
// File : Screen.cpp
// Purpose : Implementing the Screen renderer
/******************************************************************************************************************************************/
#include "Screen.hpp"

namespace Renderers {
	Screen::Screen()
	{
		m_vbo = 0;
		m_vao = 0;

		m_bytes_vertices_size = 0;
		m_bytes_textcoord_size = 0;
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

	}
	void Screen::Draw(unsigned int const texture_id, unsigned int const ping_pong_texture)
	{
		if (m_vao != 0)
		{
			glBindVertexArray(m_vao);
			if (glIsVertexArray(m_vao) == GL_TRUE)
			{
				if (texture_id != 0 && ping_pong_texture != 0)
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, texture_id);

					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, ping_pong_texture);

					glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, 0);

					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, 0);
					glBindVertexArray(0);
				}
				else
				{
					glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
				}
			}
		}
	}

	void Screen::Draw(bool first_it, unsigned int const texture_id, unsigned int const ping_pong_texture)
	{
		if (texture_id == 0 && ping_pong_texture == 0)
		{
			glBindVertexArray(m_vao);
			if (glIsVertexArray(m_vao) == GL_TRUE)
			{
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			}
		}
		else
		{
			if (first_it)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture_id);

			}
			else
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, ping_pong_texture);
			}

			glBindVertexArray(m_vao);
			if (glIsVertexArray(m_vao) == GL_TRUE)
			{
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			}

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glBindVertexArray(0);
	}

	void Screen::Draw(unsigned int texture_id)
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
						glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

						glActiveTexture(GL_TEXTURE0);
						glBindTexture(GL_TEXTURE_2D, 0);
					}
				}
				else
				{
					glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
				}
				glBindVertexArray(0);
			}
		}
	}

	void Screen::Attach()
	{
		if (m_vbo == 0)
		{
			glGenBuffers(1, &m_vbo);
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

		if (m_vao == 0)
		{
			glGenVertexArrays(1, &m_vao);
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
						glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_bytes_vertices_size));
						glEnableVertexAttribArray(2);
						glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_bytes_vertices_size + m_bytes_normals_size));

						glBindBuffer(GL_ARRAY_BUFFER, 0);
					}
				}

				glBindVertexArray(0);
			}

		}
	}
	void Screen::Load()
	{

		m_vertices = {
			-1.0f,  1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			1.0f, -1.0f, 0.0f
		};

		m_normals =
		{
			0.0f, 0.0f, 1.0f,  // top right
			0.0f, 0.0f, 1.0f,  // bottom right
			0.0f, 0.0f, 1.0f,  // bottom left
			0.0f, 0.0f, 1.0f   // top left
		};

		m_texture_coord = {
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 0.0f
		};

		m_bytes_vertices_size = m_vertices.size() * sizeof(GLfloat);
		m_bytes_normals_size = m_normals.size() * sizeof(GLfloat);
		m_bytes_textcoord_size = (unsigned int)(m_texture_coord.size() * sizeof(GLfloat));
	}
}