/******************************************************************************************************************************************/
// File : AddNewComponentCommand.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "AddNewComponentCommand.hpp"

namespace Commands
{
	AddNewComponentCommmand::AddNewComponentCommmand(Enums::RendererType component_type) : m_component_type(component_type)
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

	AddNewComponentCommmand::~AddNewComponentCommmand()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}

		if (m_camera_service)
		{
			m_camera_service.reset();
		}
	}

	void AddNewComponentCommmand::Execute()
	{
		if (m_camera_service)
		{
			glm::vec3 position = m_camera_service->GetPos() + m_camera_service->GetTarget();
			switch (m_component_type)
			{
			case Enums::RendererType::TRIANGLE:
				this->MakeNewComponent(std::make_shared<Component::ComponentBase>(position, glm::vec3(0.2f), m_component_type ,glm::vec4(1.f)));
				SQ_APP_TRACE("New triangle added");
				break;
			case Enums::RendererType::SQUARE:
				this->MakeNewComponent(std::make_shared<Component::ComponentBase>(position, glm::vec3(0.2f), m_component_type, glm::vec4(1.f)));
				SQ_APP_TRACE("New square added");
				break;
			case Enums::RendererType::SKYBOX:
			case Enums::RendererType::GRID:
				SQ_APP_TRACE("This component type cannot be added to the scene");
				break;
			case Enums::RendererType::NONE:
			default:
				SQ_APP_TRACE("Component type not known. Cannot add it");
				break;
			}
		}

	}
	void AddNewComponentCommmand::MakeNewComponent(std::shared_ptr<Component::IComponent> new_component_to_make)
	{
		if (m_state_service)
		{
			new_component_to_make->SetSelected(true);
			m_state_service->addComponent(new_component_to_make);
			m_state_service->setSelectedComponent();
			new_component_to_make.reset();
		}
	}
}