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
		void Execute() override;
	private:
		std::shared_ptr<Services::JsonService> m_json_service;

	};
}

#endif