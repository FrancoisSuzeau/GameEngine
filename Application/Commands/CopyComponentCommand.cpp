/******************************************************************************************************************************************/
// File : CopyComponentCommand.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "CopyComponentCommand.hpp"

namespace Commands
{
	CopyComponentCommand::CopyComponentCommand(std::shared_ptr<Component::IComponent> renderer_to_copy) : m_renderer_to_copy(renderer_to_copy)
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_state_service = container->GetReference<Services::StateService>();
			if (!m_state_service)
			{
				SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_camera_service = container->GetReference<Services::CameraService>();
			if (!m_camera_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Camera service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
	}

	CopyComponentCommand::~CopyComponentCommand()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}

		if (m_renderer_to_copy)
		{
			m_renderer_to_copy.reset();
		}

		if (m_camera_service)
		{
			m_camera_service.reset();
		}
	}

	void CopyComponentCommand::Execute()
	{
		if (m_state_service && m_renderer_to_copy)
		{
			switch (m_renderer_to_copy->GetType())
			{
			case Enums::RendererType::TRIANGLE:
			case Enums::RendererType::SQUARE:
			case Enums::RendererType::CUBE:
			case Enums::RendererType::SPHERE:
				this->MakeNewComponent(std::make_shared<Component::ComponentBase>(*std::dynamic_pointer_cast<Component::ComponentBase>(m_renderer_to_copy)));
				SQ_APP_TRACE("Component copied !");
				break;
			case Enums::RendererType::CUBE_TEXTURED:
			case Enums::RendererType::SQUARE_TEXTURED:
			case Enums::RendererType::TRIANGLE_TEXTURED:
			case Enums::RendererType::SPHERE_TEXTURED:
				this->MakeNewComponent(std::make_shared<Component::TexturedComponent>(*std::dynamic_pointer_cast<Component::TexturedComponent>(m_renderer_to_copy)));
				SQ_APP_TRACE("Component copied !");
				break;
			case Enums::RendererType::SKYBOX:
			case Enums::RendererType::GRID:
			case Enums::RendererType::NONE:
			default:
				break;
			}
			
		}
	}
	void CopyComponentCommand::MakeNewComponent(std::shared_ptr<Component::IComponent> new_component_to_make)
	{
		if (m_state_service && m_renderer_to_copy && m_camera_service)
		{
			glm::vec3 position = m_camera_service->GetPos() + m_camera_service->GetTarget();
			
			m_renderer_to_copy->SetSelected(false);
			new_component_to_make->SetPosition(position);
			new_component_to_make->SetSelected(true);
			m_state_service->addComponent(new_component_to_make);
			m_state_service->setSelectedComponent();
			new_component_to_make.reset();
		}
	}
}