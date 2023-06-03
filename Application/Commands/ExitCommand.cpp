/******************************************************************************************************************************************/
// File : ExitCommand.cpp
// Purpose : Implementing the exit command
/******************************************************************************************************************************************/
#include "ExitCommand.hpp"

using namespace Commands;

ExitCommand::ExitCommand(std::shared_ptr<Starting::Application> app_ptr)
{
	m_app_ptr = app_ptr;

}

void ExitCommand::Execute()
{
	this->m_app_ptr->EndingBuilders();
}
