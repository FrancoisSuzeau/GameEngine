/******************************************************************************************************************************************/
// File : ModifyConfigsCommand.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "ModifyConfigsCommand.hpp"

namespace Commands

{

	ModifyConfigsCommand::ModifyConfigsCommand(std::string const value, Enums::ConfigsModifier configs_modifier) : m_int_value(0), m_float_value(0.f),
		m_string_value(value), m_configs_modifier(configs_modifier), m_bool_value(false)
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

	ModifyConfigsCommand::ModifyConfigsCommand(bool const value, Enums::ConfigsModifier configs_modifier) : m_int_value(0), m_float_value(0.f),
		m_string_value(""), m_configs_modifier(configs_modifier), m_bool_value(value)
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

	ModifyConfigsCommand::ModifyConfigsCommand(float const value, Enums::ConfigsModifier configs_modifier) : m_string_value(""), m_int_value(0),
		m_float_value(value), m_configs_modifier(configs_modifier), m_bool_value(false)
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

	ModifyConfigsCommand::ModifyConfigsCommand(int const value, Enums::ConfigsModifier configs_modifier) : m_string_value(""), m_float_value(0.f),
		m_int_value(value), m_configs_modifier(configs_modifier), m_bool_value(false)
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
				m_configs->AddCreatedScene(m_string_value);
				break;
			case Enums::ConfigsModifier::CHANGERATIO:
				m_configs->SetGridSpacingRatio(m_int_value);
				break;
			case Enums::ConfigsModifier::CHANGETRIGGER:
				m_configs->SetGridScalingTrigger(m_float_value);
				break;
			case Enums::ConfigsModifier::RENDERGRID:
				m_configs->SetRenderGrid(m_bool_value);
				break;
			case Enums::ConfigsModifier::BLOOMSTRENGTH:
				m_configs->SetBloomStrength(m_int_value);
				break;
			case Enums::ConfigsModifier::BLOOM:
				m_configs->SetBloom(m_bool_value);
				break;
			default:
				break;
			}
		}
	}
}