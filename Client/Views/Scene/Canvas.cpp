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

		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_shader_service = container->GetReference<Services::ShaderService>();
			if (!m_shader_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Shader service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_runtime_service = container->GetReference<Services::RunTimeService>();
			if (!m_runtime_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Runtime service is not referenced yet", __FILE__, __FUNCTION__);
			}
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

		if (m_runtime_service)
		{
			m_runtime_service.reset();
		}

		for (std::map<Enums::RendererType, std::unique_ptr<Renderers::IRenderer>>::iterator it = m_renderers.begin(); it != m_renderers.end(); it++)
		{
			if (it->second)
			{
				it->second->Clean();
				it->second.reset();
			}
		}

		m_renderers.clear();
	}

	void Canvas::Render(std::vector<std::shared_ptr<Component::IComponent>> components)
	{
		for (std::vector<std::shared_ptr<Component::IComponent>>::iterator it = components.begin(); it != components.end(); it++)
		{
			if (m_draggable_component)
			{
				m_draggable_component->OnHoverRenderer(it[0]);
			}

			switch (it[0]->GetType())
			{
			case Enums::RendererType::SQUARE:
			case Enums::RendererType::TRIANGLE:
			{
				std::shared_ptr<Component::ComponentBase> component = std::dynamic_pointer_cast<Component::ComponentBase> (it[0]);

				if (component && m_shader_service && (m_renderers.contains(component->GetType()) && m_renderers.at(component->GetType())))
				{
					std::string shader_name = Constants::UNTEXTURED_SHADER;
					if (m_runtime_service && m_runtime_service->IsRenderingLine())
					{
						shader_name = Constants::HOVER_SHADER;
					}
					if (m_shader_service)
					{
						m_shader_service->BindShaderProgram(shader_name);
						Component::Transformer::PutIntoShader(component, m_shader_service, shader_name);
						m_renderers.at(component->GetType())->Draw();
						m_shader_service->UnbindShaderProgram();
					}

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
	void Canvas::TransformRenderers(std::vector<std::shared_ptr<Component::IComponent>> components)
	{
		for (std::vector<std::shared_ptr<Component::IComponent>>::iterator it = components.begin(); it != components.end(); it++)
		{
			Component::Transformer::ReinitModelMat(it[0]);
			Component::Transformer::Move(it[0]);
			Component::Transformer::Resize(it[0]);
		}
	}
	void Canvas::DragRenderers(std::vector<std::shared_ptr<Component::IComponent>> components)
	{
		if (m_draggable_component)
		{
			for (std::vector<std::shared_ptr<Component::IComponent>>::iterator it = components.begin(); it != components.end(); it++)
			{
				m_draggable_component->OnSelectRenderer(it[0]);
				m_draggable_component->OnUnSelectRenderer(it[0]);
			}

			m_draggable_component->OnSelectRenderers(components);
		}

	}
	void Canvas::ConstructRenderer()
	{
		m_renderers.insert_or_assign(Enums::RendererType::TRIANGLE, std::make_unique<Renderers::Triangle>());
		m_renderers.insert_or_assign(Enums::RendererType::SQUARE, std::make_unique<Renderers::Square>());
		for (std::map<Enums::RendererType, std::unique_ptr<Renderers::IRenderer>>::iterator it = m_renderers.begin(); it != m_renderers.end(); it++)
		{
			if (it->second)
			{
				it->second->Construct();
			}
		}
	}
}