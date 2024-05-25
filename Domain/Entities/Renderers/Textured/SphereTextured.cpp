/******************************************************************************************************************************************/
// File : SphereTextured.cpp
// Purpose : Implementing the SphereTextured renderer
/******************************************************************************************************************************************/
#include "SphereTextured.hpp"

namespace Renderers {

	SphereTextured::SphereTextured(float radius, unsigned int long_seg, unsigned int lat_seg) : m_radius(radius), m_long_seg(long_seg), m_lat_seg(lat_seg)
	{
		m_vbo = 0;
		m_vao = 0;
		m_ebo = 0;
		m_bytes_vertices_size = 0;
		m_bytes_indices_size = 0;
		m_bytes_textcoord_size = 0;
		m_bytes_normals_size = 0;
	}

	SphereTextured::~SphereTextured()
	{
	}

	void SphereTextured::Construct()
	{
		this->Load();
		this->Attach();
	}

	void SphereTextured::Draw(unsigned int texture_id)
	{
		if (m_vao != 0)
		{
			glBindVertexArray(m_vao);
			if (glIsVertexArray(m_vao) == GL_TRUE)
			{
				if (texture_id != 0)
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, texture_id);
					if (glIsTexture(texture_id) == GL_TRUE)
					{
						glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);
						glBindTexture(GL_TEXTURE_2D, 0);
					}
				}
				else
				{
					glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);
				}
				
				glBindVertexArray(0);
			}
		}
	}

	void SphereTextured::Clean()
	{
		base::Clean();
	}

	void SphereTextured::Attach()
	{
		/************************************************* VBO management ********************************************************/

		if (m_vbo == 0)
		{
			glGenBuffers(1, &m_vbo);
		}

		if (m_vao == 0)
		{
			glGenVertexArrays(1, &m_vao);
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
				glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size + m_bytes_normals_size + m_bytes_textcoord_size, 0, GL_STATIC_DRAW);
				glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, m_vertices.data());
				glBufferSubData(GL_ARRAY_BUFFER, m_bytes_vertices_size, m_bytes_normals_size, m_normals.data());
				glBufferSubData(GL_ARRAY_BUFFER, m_bytes_vertices_size + m_bytes_normals_size, m_bytes_textcoord_size, m_texture_coord.data());
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

		/************************************************* VAO management ********************************************************/

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
								glEnableVertexAttribArray(0);
								glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

								glEnableVertexAttribArray(1);
								glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_bytes_vertices_size));

								glEnableVertexAttribArray(2);
								glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_bytes_vertices_size + m_bytes_normals_size));

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
	void SphereTextured::Load()
	{

		unsigned int long_verts = m_long_seg + 1;
		unsigned int lat_verts = m_lat_seg + 1;


		for (float i = 0.f; i < long_verts; i++)
		{
			const double i_div_long = i / m_long_seg;
			const double theta = i == 0.0 || i == m_long_seg ? 0.0 : i_div_long * 2.0 * M_PI;

			for (float j = 0.f; j < lat_verts; j++)
			{
				const double j_div_lat = j / m_lat_seg;
				const double phi = j_div_lat * M_PI;

				GLfloat n1 = (GLfloat)cos(theta) * (GLfloat)sin(phi);
				GLfloat n2 = (GLfloat)cos(phi);
				GLfloat n3 = (GLfloat)sin(theta) * (GLfloat)sin(phi);


				m_vertices.push_back(n1 * m_radius);
				m_vertices.push_back(n2 * m_radius);
				m_vertices.push_back(n3 * m_radius);

				m_texture_coord.push_back(n1 * m_radius);
				m_texture_coord.push_back(n2 * m_radius);
				m_texture_coord.push_back(n3 * m_radius);

				m_normals.push_back(n1);
				m_normals.push_back(n2);
				m_normals.push_back(n3);
			}
		}

		

		for (unsigned int i = 0; i < m_long_seg; i++)
		{
			for (unsigned int j = 0; j < m_lat_seg; j++)
			{
				const unsigned int v0 = j + lat_verts * i;
				const unsigned int v1 = j + lat_verts * (i + 1);
				const unsigned int v2 = v1 + 1;
				const unsigned int v3 = v0 + 1;

				m_indices.push_back(v0);
				m_indices.push_back(v1);
				m_indices.push_back(v2);

				m_indices.push_back(v0);
				m_indices.push_back(v2);
				m_indices.push_back(v3);
			}
		}

		m_bytes_indices_size = (unsigned int)(m_indices.size() * sizeof(unsigned int));
		m_bytes_vertices_size = m_vertices.size() * sizeof(GLfloat);
		m_bytes_textcoord_size = (unsigned int)(m_texture_coord.size() * sizeof(GLfloat));
		m_bytes_normals_size = m_normals.size() * sizeof(GLfloat);
	}

}