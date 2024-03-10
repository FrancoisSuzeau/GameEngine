/******************************************************************************************************************************************/
// File : ExitCommand.hpp
// Purpose : An exit command
/******************************************************************************************************************************************/
#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H

#include "ICommand.hpp"

#include <memory>
#include "../Services/StateService.hpp"
#include "Container/Container.hpp"

namespace Commands {

	class ExitCommand : public ICommand
	{
	public:
		ExitCommand(std::function<void(bool)> callback);
		~ExitCommand();
		void Execute() override;
	private:
		std::function<void(bool)> m_callback;
	};
}

#endif