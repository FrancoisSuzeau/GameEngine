/******************************************************************************************************************************************/
// File : ModifyConfigsCommand.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "ModifyConfigsCommand.hpp"

namespace Commands

{

	ModifyConfigsCommand::ModifyConfigsCommand(std::string const filename, Enums::ConfigsModifier configs_modifier) : m_filename(filename), m_configs_modifier(configs_modifier)
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
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

		if (m_state_service)
		{
			m_state_service.reset();
		}

	}

	void ModifyConfigsCommand::Execute()
	{
		if (m_configs && m_state_service)
		{
			switch (m_configs_modifier)
			{
			case Enums::ADDFILE:
				m_configs->AddCreatedScene(m_filename);
				break;
			default:
				break;
			}

			//m_state_service->setConfigs(std::move(m_configs));
		}
	}
}