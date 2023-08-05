/******************************************************************************************************************************************/
// File : DeleteShaderCommand.hpp
// Purpose : A delete shader command
/******************************************************************************************************************************************/
#ifndef DELETESHADERCOMMAND_H
#define DELETESHADERCOMMAND_H

#include "ICommand.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "../Services/Services.hpp"
#include <memory>

namespace Commands {

	class DeleteShaderCommand : public ICommand
	{
	public:
		DeleteShaderCommand(std::string const shader_name);
		void Execute() override;
	private:
		std::shared_ptr<Services::ShaderService> m_shader_service;
		std::string const m_shader_name;


	};
}

#endif