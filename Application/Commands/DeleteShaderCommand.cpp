/******************************************************************************************************************************************/
// File : DeleteShaderCommand.cpp
// Purpose : Implementing the delete shader command
/******************************************************************************************************************************************/
#include "DeleteShaderCommand.hpp"

using namespace Commands;

DeleteShaderCommand::DeleteShaderCommand(std::string const shader_name) : m_shader_name(shader_name)
{
	m_shader_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::ShaderService>();
	if (!m_shader_service)
	{
		SQ_APP_ERROR("Class {} in function {} : Shader service is not referenced yet", __FILE__, __FUNCTION__);
	}
}

void DeleteShaderCommand::Execute()
{
	if (m_shader_service)
	{
		SQ_APP_INFO("New shader command is called");
		m_shader_service->DeleteShader(m_shader_name);
		m_shader_service.reset();
	}
	
}
