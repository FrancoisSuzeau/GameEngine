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

		for (std::map<Enums::RendererType, std::shared_ptr<Renderers::IRenderer>>::iterator it = m_components.begin(); it != m_components.end(); it++)
		{
			if (it->second)
			{
				it->second->Clean();
				it->second.reset();
			}
		}

		m_components.clear();
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

			switch (it[0]->GetType())
			{
			case Enums::RendererType::SQUARE:
			case Enums::RendererType::TRIANGLE:
			{
				std::shared_ptr<Component::ComponentBase> component = std::dynamic_pointer_cast<Component::ComponentBase> (it[0]);

				if (component && m_shader_service && (m_components.contains(component->GetType()) && m_components.at(component->GetType())))
				{
					std::string shader_name = Constants::UNTEXTURED_SHADER;
					if (mode == GL_LINE)
					{
						shader_name = Constants::HOVER_SHADER;
					}

					glUseProgram(m_shader_service->GetProgramId(shader_name));
					Component::Transformer::PutIntoShader(component, m_shader_service, shader_name);
					m_components.at(component->GetType())->Draw();
					glUseProgram(0);

					component.reset();
				}
			}
			break;
			case Enums::RendererType::SQUARE_TEXTURED:
				break;
			default:
				break;
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
	void Canvas::ConstructRenderer()
	{
		m_components.insert_or_assign(Enums::RendererType::TRIANGLE, std::make_shared<Renderers::Triangle>());
		m_components.insert_or_assign(Enums::RendererType::SQUARE, std::make_shared<Renderers::Square>());
		for (std::map<Enums::RendererType, std::shared_ptr<Renderers::IRenderer>>::iterator it = m_components.begin(); it != m_components.end(); it++)
		{
			if (it->second)
			{
				it->second->Construct();
			}
		}
	}
}