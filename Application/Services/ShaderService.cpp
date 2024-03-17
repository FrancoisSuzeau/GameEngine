/******************************************************************************************************************************************/
// File : ShaderService.cpp
// Purpose : Implementing service shader
/******************************************************************************************************************************************/
#include "ShaderService.hpp"

namespace Services
{
	void ShaderService::Init()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_loader_service = container->GetReference<Services::LoaderService>();
			if (!m_loader_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Loader service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_opengl_service = container->GetReference<Services::OpenGLService>();
			if (!m_opengl_service)
			{
				SQ_APP_ERROR("Class {} in function {} : OpenGL service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
		
	}

	void ShaderService::DeInit()
	{
		for (std::map<std::string, GLuint>::iterator it = m_shader_program_map.begin(); it != m_shader_program_map.end(); it++)
		{
			this->DeleteShaderProgram(it->first);
		}

		m_shader_program_map.clear();

		if (m_loader_service)
		{
			m_loader_service.reset();
		}

		if (m_opengl_service)
		{
			m_opengl_service.reset();
		}
	}

	void ShaderService::AddShader(std::string shader_name, Enums::ShaderType shader_type)
	{
		if (!m_shader_program_map.contains(shader_name) && m_loader_service)
		{
			m_shader_program_map.insert_or_assign(shader_name, m_loader_service->LoadShader(shader_name, shader_type));
		}
		else
		{
			SQ_APP_ERROR("Class {} in function {} : Shader {} already exist", __FILE__, __FUNCTION__, shader_name);
		}
		
	}

	void ShaderService::BindShaderProgram(std::string const shader_name)
	{
		if (m_shader_program_map.contains(shader_name) && m_opengl_service)
		{
			m_opengl_service->bindProgram( m_shader_program_map.at(shader_name));
		}
	}

	void ShaderService::UnbindShaderProgram()
	{
		if (m_opengl_service)
		{
			m_opengl_service->bindProgram(0);
		}
	}
	 
	void ShaderService::setVec(std::string shader_name, std::string const location, glm::vec3 const& vec_to_add)
	{

		if (m_shader_program_map.contains(shader_name) && m_opengl_service)
		{
			m_opengl_service->setVec(m_shader_program_map.at(shader_name), location, vec_to_add);
		}
	}
	void ShaderService::setVec(std::string shader_name, std::string const location, glm::vec4 const& vec_to_add)
	{
		if (m_shader_program_map.contains(shader_name) && m_opengl_service)
		{
			m_opengl_service->setVec(m_shader_program_map.at(shader_name), location, vec_to_add);
		}
	}
	void ShaderService::setMat4(std::string shader_name, std::string const location, glm::mat4 const& matrice_to_add)
	{
		if (m_shader_program_map.contains(shader_name) && m_opengl_service)
		{
			m_opengl_service->setMat4(m_shader_program_map.at(shader_name), location, matrice_to_add);
		}
	}
	void ShaderService::setTexture(std::string shader_name, std::string const location, int const count)
	{
		if (m_shader_program_map.contains(shader_name) && m_opengl_service)
		{
			
			m_opengl_service->setTexture(m_shader_program_map.at(shader_name), location, count);
			
		}
	}
	void ShaderService::setFloat(std::string shader_name, std::string const location, float const to_ad)
	{
		if (m_shader_program_map.contains(shader_name) && m_opengl_service)
		{
			
			m_opengl_service->setFloat(m_shader_program_map.at(shader_name), location, to_ad);
			
		}
	}
	void ShaderService::setInt(std::string shader_name, std::string const location, int const to_ad)
	{
		if (m_shader_program_map.contains(shader_name) && m_opengl_service)
		{
			m_opengl_service->setInt(m_shader_program_map.at(shader_name), location, to_ad);
		}
	}
	void ShaderService::DeleteShaderProgram(std::string const shader_name)
	{

		if (m_shader_program_map.contains(shader_name) && glIsProgram(m_shader_program_map.at(shader_name)) == GL_TRUE)
		{
			glDeleteProgram(m_shader_program_map.at(shader_name));
			m_shader_program_map.at(shader_name) = 0;
		}
	}
}

