/******************************************************************************************************************************************/
// File : SaveConfigCommand.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "SaveConfigCommand.hpp"

namespace Commands
{
	SaveConfigCommand::SaveConfigCommand() 
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_state_service = container->GetReference<Services::StateService>();
			if (!m_state_service)
			{
				SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_json_service = container->GetReference<Services::JsonService>();
			if (!m_json_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Json service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
	}

	SaveConfigCommand::~SaveConfigCommand()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}

		if (m_json_service)
		{
			m_json_service.reset();
		}
	}

	void SaveConfigCommand::Execute()
	{
		if (m_json_service && m_state_service)
		{
			m_json_service->SaveConfigs(m_state_service->getConfigs());
			m_state_service.reset();
			m_json_service.reset();
		}
	}
}


