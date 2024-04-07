/******************************************************************************************************************************************/
// File : Grid.cpp
// Purpose : Implementing the Grid renderer
/******************************************************************************************************************************************/
#include "Grid.hpp"

namespace Renderers {

	Grid::Grid(const int grid_size, const float grid_spacing) : m_grid_size(grid_size), m_grid_spacing(grid_spacing / 100.f)
	{
		m_ebo = 0;
		m_vao = 0;
		m_vbo = 0;
		m_bytes_vertices_size = 0;
		m_bytes_indices_size = 0;
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
		m_vec_vertices.clear();
	}

	void Grid::Draw()
	{
		if (m_vao != 0)
		{
			glBindVertexArray(m_vao);
			if (glIsVertexArray(m_vao) == GL_TRUE)
			{
				glDrawElements(GL_LINES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);
			}
		}
	}

	void Grid::Actualize(int const grid_scaling_ratio, int const behavior)
	{
		switch (behavior)
		{
		case 1:
			m_grid_spacing += (float)grid_scaling_ratio / 100.f;
			break;
		case -1:
			m_grid_spacing -= (float)grid_scaling_ratio / 100.f;
			break;
		default:
			break;
		}
		
		m_vec_vertices.clear();
		m_indices.clear();
		this->Construct();
	}

	void Grid::Attach()
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
				glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size, 0, GL_DYNAMIC_DRAW);
				glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, m_vec_vertices.data());

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
						glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
						glEnableVertexAttribArray(0);

						glBindBuffer(GL_ARRAY_BUFFER, 0);
					}
				}

				glBindVertexArray(0);
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
								glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
								glEnableVertexAttribArray(0);

								glBindVertexArray(0);
								glBindBuffer(GL_ARRAY_BUFFER, 0);
								glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

							}
						}
					}
				}
			}
		}
	}
	void Grid::Load()
	{
		for (int i = 0; i <= m_grid_size; ++i) 
		{
			float x = i * m_grid_spacing;
			float y = 0.0f;
			float z = 0.0f;
			m_vec_vertices.push_back(glm::vec3(x, y, 0.0f));
			m_vec_vertices.push_back(glm::vec3(x, y, m_grid_size * m_grid_spacing));

			x = 0.0f;
			y = 0.0f;
			z = i * m_grid_spacing;
			m_vec_vertices.push_back(glm::vec3(0.0f, y, z));
			m_vec_vertices.push_back(glm::vec3(m_grid_size * m_grid_spacing, y, z));
		}

		m_bytes_vertices_size = m_vec_vertices.size() * sizeof(glm::vec3);

		for (unsigned int i = 0; i < m_vec_vertices.size(); ++i)
		{
			m_indices.push_back(i);
		}

		m_bytes_indices_size = (unsigned int)(m_indices.size() * sizeof(unsigned int));
	}

}