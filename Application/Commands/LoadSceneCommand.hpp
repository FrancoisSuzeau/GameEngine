/******************************************************************************************************************************************/
// File : LoadSceneCommand.hpp
// Purpose : A save scene command
/******************************************************************************************************************************************/
#ifndef LOADSCENECOMMAND_H
#define LOADSCENECOMMAND_H

#include "ICommand.hpp"
#include "IRenderer.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "../Services/StateService.hpp"
#include "../Services/LoaderService.hpp"
#include "../Services/PhysicsService.hpp"
#include "../Services/ShaderService.hpp"
#include "../Services/CameraService.hpp"

#include <memory>
#include <vector>
#include <tuple>

namespace Commands {

	class LoadSceneCommand : public ICommand
	{
	public:
		LoadSceneCommand(std::string const filename);
		~LoadSceneCommand();
		void Execute() override;
	private:

		std::shared_ptr<Services::LoaderService> m_loader_service;
		std::shared_ptr<Services::StateService> m_state_service;
		std::shared_ptr<Services::PhysicsService> m_physics_service;
		std::shared_ptr<Services::ShaderService> m_shader_service;
		std::shared_ptr<Services::CameraService> m_camera_service;

		
	};
}

#endif