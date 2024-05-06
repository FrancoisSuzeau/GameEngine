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
#include "../Services/StateService.hpp"
#include "../Services/LoaderService.hpp"

#include <memory>
#include <vector>

namespace Commands {

	class LoadSceneCommand : public ICommand
	{
	public:
		LoadSceneCommand(std::string const filename);
		~LoadSceneCommand();
		void Execute() override;
	private:

		std::shared_ptr<Services::LoaderService> m_loader_service;
		std::shared_ptr<Services::StateService> m_state_service;
		
	};
}

#endif