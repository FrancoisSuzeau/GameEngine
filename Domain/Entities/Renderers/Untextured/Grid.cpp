/******************************************************************************************************************************************/
// File : Grid.cpp
// Purpose : Implementing the Grid renderer
/******************************************************************************************************************************************/
#include "Grid.hpp"

namespace Renderers {

	Grid::Grid(int slice) : m_slices(slice)
	{
		m_ebo = 0;
		m_vao = 0;
		m_vbo = 0;

		m_type = Enums::RendererType::GRID;
		
		m_lenght = 0;
		m_model_mat = glm::mat4(1.f);
		m_back_ground_color = glm::vec3(1.f);
	}

	Grid::~Grid()
	{
	}

	void Grid::Construct()
	{
		this->Load();
		this->Attach();
	}

	void Grid::Clean()
	{
		base::Clean();
		this->CleanEbo();
		m_vec_indices.clear();
		m_vec_vertices.clear();

	}

	GLint Grid::GetLength() const
	{
		return m_lenght;
	}

	void Grid::Attach()
	{
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vec_vertices.size() * sizeof(glm::vec3), glm::value_ptr(m_vec_vertices[0]), GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		
		glGenBuffers(1, &m_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vec_indices.size() * sizeof(glm::uvec4), glm::value_ptr(m_vec_indices[0]), GL_STATIC_DRAW);

		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_lenght = (GLuint)m_vec_indices.size() * 4;
	}
	void Grid::Load()
	{
		for (int i = 0; i <= m_slices; i++) 
		{
			for (int j = 0; j <= m_slices; j++) 
			{
				float x = (float)i / (float)m_slices;
				float y = 0;
				float z = (float)j / (float)m_slices;

				m_vec_vertices.push_back(glm::vec3(x, y, z));
			}
		}

		for (int i = 0; i < m_slices; i++) 
		{
			for (int j = 0; j < m_slices; j++) 
			{

				int row1 = j * (m_slices + 1);
				int row2 = (j + 1) * (m_slices + 1);

				m_vec_indices.push_back(glm::uvec4(row1 + i, row1 + i + 1, row1 + i + 1, row2 + i + 1));
				m_vec_indices.push_back(glm::uvec4(row2 + i + 1, row2 + i, row2 + i, row1 + i));

			}
		}
	}

	void Grid::CleanEbo()
	{
		if (m_ebo != 0)
		{
			glDeleteBuffers(1, &m_ebo);
			m_ebo = 0;
		}
	}

}