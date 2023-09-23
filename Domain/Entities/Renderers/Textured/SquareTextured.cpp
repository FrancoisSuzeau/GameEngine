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
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size, m_vertices.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
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