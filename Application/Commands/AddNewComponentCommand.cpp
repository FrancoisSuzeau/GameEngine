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
		}
	}

	void AddNewComponentCommmand::Execute()
	{
		switch (m_component_type)
		{
		case Enums::RendererType::TRIANGLE:
			this->MakeNewComponent(std::make_shared<Renderers::Triangle>(glm::vec3(0.f), glm::vec4(1.f), glm::vec3(0.2f)));
			SQ_APP_TRACE("New triangle added");
			break;
		case Enums::RendererType::SQUARE:
			this->MakeNewComponent(std::make_shared<Renderers::Square>(glm::vec3(0.f), glm::vec4(1.f), glm::vec3(0.2f)));
			SQ_APP_TRACE("New square added");
			break;
		case Enums::RendererType::NONE:
		default:
			SQ_APP_TRACE("Component type not known. Cannot add it");
			break;
		}

	}
	void AddNewComponentCommmand::MakeNewComponent(std::shared_ptr<Renderers::IRenderer> new_component_to_make)
	{
		if (m_state_service)
		{
			new_component_to_make->Construct();
			new_component_to_make->SetSelected(true);
			m_state_service->addRenderer(new_component_to_make);
			m_state_service->setSelectedRenderer();
		}
	}
}