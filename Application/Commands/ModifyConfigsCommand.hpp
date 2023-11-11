/******************************************************************************************************************************************/
// File : ModifyConfigsCommand.hpp
// Purpose : A save scene command
/******************************************************************************************************************************************/
#ifndef MODIFYCONFIGCOMMAND_H
#define MODIFYCONFIGCOMMAND_H

#include "ICommand.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "../Services/Services.hpp"

#include <memory>

namespace Commands {

	class ModifyConfigsCommand : public ICommand
	{
	public:
		
		ModifyConfigsCommand(std::string const filename, Enums::ConfigsModifier configs_modifier);
		void Execute() override;
	private:

		std::shared_ptr<Services::ConfigEntity> m_configs;
		std::string const m_filename;
		Enums::ConfigsModifier m_configs_modifier;

	};
}

#endif