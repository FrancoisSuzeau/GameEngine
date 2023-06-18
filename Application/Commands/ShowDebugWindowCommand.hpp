/******************************************************************************************************************************************/
// File : ShowDebugWindowCommand.hpp
// Purpose : An exit command
/******************************************************************************************************************************************/
#ifndef SHDEBUGCOMMAND_H
#define SHDEBUGCOMMAND_H

#include "ICommand.hpp"

#include <memory>
#include "../Services/StateService.hpp"

namespace Commands {

	class ShowDebugWindowCommand : public ICommand
	{
	public:
		ShowDebugWindowCommand(std::shared_ptr<Services::StateService> state_service);
		void Execute() override;
	private:
		std::shared_ptr<Services::StateService> m_state_service;

	};
}

#endif