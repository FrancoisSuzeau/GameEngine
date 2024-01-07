/******************************************************************************************************************************************/
// File : IRenderer.hpp
// Purpose : An interface for the renderers
/******************************************************************************************************************************************/
#ifndef IRENDERER_H
#define IRENDERER_H

#include <GL/glew.h>
#include <vector>
#include "../Shaders/Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
		virtual ~IRenderer() { }
		virtual void Construct() = 0;
		virtual void Clean()
		{
			CleanVbo();
			CleanVao();
			CleanEbo();
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

		virtual glm::vec3 GetPosition() const
		{
			return m_position;
		}

		virtual void SetPosition(glm::vec3 const new_val)
		{
			m_position = new_val;
		}

		virtual glm::vec3 GetSize() const
		{
			return m_size;
		}

		virtual void SetSize(glm::vec3 const new_val)
		{
			m_size = new_val;
		}

		virtual void SetHovered(bool const new_val)
		{
			m_hovered = new_val;
		}

		virtual void SetSelected(bool const new_val)
		{
			m_selected = new_val;
		}

		virtual bool GetHovered() const
		{
			return m_hovered;
		}

		virtual bool GetSelected() const
		{
			return m_selected;
		}

		void IncrementAngle(float const incr)
		{
			if (m_angle > 360.f)
			{
				m_angle = 0.f;
			}
			else
			{
				m_angle += incr;
			}
		}

		float GetAngle() const
		{
			return m_angle;
		}

	protected:
		std::vector<GLfloat> m_vertices;
		size_t m_bytes_vertices_size;
		GLuint m_vbo;
		GLuint m_vao;
		GLuint m_ebo;
		Enums::RendererType m_type;

		glm::mat4 m_model_mat;
		glm::vec3 m_back_ground_color;
		glm::vec3 m_position;
		glm::vec3 m_size;
		bool m_hovered;
		bool m_selected;
		float m_angle;

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