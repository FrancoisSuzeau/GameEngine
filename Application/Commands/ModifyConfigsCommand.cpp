/******************************************************************************************************************************************/
// File : ModifyConfigsCommand.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "ModifyConfigsCommand.hpp"

namespace Commands

{

	ModifyConfigsCommand::ModifyConfigsCommand(std::string const filename, Enums::ConfigsModifier configs_modifier) : m_filename(filename), m_configs_modifier(configs_modifier)
	{
		std::shared_ptr<Services::StateService> m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
		else
		{
			m_configs = m_state_service->getConfigs();
		}
	}

	ModifyConfigsCommand::~ModifyConfigsCommand()
	{
		if (m_configs)
		{
			m_configs.reset();
		}
	}

	void ModifyConfigsCommand::Execute()
	{
		if (m_configs)
		{
			switch (m_configs_modifier)
			{
			case Enums::ADDFILE:
				m_configs->AddCreatedScene(m_filename);
				break;
			default:
				break;
			}
		}
	}
}