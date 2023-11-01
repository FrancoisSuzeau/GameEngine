/******************************************************************************************************************************************/
// File : LoadSceneCommand.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "LoadSceneCommand.hpp"

namespace Commands
{
	LoadSceneCommand::LoadSceneCommand(std::function<void()> callback) : m_callback(callback)
	{

	}

	void LoadSceneCommand::Execute()
	{
		if (m_callback)
		{
			m_callback();
		}
	}
}


