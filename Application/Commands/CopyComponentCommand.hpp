/******************************************************************************************************************************************/
// File : CopyComponentCommand.hpp
// Purpose : A save scene command
/******************************************************************************************************************************************/
#ifndef COPYCOMPONENTCOMMAND_H
#define COPYCOMPONENTCOMMAND_H

#include "ICommand.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "../Services/StateService.hpp"
#include "IComponent.hpp"
#include "../Services/CameraService.hpp"


#include <memory>

namespace Commands {

	class CopyComponentCommand : public ICommand
	{
	public:
		CopyComponentCommand(std::shared_ptr<Component::IComponent> renderer_to_copy);
		~CopyComponentCommand();
		void Execute() override;
	private:
		std::shared_ptr<Services::StateService> m_state_service;
		std::shared_ptr<Component::IComponent> m_renderer_to_copy;
		std::shared_ptr<Services::CameraService> m_camera_service;
		void MakeNewComponent(std::shared_ptr<Component::IComponent> new_component_to_make);
	};
}

#endif