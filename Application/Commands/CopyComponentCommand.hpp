/******************************************************************************************************************************************/
// File : CopyComponentCommand.hpp
// Purpose : A save scene command
/******************************************************************************************************************************************/
#ifndef COPYCOMPONENTCOMMAND_H
#define COPYCOMPONENTCOMMAND_H

#include "ICommand.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "../Services/Services.hpp"

#include <memory>

namespace Commands {

	class CopyComponentCommand : public ICommand
	{
	public:
		CopyComponentCommand(std::shared_ptr<Renderers::IRenderer> renderer_to_copy);
		~CopyComponentCommand();
		void Execute() override;
	private:
		std::shared_ptr<Services::StateService> m_state_service;
		std::shared_ptr<Renderers::IRenderer> m_renderer_to_copy;
	};
}

#endif