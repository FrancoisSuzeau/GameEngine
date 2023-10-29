/******************************************************************************************************************************************/
// File : SaveConfigCommand.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "SaveConfigCommand.hpp"

namespace Commands
{
	SaveConfigCommand::SaveConfigCommand()
	{
		m_json_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::JsonService>();
		if (!m_json_service)
		{
			SQ_APP_ERROR("Class {} in function {} : Json service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}

	void SaveConfigCommand::Execute()
	{
		if (m_json_service)
		{
			SQ_APP_INFO("Save scene command is called");

			m_json_service->SaveConfigs();
			m_json_service.reset();
		}
	}
}


