/******************************************************************************************************************************************/
// File : ModifyShaderCommand.cpp
// Purpose : Implementing the Modify shader command
/******************************************************************************************************************************************/
#include "ModifyShaderCommand.hpp"

namespace Commands
{
	ModifyShaderCommand::ModifyShaderCommand(std::string const shader_name, Enums::ShaderModifier shader_modifier, 
		std::string const location, glm::vec3 const& vec_to_add, glm::mat4 const& matrice_to_add, int const count, float const to_ad, 
		int const to_add) 
		: m_shader_name(shader_name), m_shader_modifier(shader_modifier), m_location(location), m_vec_to_add(vec_to_add),
		m_matrice_to_add(matrice_to_add), m_count(count), m_to_ad(to_ad), m_to_add(to_add)
	{
		m_shader_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::ShaderService>();
		if (!m_shader_service)
		{
			SQ_APP_ERROR("Class {} in function {} : Shader service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}

	void ModifyShaderCommand::Execute()
	{
		if (m_shader_service)
		{
			SQ_APP_INFO("Modify shader command is called");
			switch (m_shader_modifier)
			{
			case Enums::VEC3:
				m_shader_service->setVec3(m_shader_name, m_location, m_vec_to_add);
				break;
			case Enums::MAT4:
				m_shader_service->setMat4(m_shader_name, m_location, m_matrice_to_add);
				break;
			case Enums::TEXTURE:
				m_shader_service->setTexture(m_shader_name, m_location, m_count);
				break;
			case Enums::FLOAT:
				m_shader_service->setFloat(m_shader_name, m_location, m_to_ad);
				break;
			case Enums::INT:
				m_shader_service->setInt(m_shader_name, m_location, m_to_add);
				break;
			default:
				break;
			}
		}
	}
}



