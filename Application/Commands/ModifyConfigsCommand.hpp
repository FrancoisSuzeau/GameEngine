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
		
		ModifyConfigsCommand(std::string const value, Enums::ConfigsModifier configs_modifier);
		ModifyConfigsCommand(float const value, Enums::ConfigsModifier configs_modifier);
		ModifyConfigsCommand(int const value, Enums::ConfigsModifier configs_modifier);
		ModifyConfigsCommand(bool const value, Enums::ConfigsModifier configs_modifier);
		~ModifyConfigsCommand();
		void Execute() override;
	private:

		std::shared_ptr<Services::ConfigEntity> m_configs;
		std::string const m_string_value;
		float m_float_value;
		int m_int_value;
		bool m_bool_value;
		Enums::ConfigsModifier m_configs_modifier;
		std::shared_ptr<Services::StateService> m_state_service;

	};
}

#endif