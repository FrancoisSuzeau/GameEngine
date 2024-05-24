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
		this->GetServices();
	}

	ModifyConfigsCommand::ModifyConfigsCommand(bool const value, Enums::ConfigsModifier configs_modifier) : m_int_value(0), m_float_value(0.f),
		m_string_value(""), m_configs_modifier(configs_modifier), m_bool_value(value)
	{
		this->GetServices();
	}

	ModifyConfigsCommand::ModifyConfigsCommand(Enums::ConfigsModifier configs_modifier) : m_int_value(0), m_float_value(0.f),
		m_string_value(""), m_configs_modifier(configs_modifier), m_bool_value(false)
	{
		this->GetServices();
	}

	ModifyConfigsCommand::ModifyConfigsCommand(float const value, Enums::ConfigsModifier configs_modifier) : m_string_value(""), m_int_value(0),
		m_float_value(value), m_configs_modifier(configs_modifier), m_bool_value(false)
	{
		this->GetServices();
	}

	ModifyConfigsCommand::ModifyConfigsCommand(int const value, Enums::ConfigsModifier configs_modifier) : m_string_value(""), m_float_value(0.f),
		m_int_value(value), m_configs_modifier(configs_modifier), m_bool_value(false)
	{
		this->GetServices();
	}

	ModifyConfigsCommand::~ModifyConfigsCommand()
	{

		if (m_state_service)
		{
			m_state_service.reset();
		}
	}

	void ModifyConfigsCommand::Execute()
	{
		if (m_state_service && m_state_service->getConfigs() && m_framebuffer_service)
		{
			switch (m_configs_modifier)
			{
			case Enums::ConfigsModifier::ADDFILE:
				m_state_service->getConfigs()->AddCreatedScene(m_string_value);
				break;
			case Enums::ConfigsModifier::CHANGERATIO:
				m_state_service->getConfigs()->SetGridSpacingRatio(m_int_value);
				break;
			case Enums::ConfigsModifier::CHANGETRIGGER:
				m_state_service->getConfigs()->SetGridScalingTrigger(m_float_value);
				break;
			case Enums::ConfigsModifier::RENDERGRID:
				m_state_service->getConfigs()->SetRenderGrid(m_bool_value);
				break;
			case Enums::ConfigsModifier::BLOOMSTRENGTH:
				m_state_service->getConfigs()->SetBloomStrength(m_int_value);
				break;
			case Enums::ConfigsModifier::BLOOM:
				m_state_service->getConfigs()->SetBloom(m_bool_value);
				break;
			case Enums::ConfigsModifier::RENDERDEBUG:
				m_state_service->getConfigs()->SetRenderDebug(m_bool_value);
				break;
			case::Enums::ConfigsModifier::RENDERSKYBOX:
				m_state_service->getConfigs()->SetRenderSkybox(m_bool_value);
				break;
			case::Enums::ConfigsModifier::SHADOW:
				m_state_service->getConfigs()->SetDepth(m_bool_value);
				break;
			case::Enums::ConfigsModifier::ANTIALIASINGACIVE:
				m_framebuffer_service->ClearFramebuffer();
				m_bool_value ? m_framebuffer_service->BuildMultiSampleFrameBuffer() : m_framebuffer_service->BuildNormalFrameBuffer();
				m_state_service->getConfigs()->SetMutliSample(m_bool_value);
				break;
			case::Enums::ConfigsModifier::DEFAULT:
				m_state_service->getConfigs()->SetToDefault();
				break;
			default:
				break;
			}
		}
	}
	void ModifyConfigsCommand::GetServices()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_state_service = container->GetReference<Services::StateService>();
			if (!m_state_service)
			{
				SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_framebuffer_service = container->GetReference<Services::FramebufferService>();
			if (!m_framebuffer_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Framebuffer service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
	}
}