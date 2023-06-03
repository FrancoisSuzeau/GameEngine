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

namespace Commands {

	class ExitCommand : public ICommand
	{
	public:
		ExitCommand(std::shared_ptr<Starting::Application> app_ptr);
		void Execute() override;
	private:
		std::shared_ptr<Starting::Application> m_app_ptr;

	};
}

#endif