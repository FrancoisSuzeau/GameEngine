/******************************************************************************************************************************************/
// File : CopyComponentCommand.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "CopyComponentCommand.hpp"

namespace Commands
{
	CopyComponentCommand::CopyComponentCommand(std::shared_ptr<Renderers::IRenderer> renderer_to_copy) : m_renderer_to_copy(renderer_to_copy)
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
				this->MakeNewComponent(std::make_shared<Renderers::Triangle>(*std::dynamic_pointer_cast<Renderers::Triangle>(m_renderer_to_copy)));
				SQ_APP_TRACE("Component copied !");
				break;
			case Enums::RendererType::SQUARE:
				this->MakeNewComponent(std::make_shared<Renderers::Square>(*std::dynamic_pointer_cast<Renderers::Square>(m_renderer_to_copy)));
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
	void CopyComponentCommand::MakeNewComponent(std::shared_ptr<Renderers::IRenderer> new_component_to_make)
	{
		if (m_state_service && m_renderer_to_copy && m_camera_service)
		{
			glm::vec3 position = m_camera_service->GetPos() + m_camera_service->GetTarget();
			position.z = -1.f;
			
			m_renderer_to_copy->SetSelected(false);
			new_component_to_make->SetPosition(position);
			new_component_to_make->SetSelected(true);
			m_state_service->addRenderer(new_component_to_make);
			m_state_service->setSelectedRenderer();
		}
	}
}