/******************************************************************************************************************************************/
// File : ModifyConfigsCommand.hpp
// Purpose : A save scene command
/******************************************************************************************************************************************/
#ifndef MODIFYCONFIGCOMMAND_H
#define MODIFYCONFIGCOMMAND_H

#include "ICommand.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "../Services/StateService.hpp"
#include "../Services/LoaderService.hpp"
#include "../Services/RunTimeService.hpp"

#include <memory>

namespace Commands {

	class ModifyConfigsCommand : public ICommand
	{
	public:
		
		ModifyConfigsCommand(std::string const value, Enums::ConfigsModifier configs_modifier);
		ModifyConfigsCommand(float const value, Enums::ConfigsModifier configs_modifier);
		ModifyConfigsCommand(int const value, Enums::ConfigsModifier configs_modifier);
		ModifyConfigsCommand(bool const value, Enums::ConfigsModifier configs_modifier);
		ModifyConfigsCommand(Enums::ConfigsModifier configs_modifier);
		~ModifyConfigsCommand();
		void Execute() override;
	private:

		void GetServices();
		std::string const m_string_value;
		float m_float_value;
		int m_int_value;
		bool m_bool_value;
		Enums::ConfigsModifier m_configs_modifier;
		std::shared_ptr<Services::StateService> m_state_service;
		std::shared_ptr<Services::LoaderService> m_loader_service;
		std::shared_ptr < Services::RunTimeService> m_runtime_service;

	};
}

#endif