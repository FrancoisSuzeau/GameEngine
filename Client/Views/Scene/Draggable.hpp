/******************************************************************************************************************************************/
// File : Draggable.hpp
// Purpose : The draggable component
/******************************************************************************************************************************************/
#ifndef DRAGGABLE_H
#define DRAGGABLE_H

#include "IComponent.hpp"
#include "Container/Container.hpp"
#include "Constants/NumberConstants.hpp"
#include "Services/MouseInputService.hpp"

namespace Views
{
	class Draggable
	{
	public:
		Draggable();
		void Clean();
		void OnSelectRenderer(std::shared_ptr<Component::IComponent> renderer);
		void OnHoverRenderer(std::shared_ptr<Component::IComponent> renderer);
		void OnUnSelectRenderer(std::shared_ptr<Component::IComponent> renderer);
		void OnSelectRenderers(std::vector<std::shared_ptr<Component::IComponent>> renderers);
	private:
		std::shared_ptr<Services::MouseInputService> m_mouse_input_service;
		std::shared_ptr<Services::KeyboardInputService> m_keyboard_input_service;
		std::shared_ptr<Services::StateService> m_state_service;
		std::shared_ptr<Services::CameraService> m_camera_service;

		bool CalculateIntersection(std::shared_ptr<Component::IComponent> renderer);

	};
}

#endif