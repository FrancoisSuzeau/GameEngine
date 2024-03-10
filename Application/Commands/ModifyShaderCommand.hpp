/******************************************************************************************************************************************/
// File : ModifyShaderCommand.hpp
// Purpose : A Modify shader command
/******************************************************************************************************************************************/
#ifndef MODIFYSHADERCOMMAND_H
#define MODIFYSHADERCOMMAND_H

#include "ICommand.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "../Services/Services.hpp"
#include <memory>

namespace Commands {

	class ModifyShaderCommand : public ICommand
	{
	public:
		ModifyShaderCommand(std::string const shader_name, Enums::ShaderModifier shader_modifier, std::string const location,
			glm::vec3 const& vec_to_add = glm::vec3(), glm::mat4 const& matrice_to_add = glm::mat4(), int const count = 0, float const to_ad = 0,
			int const to_add = 0);
		~ModifyShaderCommand();
		void Execute() override;
	private:
		std::shared_ptr<Services::ShaderService> m_shader_service;
		std::string const m_shader_name;
		Enums::ShaderModifier m_shader_modifier;
		std::string const m_location;
		glm::vec3 const m_vec_to_add;
		glm::mat4 const m_matrice_to_add;
		int const m_count;
		float const m_to_ad;
		int const m_to_add;



	};
}

#endif