/******************************************************************************************************************************************/
// File : ExitCommand.cpp
// Purpose : Implementing the exit command
/******************************************************************************************************************************************/
#include "ExitCommand.hpp"

namespace Commands
{
	ExitCommand::ExitCommand(std::function<void(bool)> callback) : m_callback(callback)
	{
		
	}

	void ExitCommand::Execute()
	{
		m_callback(true);
	}
}
