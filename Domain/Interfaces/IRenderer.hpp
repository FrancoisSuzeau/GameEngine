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

namespace Enums {
	enum RendererType {NONE, TRIANGLE, SQUARE};
}

namespace Renderers {

	

	class IRenderer
	{
	public:
		virtual ~IRenderer() {}
		virtual void Construct() = 0;
		virtual void Clean()
		{
			CleanVbo();
			CleanVao(),
			m_vertices.clear();
		}
		virtual Enums::RendererType GetType()
		{
			return m_type;
		}

		virtual GLuint GetVAO()
		{
			return m_vao;
		}

	protected:
		std::vector<GLfloat> m_vertices;
		unsigned int m_bytes_vertices_size;
		GLuint m_vbo;
		GLuint m_vao;
		GLuint  m_ebo;
		Enums::RendererType m_type;

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

		

		
	};
}

#endif