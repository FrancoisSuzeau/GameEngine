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
	enum RendererType {NONE, TRIANGLE, SQUARE, SQUARE_TEXTURED, GRID, SKYBOX};
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
		virtual Enums::RendererType GetType() const
		{
			return m_type;
		}

		virtual GLuint GetVAO() const
		{
			return m_vao;
		}

		virtual glm::mat4 GetModelMat() const
		{
			return m_model_mat;
		}

		virtual void SetModelMat(glm::mat4 model_mat)
		{
			m_model_mat = model_mat;
		}

		virtual void SetBackgroundColor(glm::vec3 new_bacground_color)
		{
			m_back_ground_color = new_bacground_color;
		}

		virtual glm::vec3 GetBackgroundColor() const
		{
			return m_back_ground_color;
		}

	protected:
		std::vector<GLfloat> m_vertices;
		unsigned int m_bytes_vertices_size;
		GLuint m_vbo;
		GLuint m_vao;
		GLuint  m_ebo;
		Enums::RendererType m_type;

		glm::mat4 m_model_mat;
		glm::vec3 m_back_ground_color;

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