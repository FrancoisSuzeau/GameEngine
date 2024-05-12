/******************************************************************************************************************************************/
// File : Canvas.cpp
// Purpose : Implementing the GUI view app style editor
/******************************************************************************************************************************************/

#include "Canvas.hpp"

namespace Views
{
	Canvas::Canvas(std::shared_ptr<ViewModels::IViewModel> parent)
	{
		m_parent_view_model = parent;
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

			m_state_service = container->GetReference<Services::StateService>();
			if (!m_runtime_service)
			{
				SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
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

		for (std::map<Enums::RendererType, std::unique_ptr<Renderers::IRenderer>>::iterator it = m_renderers.begin(); it != m_renderers.end(); it++)
		{
			if (it->second)
			{
				it->second->Clean();
				it->second.reset();
			}
		}

		m_renderers.clear();

		if (m_parent_view_model)
		{
			m_parent_view_model.reset();
		}
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
			case Enums::RendererType::CUBE:
			case Enums::RendererType::SPHERE:
			{
				std::shared_ptr<Component::ComponentBase> component = std::dynamic_pointer_cast<Component::ComponentBase> (it[0]);

				if (component && m_shader_service && (m_renderers.contains(component->GetType()) && m_renderers.at(component->GetType())))
				{
					std::string shader_name = m_state_service->getPass() == Enums::FramebufferType::DEPTHBUFFER ? Constants::DEPTH_SHADER : Constants::UNTEXTURED_SHADER;
					if (m_runtime_service && m_runtime_service->IsRenderingLine() && m_state_service->getPass() != Enums::FramebufferType::DEPTHBUFFER)
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
			case Enums::RendererType::CUBE_TEXTURED:
			case Enums::RendererType::TRIANGLE_TEXTURED:
			case Enums::RendererType::SQUARE_TEXTURED:
			{
				std::shared_ptr<Component::TexturedComponent> component = std::dynamic_pointer_cast<Component::TexturedComponent> (it[0]);

				if (component && m_shader_service && (m_renderers.contains(component->GetType()) && m_renderers.at(component->GetType())))
				{
					std::string shader_name = m_state_service->getPass() == Enums::FramebufferType::DEPTHBUFFER ? Constants::DEPTH_SHADER : Constants::TEXTURED_SHADER;
					if (m_runtime_service && m_runtime_service->IsRenderingLine() && m_state_service->getPass() != Enums::FramebufferType::DEPTHBUFFER)
					{
						shader_name = Constants::HOVER_SHADER;
					}
					if (m_shader_service)
					{
						m_shader_service->BindShaderProgram(shader_name);
						Component::Transformer::PutIntoShader(component, m_shader_service, shader_name);
						m_renderers.at(component->GetType())->Draw(component->GetTextureId());
						m_shader_service->UnbindShaderProgram();
					}

					component.reset();
				}
			}
				break;
			default:
				break;
			}
		}
	}
	void Canvas::TransformComponents(std::vector<std::shared_ptr<Component::IComponent>> components)
	{
		for (std::vector<std::shared_ptr<Component::IComponent>>::iterator it = components.begin(); it != components.end(); it++)
		{
			Component::Transformer::ReinitModelMat(it[0]);
			Component::Transformer::Move(it[0]);
			Component::Transformer::Resize(it[0]);
		}
	}
	void Canvas::DragComponents(std::vector<std::shared_ptr<Component::IComponent>> components)
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
		m_renderers.insert_or_assign(Enums::RendererType::CUBE, std::make_unique<Renderers::Cube>());
		m_renderers.insert_or_assign(Enums::RendererType::CUBE_TEXTURED, std::make_unique<Renderers::CubeTextured>());
		m_renderers.insert_or_assign(Enums::RendererType::TRIANGLE_TEXTURED, std::make_unique<Renderers::TriangleTextured>());
		m_renderers.insert_or_assign(Enums::RendererType::SQUARE_TEXTURED, std::make_unique<Renderers::SquareTextured>());
		m_renderers.insert_or_assign(Enums::RendererType::SPHERE, std::make_unique<Renderers::Sphere>(1.f, 70, 70));
		
		for (std::map<Enums::RendererType, std::unique_ptr<Renderers::IRenderer>>::iterator it = m_renderers.begin(); it != m_renderers.end(); it++)
		{
			if (it->second)
			{
				it->second->Construct();
			}
		}
	}
}