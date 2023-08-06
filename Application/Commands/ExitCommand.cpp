/******************************************************************************************************************************************/
// File : ExitCommand.cpp
// Purpose : Implementing the exit command
/******************************************************************************************************************************************/
#include "ExitCommand.hpp"

using namespace Commands;

ExitCommand::ExitCommand()
{
	m_state_service = IoC::Container::Container::GetInstanceContainer()->make<Services::StateService>();
}

void ExitCommand::Execute()
{
	if (m_state_service)
	{
		SQ_APP_INFO("Exit command is called");
		this->m_state_service->setExit(true);
	}
	
	
}
