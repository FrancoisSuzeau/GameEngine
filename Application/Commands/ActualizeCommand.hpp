/******************************************************************************************************************************************/
// File : ActualizeCommand.hpp
// Purpose : A save scene command
/******************************************************************************************************************************************/
#ifndef ACTUALIZECOMMAND_H
#define ACTUALIZECOMMAND_H

#include "ICommand.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "../Services/Services.hpp"

#include <memory>

namespace Commands {

	class ActualizeCommand : public ICommand
	{
	public:
		ActualizeCommand();
		~ActualizeCommand();
		void Execute() override;
	private:
		std::shared_ptr<Services::StateService> m_state_service;
	};
}

#endif