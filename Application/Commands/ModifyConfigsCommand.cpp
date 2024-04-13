/******************************************************************************************************************************************/
// File : ModifyConfigsCommand.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "ModifyConfigsCommand.hpp"

namespace Commands

{

	ModifyConfigsCommand::ModifyConfigsCommand(std::string const filename, Enums::ConfigsModifier configs_modifier) : m_grid_scaling_ratio(0), m_grid_scaling_trigger(0.f),
		m_filename(filename), m_configs_modifier(configs_modifier)
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

	ModifyConfigsCommand::ModifyConfigsCommand(float const grid_scaling_trigger, Enums::ConfigsModifier configs_modifier) : m_filename(""), m_grid_scaling_ratio(0),
		m_grid_scaling_trigger(grid_scaling_trigger), m_configs_modifier(configs_modifier)
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

	ModifyConfigsCommand::ModifyConfigsCommand(int const grid_scaling_ratio, Enums::ConfigsModifier configs_modifier) : m_filename(""), m_grid_scaling_trigger(0.f),
		m_grid_scaling_ratio(grid_scaling_ratio), m_configs_modifier(configs_modifier)
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
			case Enums::ConfigsModifier::ADDFILE:
				m_configs->AddCreatedScene(m_filename);
				break;
			case Enums::ConfigsModifier::CHANGERATIO:
				m_configs->SetGridScalingRatio(m_grid_scaling_ratio);
				break;
			case Enums::ConfigsModifier::CHANGETRIGGER:
				m_configs->SetGridScalingTrigger(m_grid_scaling_trigger);
				break;
			default:
				break;
			}
		}
	}
}