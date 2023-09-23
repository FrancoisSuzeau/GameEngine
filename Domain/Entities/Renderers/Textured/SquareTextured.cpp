/******************************************************************************************************************************************/
// File : SquareTextured.cpp
// Purpose : Implementing the SquareTextured renderer
/******************************************************************************************************************************************/
#include "SquareTextured.hpp"

namespace Renderers {
	SquareTextured::SquareTextured() : base()
	{
		m_vertices.reserve(18);
		m_bytes_vertices_size = 18 * sizeof(GLfloat);
		m_texture_coord.reserve(12);
		m_bytes_texture_coord_size = 12 * sizeof(GLfloat);
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
		m_texture_coord.clear();
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
		float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
			// positions   // texCoords
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,

			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f, 1.0f
		};
		/************************************************* VBO management ********************************************************/
		glGenBuffers(1, &m_vbo);

		//glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		//if (glIsBuffer(m_vbo) == GL_TRUE)
		//{
		//	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		//	/*glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, m_vertices.data());
		//	glBufferSubData(GL_ARRAY_BUFFER, m_bytes_vertices_size, m_bytes_texture_coord_size, m_texture_coord.data());*/
		//	glBindBuffer(GL_ARRAY_BUFFER, 0);
		//}

		/************************************************* VAO management ********************************************************/
		glGenVertexArrays(1, &m_vao);

		glBindVertexArray(m_vao);

		if (glIsVertexArray(m_vao) == GL_TRUE)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

			if (glIsBuffer(m_vbo) == GL_TRUE)
			{
				glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
				
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
				

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			glBindVertexArray(0);
		}
	}
	void SquareTextured::Load()
	{
		//vertices positions
		m_vertices.push_back(-1.f);
		m_vertices.push_back(-1.f);
		m_vertices.push_back(-1.f);

		m_vertices.push_back(1.f);
		m_vertices.push_back(-1.f);
		m_vertices.push_back(-1.f);

		m_vertices.push_back(1.f);
		m_vertices.push_back(1.f);
		m_vertices.push_back(-1.f);

		m_vertices.push_back(-1.f);
		m_vertices.push_back(-1.f);
		m_vertices.push_back(-1.f);

		m_vertices.push_back(-1.f);
		m_vertices.push_back(1.f);
		m_vertices.push_back(-1.f);

		m_vertices.push_back(1.f);
		m_vertices.push_back(1.f);
		m_vertices.push_back(-1.f);

		//texture coordinates
		m_texture_coord.push_back(0.f);
		m_texture_coord.push_back(0.f);
		
		m_texture_coord.push_back(1.f);
		m_texture_coord.push_back(0.f);
		
		m_texture_coord.push_back(1.f);
		m_texture_coord.push_back(1.f);
		
		m_texture_coord.push_back(0.f);
		m_texture_coord.push_back(0.f);

		m_texture_coord.push_back(0.f);
		m_texture_coord.push_back(1.f);

		m_texture_coord.push_back(1.f);
		m_texture_coord.push_back(1.f);
	}
}