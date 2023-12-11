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
		m_vec_vertices.reserve((m_slices + 1) * (m_slices + 1));
		m_vec_indices.reserve((m_slices) * (m_slices) * 2);
		m_bytes_vertices_size = m_vec_vertices.capacity() * sizeof(glm::vec3);
		m_bytes_indices_size = m_vec_indices.capacity() * sizeof(glm::uvec4);
		m_lenght = (GLuint)(m_vec_vertices.capacity() * 4);
		

		m_type = Enums::RendererType::GRID;
		m_model_mat = glm::mat4(1.f);
		m_back_ground_color = glm::vec3(1.f);
		m_position = glm::vec3(-10.f, -1.f, -10.f);
		m_size = glm::vec3(20.f);

		m_hovered = false;
		m_selected = false;
		m_angle = 0.f;
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
		m_vec_indices.clear();
		m_vec_vertices.clear();

	}

	GLint Grid::GetLength() const
	{
		return m_lenght;
	}

	void Grid::Attach()
	{
		glGenBuffers(1, &m_vbo);
		if (m_vbo != 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			if (glIsBuffer(m_vbo) == GL_TRUE)
			{
				glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size, 0, GL_STATIC_DRAW);
				glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, m_vec_vertices.data());
			}
		}

		glGenVertexArrays(1, &m_vao);
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
						glEnableVertexAttribArray(0);
						glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));


						glGenBuffers(1, &m_ebo);
						if (m_ebo != 0)
						{
							glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
							if (glIsBuffer(m_ebo) == GL_TRUE)
							{
								glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_bytes_indices_size, 0, GL_STATIC_DRAW);
								glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_bytes_indices_size, m_vec_indices.data());

								glBindVertexArray(0);
								glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
								glBindBuffer(GL_ARRAY_BUFFER, 0);
							}
						}
					}
				}
			}
		}

		
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

}