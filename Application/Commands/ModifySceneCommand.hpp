/******************************************************************************************************************************************/
// File : ModifySceneCommand.hpp
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

	class ModifySceneCommand : public ICommand
	{
	public:
		ModifySceneCommand(Enums::SceneModifier const scene_modifier, Enums::RendererType component_type);
		ModifySceneCommand(Enums::SceneModifier const scene_modifier);
		ModifySceneCommand(Enums::SceneModifier const scene_modifier, std::string const string_value);
		ModifySceneCommand(Enums::SceneModifier const scene_modifier, std::string const string_value, Enums::RendererType component_type);
		ModifySceneCommand(Enums::SceneModifier const scene_modifier, std::shared_ptr<Component::IComponent> component_to_copy);
		~ModifySceneCommand();
		void Execute() override;
	private:
		std::shared_ptr<Services::StateService> m_state_service;
		std::shared_ptr<Services::CameraService> m_camera_service;
		std::shared_ptr<Services::LoaderService> m_loader_service;
		Enums::RendererType const m_component_type;
		Enums::SceneModifier const m_scene_modifier;
		std::string const m_string_value;
		std::shared_ptr<Component::IComponent> m_component_to_copy;
		void PostAddingComponentToScene(std::shared_ptr<Component::IComponent> new_component_to_make, glm::vec3 const cam_position);
		void AddComponentToScene();
		void CopyComponent();
		void GetServices();
	};
}

#endif