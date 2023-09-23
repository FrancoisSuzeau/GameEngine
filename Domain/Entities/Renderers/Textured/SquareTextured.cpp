/******************************************************************************************************************************************/
// File : SquareTextured.cpp
// Purpose : Implementing the SquareTextured renderer
/******************************************************************************************************************************************/
#include "SquareTextured.hpp"

namespace Renderers {
	SquareTextured::SquareTextured() : base()
	{
		m_vertices.reserve(24);
		m_bytes_vertices_size = 24 * sizeof(GLfloat);
		m_texture_id = 0;
	}
	SquareTextured::~SquareTextured()
	{
	}
	void SquareTextured::Construct()
	{
		this->Load();
		this->Attach();
	}
	void SquareTextured::Clean()
	{
		base::Clean();
		
	}
	unsigned int SquareTextured::GetTextureId() const
	{
		return m_texture_id;
	}
	void SquareTextured::SetTextureID(unsigned int const texture_id)
	{
		m_texture_id = texture_id;
	}
	void SquareTextured::Attach()
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
				glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
				if (glIsBuffer(m_vbo) == GL_TRUE)
				{
					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), BUFFER_OFFSET(0));
					glEnableVertexAttribArray(1);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
					glBindBuffer(GL_ARRAY_BUFFER, 0);
				}

				glBindVertexArray(0);
			}

		}
	}
	void SquareTextured::Load()
	{
		float vertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
			// positions   // texCoords
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,

			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f, 1.0f
		};

		for (int i = 0; i < 24; i++)
		{
			m_vertices.push_back(vertices[i]);
		}
	}
}