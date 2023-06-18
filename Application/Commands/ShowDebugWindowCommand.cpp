/******************************************************************************************************************************************/
// File : ShowDebugWindowCommand.cpp
// Purpose : Implementing the exit command
/******************************************************************************************************************************************/
#include "ShowDebugWindowCommand.hpp"

using namespace Commands;

ShowDebugWindowCommand::ShowDebugWindowCommand(std::shared_ptr<Services::StateService> state_services)
{
	m_state_service = state_services;
}

void ShowDebugWindowCommand::Execute()
{
	this->m_state_service->setDebugWindow(true);
}
