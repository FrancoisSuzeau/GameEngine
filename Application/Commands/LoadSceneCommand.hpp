/******************************************************************************************************************************************/
// File : LoadSceneCommand.hpp
// Purpose : A save scene command
/******************************************************************************************************************************************/
#ifndef LOADSCENECOMMAND_H
#define LOADSCENECOMMAND_H

#include "ICommand.hpp"
#include "IRenderer.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "../Services/Services.hpp"

#include <memory>
#include <vector>

namespace Commands {

	class LoadSceneCommand : public ICommand
	{
	public:
		LoadSceneCommand(std::string const filename);
		
		void Execute() override;
	private:

		std::shared_ptr<Services::JsonService> m_json_service;
		std::shared_ptr<Services::StateService> m_state_service;
		
	};
}

#endif