/******************************************************************************************************************************************/
// File : LoadNewShaderCommand.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "LoadNewShaderCommand.hpp"

namespace Commands
{
	LoadNewShaderCommand::LoadNewShaderCommand(std::string const shader_name, Enums::ShaderType const shader_type) : m_shader_name(shader_name),
		m_shader_type(shader_type)
	{
		m_shader_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::ShaderService>();
		if (!m_shader_service)
		{
			SQ_APP_ERROR("Class {} in function {} : Shader service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}

	LoadNewShaderCommand::~LoadNewShaderCommand()
	{
		if (m_shader_service)
		{
			m_shader_service.reset();
		}
	}

	void LoadNewShaderCommand::Execute()
	{
		if (m_shader_service)
		{
			SQ_APP_INFO("New shader command is called");
			m_shader_service->LoadShader(m_shader_name, m_shader_type);
			m_shader_service.reset();
		}

	}
}
