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
		base::Clean();
	}

	glm::vec3 Triangle::GetVertex1() const
	{
		return glm::vec3(m_vertices.at(0), m_vertices.at(1), m_vertices.at(2));
	}

	glm::vec3 Triangle::GetVertex2() const
	{
		return glm::vec3(m_vertices.at(3), m_vertices.at(4), m_vertices.at(5));
	}

	glm::vec3 Triangle::GetVertex3() const
	{
		return glm::vec3(m_vertices.at(6), m_vertices.at(7), m_vertices.at(8));
	}

	void Triangle::Attach()
	{
		/************************************************* VBO management ********************************************************/
		glGenBuffers(1, &m_vbo);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		if (glIsBuffer(m_vbo) == GL_TRUE)
		{
			glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size, 0, GL_STATIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, m_vertices.data());
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		/************************************************* VAO management ********************************************************/
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
		
		m_vertices.push_back(-1.0f);
		m_vertices.push_back(-1.0f);
		m_vertices.push_back(0.f);
		m_vertices.push_back(1.0f);
		m_vertices.push_back(-1.0f);
		m_vertices.push_back(0.f);
		m_vertices.push_back(0.f);
		m_vertices.push_back(1.0f);
		m_vertices.push_back(0.f);
	}
	
}