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
			SQ_APP_TRACE("New triangle added");
			break;
		case Enums::RendererType::SQUARE:
			SQ_APP_TRACE("New square added");
			break;
		case Enums::RendererType::NONE:
		default:
			SQ_APP_TRACE("Component type not known. Cannot add it");
			break;
		}

	}
}