/******************************************************************************************************************************************/
// File : IRenderer.hpp
// Purpose : An interface for the renderers
/******************************************************************************************************************************************/
#ifndef IRENDERER_H
#define IRENDERER_H

#include <GL/glew.h>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

namespace Enums {
	enum RendererType { NONE = -1, TRIANGLE = 0, SQUARE = 1, CUBE_TEXTURED = 2, SQUARE_TEXTURED = 3, GRID = 4, SKYBOX = 5, SUBBGRID = 6, SUBGRID2 = 7  };
}

namespace Renderers {

	

	class IRenderer
	{
	public:
		virtual ~IRenderer() { }
		virtual void Construct() = 0;
		virtual void Draw() {}
		virtual void Draw(unsigned int texture_id) {}
		virtual void Draw(unsigned int const texture_id, unsigned int const ping_pong_texture) {}
		virtual void Draw(bool first_it, unsigned int const texture_id, unsigned int const ping_pong_texture) {}
		virtual void Actualize(int const grid_scaling_ratio) {}
		virtual void Clean()
		{
			CleanVbo();
			CleanVao();
			CleanEbo();
			m_vertices.clear();
			m_indices.clear();
		}


	protected:
		std::vector<GLfloat> m_vertices;
		size_t m_bytes_vertices_size;
		GLuint m_vbo;
		GLuint m_vao;
		GLuint m_ebo;

		std::vector<unsigned int> m_indices;
		unsigned int m_bytes_indices_size;

	private:
		virtual void CleanVbo()
		{
			if (m_vbo != 0)
			{
				glDeleteBuffers(1, &m_vbo);
				m_vbo = 0;
			}
		}

		 virtual void CleanVao()
		{
			if (m_vao != 0)
			{
				glDeleteVertexArrays(1, &m_vao);
				m_vao = 0;

			}
		}

		 virtual void CleanEbo()
		 {
			 if (m_ebo != 0)
			 {
				 glDeleteBuffers(1, &m_ebo);
				 m_ebo = 0;
			 }
		 }

		

		
	};
}

#endif