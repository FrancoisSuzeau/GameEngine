/******************************************************************************************************************************************/
// File : ExitCommand.cpp
// Purpose : Implementing the exit command
/******************************************************************************************************************************************/
#include "ExitCommand.hpp"

using namespace Commands;

ExitCommand::ExitCommand(std::shared_ptr<Services::StateService> state_services)
{
	m_state_service = state_services;
}

void ExitCommand::Execute()
{
	SQ_APP_TRACE("Exit command is called");
	this->m_state_service->setExit(true);
}
