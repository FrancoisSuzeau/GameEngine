/******************************************************************************************************************************************/
// File : ExitCommand.cpp
// Purpose : Implementing the exit command
/******************************************************************************************************************************************/
#include "ExitCommand.hpp"

namespace Commands
{
	ExitCommand::ExitCommand()
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}

	void ExitCommand::Execute()
	{
		if (m_state_service)
		{
			SQ_APP_INFO("Exit command is called");
			this->m_state_service->setExit(true);
			m_state_service.reset();
		}


	}
}
