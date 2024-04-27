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
		ModifyConfigsCommand(float const grid_scaling_trigger, Enums::ConfigsModifier configs_modifier);
		ModifyConfigsCommand(int const grid_scaling_ratio, Enums::ConfigsModifier configs_modifier);
		ModifyConfigsCommand(bool const render_grid, Enums::ConfigsModifier configs_modifier);
		~ModifyConfigsCommand();
		void Execute() override;
	private:

		std::shared_ptr<Services::ConfigEntity> m_configs;
		std::string const m_filename;
		float m_grid_scaling_trigger;
		int m_grid_scaling_ratio;
		bool m_render_grid;
		Enums::ConfigsModifier m_configs_modifier;
		std::shared_ptr<Services::StateService> m_state_service;

	};
}

#endif