/******************************************************************************************************************************************/
// File : Grid.cpp
// Purpose : Implementing the Grid renderer
/******************************************************************************************************************************************/
#include "Grid.hpp"

namespace Renderers {

	Grid::Grid(const int grid_size, const float grid_spacing) : m_grid_size(grid_size), m_grid_spacing(grid_spacing)
	{
		m_ebo = 0;
		m_vao = 0;
		m_vbo = 0;
		m_bytes_vertices_size = 0;
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

		glBindVertexArray(this->GetVAO());
		if (glIsVertexArray(this->GetVAO()) == GL_TRUE)
		{
			glDrawArrays(GL_LINES, 0, (GLsizei)m_vec_vertices.size());
			glBindVertexArray(0);
		}
	}

	void Grid::Actualize(float const relative_distance_from_cam)
	{
		float new_grid_spacing = m_grid_spacing * (1.f + relative_distance_from_cam * 0.05f);
		m_grid_spacing = new_grid_spacing;
		this->Clean();
		this->Construct();
	}

	void Grid::Attach()
	{

		glGenVertexArrays(1, &m_vao);
		if (m_vao != 0)
		{
			glBindVertexArray(m_vao);

			glGenBuffers(1, &m_vbo);
			if (m_vbo != 0)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
				if (glIsBuffer(m_vbo) == GL_TRUE)
				{
					glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size, m_vec_vertices.data(), GL_DYNAMIC_DRAW);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

					glBindBuffer(GL_ARRAY_BUFFER, 0);
					glBindVertexArray(0);
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

			m_bytes_vertices_size = m_vec_vertices.size() * sizeof(glm::vec3);
		}
	}

}