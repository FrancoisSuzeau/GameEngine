/******************************************************************************************************************************************/
// File : ExitCommand.hpp
// Purpose : An exit command
/******************************************************************************************************************************************/
#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H

#include "ICommand.hpp"
#include "../Application.hpp"
#include "../Application.cpp"
#include <memory>
#include "../Services/StateService.hpp"

namespace Commands {

	class ExitCommand : public ICommand
	{
	public:
		ExitCommand(std::shared_ptr<Services::StateService> state_service);
		void Execute() override;
	private:
		std::shared_ptr<Starting::Application> m_app_ptr;
		std::shared_ptr<Services::StateService> m_state_service;

	};
}

#endif