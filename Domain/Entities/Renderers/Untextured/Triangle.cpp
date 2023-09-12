/******************************************************************************************************************************************/
// File : Triangle.cpp
// Purpose : Implementing the triangle renderer
/******************************************************************************************************************************************/
#include "Triangle.hpp"

namespace Renderers {

	Triangle::Triangle()
	{
		m_vbo = 0;
		m_vao = 0;
		m_vertices.reserve(9);
		m_bytes_vertices_size = 9 * sizeof(GLfloat);
	}

	Triangle::~Triangle()
	{
	}

	void Triangle::Construct()
	{
		this->Load();
		this->Attach();
	}

	void Triangle::Clean()
	{
		this->CleanVbo();
		this->CleanVao();

		m_vertices.clear();
	}

	void Triangle::Attach()
	{
		/************************************************* VBO management ********************************************************/
		this->CleanVbo();
		glGenBuffers(1, &m_vbo);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		if (glIsBuffer(m_vbo) == GL_TRUE)
		{
			glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size, 0, GL_STATIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, m_vertices.data());
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		/************************************************* VAO management ********************************************************/
		this->CleanVao();
		glGenVertexArrays(1, &m_vao);

		glBindVertexArray(m_vao);

		if (glIsVertexArray(m_vao) == GL_TRUE)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

			if (glIsBuffer(m_vbo) == GL_TRUE)
			{
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			glBindVertexArray(0);
		}
	}
	void Triangle::Load()
	{
		
		m_vertices.push_back(-0.5f);
		m_vertices.push_back(-0.5f);
		m_vertices.push_back(0.f);
		m_vertices.push_back(0.5f);
		m_vertices.push_back(-0.5f);
		m_vertices.push_back(0.f);
		m_vertices.push_back(0.f);
		m_vertices.push_back(0.5f);
		m_vertices.push_back(0.f);
	}

	void Triangle::CleanVbo()
	{
		if (m_vbo != 0)
		{
			glDeleteBuffers(1, &m_vbo);
			m_vbo = 0;
		}
	}
	void Triangle::CleanVao()
	{
		if (m_vao != 0)
		{
			glDeleteVertexArrays(1, &m_vao);
			m_vao = 0;

		}
	}
}