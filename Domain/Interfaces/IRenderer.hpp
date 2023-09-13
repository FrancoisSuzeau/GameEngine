/******************************************************************************************************************************************/
// File : IRenderer.hpp
// Purpose : An interface for the renderers
/******************************************************************************************************************************************/
#ifndef IRENDERER_H
#define IRENDERER_H

#include <GL/glew.h>
#include <vector>
#include "../Shaders/Shader.hpp"

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

namespace Renderers {

	class IRenderer
	{
	public:
		virtual ~IRenderer() {}
		virtual void Construct() = 0;
		void Clean()
		{
			CleanVbo();
			CleanVao(),
			m_vertices.clear();
		}
		GLuint GetVAO()
		{
			return m_vao;
		}

	protected:
		std::vector<GLfloat> m_vertices;
		int m_bytes_vertices_size;
		GLuint m_vbo;
		GLuint m_vao;
	private:
		void CleanVbo()
		{
			if (m_vbo != 0)
			{
				glDeleteBuffers(1, &m_vbo);
				m_vbo = 0;
			}
		}

		void CleanVao()
		{
			if (m_vao != 0)
			{
				glDeleteVertexArrays(1, &m_vao);
				m_vao = 0;

			}
		}

		

		
	};
}

#endif