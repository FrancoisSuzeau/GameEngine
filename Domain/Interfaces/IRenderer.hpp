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
		virtual void Clean() = 0;
		virtual void Render(GLuint const program_id) = 0;

	protected:
		std::vector<GLfloat> m_vertices;
		int m_bytes_vertices_size;

		GLuint m_vbo;
		GLuint m_vao;

		
	};
}

#endif