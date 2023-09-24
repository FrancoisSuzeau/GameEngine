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
		m_vertices.reserve(12);
		m_bytes_vertices_size = 12 * sizeof(GLfloat);
		m_type = Enums::RendererType::SQUARE;
		m_indices.reserve(6);
		m_bytes_indices_size = 6 * sizeof(unsigned int);

		m_model_mat = glm::mat4(1.f);
		m_back_ground_color = glm::vec3(1.f);
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
		this->CleanEbo();
		m_indices.clear();
	}

	void Square::Attach()
	{
		
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ebo);

		glBindVertexArray(m_vao);
		if (glIsVertexArray(m_vao) == GL_TRUE)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			if (glIsBuffer(m_vbo) == GL_TRUE)
			{
				glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size, m_vertices.data(), GL_STATIC_DRAW);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
				if (glIsBuffer(m_ebo) == GL_TRUE)
				{
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_bytes_indices_size, m_indices.data(), GL_STATIC_DRAW);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
					glEnableVertexAttribArray(0);

				}

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			glBindVertexArray(0);
		}
		
	}
	void Square::Load()
	{
		//top right
		m_vertices.push_back(0.5f);
		m_vertices.push_back(0.5f);
		m_vertices.push_back(0.f);
		//bottom right
		m_vertices.push_back(0.5f);
		m_vertices.push_back(-0.5f);
		m_vertices.push_back(0.f);
		//bottom left
		m_vertices.push_back(-0.5f);
		m_vertices.push_back(-0.5f);
		m_vertices.push_back(0.f);
		//top left
		m_vertices.push_back(-0.5f);
		m_vertices.push_back(0.5f);
		m_vertices.push_back(0.f);

		m_indices.push_back(0);
		m_indices.push_back(1);
		m_indices.push_back(3);
		m_indices.push_back(1);
		m_indices.push_back(2);
		m_indices.push_back(3);
	}

	void Square::CleanEbo()
	{
		if (m_ebo != 0)
		{
			glDeleteBuffers(1, &m_ebo);
			m_ebo = 0;
		}
	}

}