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

	void Canvas::Render(std::vector<std::shared_ptr<Component::IComponent>> renderers, GLenum const mode, float const line_width)
	{
		for (std::vector<std::shared_ptr<Component::IComponent>>::iterator it = renderers.begin(); it != renderers.end(); it++)
		{
			if (m_draggable_component)
			{
				m_draggable_component->OnHoverRenderer(it[0]);
			}
			glLineWidth(line_width);
			glPolygonMode(GL_FRONT_AND_BACK, mode);

			std::shared_ptr<Component::ComponentBase> component = std::dynamic_pointer_cast<Component::ComponentBase> (it[0]);
			
			if (component && m_shader_service)
			{
				switch (component->GetType())
				{
				case Enums::RendererType::TRIANGLE:
				{
					std::string shader_name = Constants::UNTEXTURED_SHADER;
					if (mode == GL_LINE)
					{
						shader_name = Constants::HOVER_SHADER;
					}
					/*glBindVertexArray(t->GetVAO());
						if (glIsVertexArray(t->GetVAO()) == GL_TRUE)
						{
							GLuint program_id = m_shader_service->GetProgramId(shader_name);
							glUseProgram(program_id);
							Component::Transformer::PutIntoShader(t, m_shader_service, shader_name);
							glDrawArrays(GL_TRIANGLES, 0, 3);
							glUseProgram(0);
							glBindVertexArray(0);
						}*/
				}
				break;
				case Enums::RendererType::SQUARE:
				{
					std::string shader_name = Constants::UNTEXTURED_SHADER;
					if (mode == GL_LINE)
					{
						shader_name = Constants::HOVER_SHADER;
					}
					/*glBindVertexArray(s->GetVAO());
						if (glIsVertexArray(s->GetVAO()) == GL_TRUE)
						{
							GLuint program_id = m_shader_service->GetProgramId(shader_name);
							glUseProgram(program_id);
							Component::Transformer::PutIntoShader(s, m_shader_service, shader_name);
							glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
							glUseProgram(0);
							glBindVertexArray(0);
						}*/
				}
				break;
				case Enums::RendererType::NONE:
				case::Enums::RendererType::GRID:
				case Enums::RendererType::SKYBOX:
				case Enums::RendererType::SQUARE_TEXTURED:
				default:
					break;
				}

				component.reset();
			}
			
		}
	}
	void Canvas::TransformRenderers(std::vector<std::shared_ptr<Component::IComponent>> renderers)
	{
		for (std::vector<std::shared_ptr<Component::IComponent>>::iterator it = renderers.begin(); it != renderers.end(); it++)
		{
			Component::Transformer::ReinitModelMat(it[0]);
			Component::Transformer::Move(it[0]);
			Component::Transformer::Resize(it[0]);
		}
	}
	void Canvas::DragRenderers(std::vector<std::shared_ptr<Component::IComponent>> renderers)
	{
		if (m_draggable_component)
		{
			for (std::vector<std::shared_ptr<Component::IComponent>>::iterator it = renderers.begin(); it != renderers.end(); it++)
			{
				m_draggable_component->OnSelectRenderer(it[0]);
				m_draggable_component->OnUnSelectRenderer(it[0]);
			}

			m_draggable_component->OnSelectRenderers(renderers);
		}
		
	}
}