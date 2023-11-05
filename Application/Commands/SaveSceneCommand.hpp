/******************************************************************************************************************************************/
// File : SaveSceneCommand.hpp
// Purpose : A save scene command
/******************************************************************************************************************************************/
#ifndef SAVESCENECOMMAND_H
#define SAVESCENECOMMAND_H

#include "ICommand.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "../Services/Services.hpp"

#include <memory>

namespace Commands {

	class SaveSceneCommand : public ICommand
	{
	public:
		SaveSceneCommand(std::string const filename);
		SaveSceneCommand();
		void Execute() override;
	private:
		std::shared_ptr<Services::JsonService> m_json_service;
		std::shared_ptr<Services::StateService> m_state_service;
	};
}

#endif