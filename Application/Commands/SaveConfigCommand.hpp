/******************************************************************************************************************************************/
// File : SaveConfigCommand.hpp
// Purpose : A save scene command
/******************************************************************************************************************************************/
#ifndef SAVECONFIGCOMMAND_H
#define SAVECONFIGCOMMAND_H

#include "ICommand.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "../Services/Services.hpp"

#include <memory>

namespace Commands {

	class SaveConfigCommand : public ICommand
	{
	public:
		SaveConfigCommand();
		~SaveConfigCommand();
		void Execute() override;
	private:
		std::shared_ptr<Services::LoaderService> m_loader_service;
		std::shared_ptr<Services::StateService> m_state_service;
	};
}

#endif