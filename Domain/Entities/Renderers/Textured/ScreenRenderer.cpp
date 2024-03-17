/******************************************************************************************************************************************/
// File : ScreenRenderer.cpp
// Purpose : Implementing the ScreenRenderer renderer
/******************************************************************************************************************************************/
#include "ScreenRenderer.hpp"

namespace Renderers {
	ScreenRenderer::ScreenRenderer()
	{
		m_vbo = 0;
		m_vao = 0;
		m_vertices.reserve(18);
		m_bytes_vertices_size = 18 * sizeof(GLfloat);
		m_texture_coord.reserve(12);
		m_bytes_textcoord_size = 12 * sizeof(GLfloat);

	}
	ScreenRenderer::~ScreenRenderer()
	{
	}
	void ScreenRenderer::Construct()
	{
		this->Load();
		this->Attach();
	}
	void ScreenRenderer::Clean()
	{
		base::Clean();
		m_texture_coord.clear();
		
	}
	void ScreenRenderer::Draw(unsigned int const texture_id)
	{
		glBindVertexArray(this->GetVAO());
		if (glIsVertexArray(this->GetVAO()) == GL_TRUE)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture_id);
			if (glIsTexture(texture_id) == GL_TRUE)
			{
				glDrawArrays(GL_TRIANGLES, 0, 6);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			glBindVertexArray(0);
		}
	}

	void ScreenRenderer::Attach()
	{
		glGenBuffers(1, &m_vbo);
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

		glGenVertexArrays(1, &m_vao);
		if (m_vao != 0)
		{
			glBindVertexArray(m_vao);
			if (glIsVertexArray(m_vao) == GL_TRUE)
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

				glBindVertexArray(0);
			}

		}
	}
	void ScreenRenderer::Load()
	{

		float vertices[18] = { -1.0f, -1.0f, -1.0f,   1.0f, -1.0f, -1.0f,   1.0f, 1.0f, -1.0f,
						-1.0f, -1.0f, -1.0f,   -1.0f, 1.0f, -1.0f,   1.0f, 1.0f, -1.0f
		};

		float coord[12] = { 0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
							  0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f
		};

		for (int i = 0; i < 18; i++)
		{
			m_vertices.push_back(vertices[i]);
			if (i < 12)
			{
				m_texture_coord.push_back(coord[i]);
			}
		}
	}
}