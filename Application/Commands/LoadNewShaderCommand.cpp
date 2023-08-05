/******************************************************************************************************************************************/
// File : LoadNewShaderCommand.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "LoadNewShaderCommand.hpp"

using namespace Commands;

LoadNewShaderCommand::LoadNewShaderCommand(std::string const shader_name, Enums::ShaderType const shader_type) : m_shader_name(shader_name),
m_shader_type(shader_type)
{
	m_shader_service = IoC::Container::Container::GetInstanceContainer()->make<Services::ShaderService>();
}

void LoadNewShaderCommand::Execute()
{
	SQ_APP_TRACE("New shader command is called");
	m_shader_service->LoadShader(m_shader_name, m_shader_type);
	
}
