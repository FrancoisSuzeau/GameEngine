/******************************************************************************************************************************************/
// File : AddNewComponentCommmand.hpp
// Purpose : A save scene command
/******************************************************************************************************************************************/
#ifndef ADDNEWCPTCOMMAND_H
#define ADDNEWCPTCOMMAND_H

#include "ICommand.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "../Services/StateService.hpp"
#include "../Services/CameraService.hpp"
#include "../Services/LoaderService.hpp"

#include "Components/ComponentBase.hpp"
#include "Components/TexturedComponent.hpp"

#include <memory>

namespace Commands {

	class AddNewComponentCommmand : public ICommand
	{
	public:
		AddNewComponentCommmand(Enums::RendererType component_type);
		~AddNewComponentCommmand();
		void Execute() override;
	private:
		std::shared_ptr<Services::StateService> m_state_service;
		std::shared_ptr<Services::CameraService> m_camera_service;
		std::shared_ptr<Services::LoaderService> m_loader_service;
		Enums::RendererType const m_component_type;
		void AddComponentToScene(std::shared_ptr<Component::IComponent> new_component_to_make);
	};
}

#endif