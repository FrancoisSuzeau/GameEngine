/******************************************************************************************************************************************/
// File : ShaderService.cpp
// Purpose : Implementing service shader
/******************************************************************************************************************************************/
#include "ShaderService.hpp"

namespace Services
{
	void ShaderService::Init()
	{
		m_shader_loader = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::ShaderLoaderService>();
		
	}

	void ShaderService::DeInit()
	{
		for (std::map<std::string, std::unique_ptr<Shaders::Shader>>::iterator it = m_shader_map.begin(); it != m_shader_map.end(); it++)
		{
			if (it->second && m_shader_loader)
			{
				GLuint program_id = it->second->getProgramId();
				m_shader_loader->deleteProgram(program_id);
				it->second.reset();
			}
		}

		m_shader_map.clear();
	}

	void ShaderService::LoadShader(std::string shader_name, Enums::ShaderType shader_type)
	{
		if (!m_shader_map.contains(shader_name) && m_shader_loader)
		{
			GLuint program_id = m_shader_loader->loadShader(shader_name, shader_type);
			m_shader_map.insert_or_assign(shader_name, std::unique_ptr<Shaders::Shader>(new Shaders::Shader(program_id)));
		}
		else
		{
			SQ_APP_ERROR("Shader {} already exist", shader_name);
		}
		
	}

	void ShaderService::DeleteShader(std::string shader_name)
	{
		if (m_shader_map.contains(shader_name) && m_shader_loader && m_shader_map.at(shader_name))
		{
			GLuint program_id = m_shader_map.at(shader_name)->getProgramId();
			m_shader_loader->deleteProgram(program_id);
			m_shader_map.at(shader_name).reset();
			m_shader_map.erase(shader_name);
		}
	}

	GLuint ShaderService::GetProgramId(std::string const shader_name)
	{
		if (m_shader_map.contains(shader_name) && m_shader_map.at(shader_name))
		{
			return m_shader_map.at(shader_name)->getProgramId();
		}

		return Constants::Return_error;
	}
	 
	void ShaderService::setVec3(std::string shader_name, std::string const location, glm::vec3 const& vec_to_add)
	{

		if (m_shader_map.contains(shader_name) && m_shader_map.at(shader_name))
		{
			m_shader_map.at(shader_name)->setVec3(location, vec_to_add);
		}
	}
	void ShaderService::setMat4(std::string shader_name, std::string const location, glm::mat4 const& matrice_to_add)
	{
		if (m_shader_map.contains(shader_name) && m_shader_map.at(shader_name))
		{
			m_shader_map.at(shader_name)->setMat4(location, matrice_to_add);
		}
	}
	void ShaderService::setTexture(std::string shader_name, std::string const location, int const count)
	{
		if (m_shader_map.contains(shader_name) && m_shader_map.at(shader_name))
		{
			
			m_shader_map.at(shader_name)->setTexture(location, count);
			
		}
	}
	void ShaderService::setFloat(std::string shader_name, std::string const location, float const to_ad)
	{
		if (m_shader_map.contains(shader_name) && m_shader_map.at(shader_name))
		{
			
			m_shader_map.at(shader_name)->setFloat(location, to_ad);
			
		}
	}
	void ShaderService::setInt(std::string shader_name, std::string const location, int const to_ad)
	{
		if (m_shader_map.contains(shader_name) && m_shader_map.at(shader_name))
		{
			m_shader_map.at(shader_name)->setInt(location, to_ad);
		}
	}
}

