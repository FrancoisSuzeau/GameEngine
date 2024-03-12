/******************************************************************************************************************************************/
// File : Canvas.cpp
// Purpose : Implementing the GUI view app style editor
/******************************************************************************************************************************************/

#include "Canvas.hpp"

namespace Views
{
	Canvas::Canvas()
	{
		m_draggable_component = std::make_unique<Views::Draggable >();

		m_shader_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::ShaderService>();
		if (!m_shader_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : Shader service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}

	void Canvas::Clean()
	{
		if (m_draggable_component)
		{
			m_draggable_component->Clean();
			m_draggable_component.reset();
		}

		if (m_shader_service)
		{
			m_shader_service.reset();
		}
	}

	void Canvas::Render(std::vector<std::shared_ptr<Renderers::IRenderer>> renderers, GLenum const mode, float const line_width)
	{
		for (std::vector<std::shared_ptr<Renderers::IRenderer>>::iterator it = renderers.begin(); it != renderers.end(); it++)
		{
			if (m_draggable_component)
			{
				m_draggable_component->OnHoverRenderer(it[0]);
			}
			glLineWidth(line_width);
			glPolygonMode(GL_FRONT_AND_BACK, mode);
			switch (it[0]->GetType())
			{
			case Enums::RendererType::TRIANGLE:
			{
				std::shared_ptr<Renderers::Triangle> t = std::dynamic_pointer_cast<Renderers::Triangle> (it[0]);
				
				std::string shader_name = Constants::UNTEXTURED_SHADER;
				if (mode == GL_LINE)
				{
					shader_name = Constants::HOVER_SHADER;
				}
				if (m_shader_service && t)
				{
					glBindVertexArray(t->GetVAO());
					if (glIsVertexArray(t->GetVAO()) == GL_TRUE)
					{
						GLuint program_id = m_shader_service->GetProgramId(shader_name);
						glUseProgram(program_id);
						Component::Transformer::PutIntoShader(t, m_shader_service, shader_name);
						glDrawArrays(GL_TRIANGLES, 0, 3);
						glUseProgram(0);
						glBindVertexArray(0);
					}
				}
				t.reset();
			}
			break;
			case Enums::RendererType::SQUARE:
			{
				std::shared_ptr<Renderers::Square> s = std::dynamic_pointer_cast<Renderers::Square> (it[0]);
				std::string shader_name = Constants::UNTEXTURED_SHADER;
				if (mode == GL_LINE)
				{
					shader_name = Constants::HOVER_SHADER;
				}
				if (m_shader_service && s)
				{
					glBindVertexArray(s->GetVAO());
					if (glIsVertexArray(s->GetVAO()) == GL_TRUE)
					{
						GLuint program_id = m_shader_service->GetProgramId(shader_name);
						glUseProgram(program_id);
						Component::Transformer::PutIntoShader(s, m_shader_service, shader_name);
						glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
						glUseProgram(0);
						glBindVertexArray(0);
					}
				}
				s.reset();
			}
			break;
			case Enums::RendererType::NONE:
			default:
				break;
			}
			
		}
	}
	void Canvas::TransformRenderers(std::vector<std::shared_ptr<Renderers::IRenderer>> renderers)
	{
		for (std::vector<std::shared_ptr<Renderers::IRenderer>>::iterator it = renderers.begin(); it != renderers.end(); it++)
		{
			Component::Transformer::ReinitModelMat(it[0]);
			Component::Transformer::Move(it[0]);
			Component::Transformer::Resize(it[0]);
		}
	}
	void Canvas::DragRenderers(std::vector<std::shared_ptr<Renderers::IRenderer>> renderers)
	{
		if (m_draggable_component)
		{
			for (std::vector<std::shared_ptr<Renderers::IRenderer>>::iterator it = renderers.begin(); it != renderers.end(); it++)
			{
				m_draggable_component->OnSelectRenderer(it[0]);
				m_draggable_component->OnUnSelectRenderer(it[0]);
			}

			m_draggable_component->OnSelectRenderers(renderers);
		}
		
	}
}