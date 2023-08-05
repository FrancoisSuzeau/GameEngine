/******************************************************************************************************************************************/
// File : LoadNewShaderCommand.hpp
// Purpose : A load shader command
/******************************************************************************************************************************************/
#ifndef LOADNEWSHADERCOMMAND_H
#define LOADNEWSHADERCOMMAND_H

#include "ICommand.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "../Services/Services.hpp"
#include <memory>

namespace Commands {

	class LoadNewShaderCommand : public ICommand
	{
	public:
		LoadNewShaderCommand(std::string const shader_name, Enums::ShaderType const shader_type);
		void Execute() override;
	private:
		std::shared_ptr<Services::ShaderService> m_shader_service;
		std::string const m_shader_name;
		Enums::ShaderType const m_shader_type;
		

	};
}

#endif