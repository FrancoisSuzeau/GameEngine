/******************************************************************************************************************************************/
// File : Draggable.hpp
// Purpose : The draggable component
/******************************************************************************************************************************************/
#ifndef DRAGGABLE_H
#define DRAGGABLE_H

#include "IComponent.hpp"
#include "Container/Container.hpp"
#include "Constants/NumberConstants.hpp"
#include "Renderers/Renderers.hpp"
#include "Services/MouseInputService.hpp"

namespace Component
{
	class Draggable : public IComponent
	{
	public:
		Draggable();
		void Clean() override;
		void OnSelectRenderer(std::shared_ptr<Renderers::IRenderer> renderer) override;
		void OnHoverRenderers(std::shared_ptr<Renderers::IRenderer> renderer) override;
		void OnUnSelectedComponents(std::vector<std::shared_ptr<Renderers::IRenderer>> renderers) override;
	private:
		std::shared_ptr<Services::MouseInputService> m_mouse_input_service;
		std::shared_ptr<Services::KeyboardInputService> m_keyboard_input_service;
		std::shared_ptr<Services::StateService> m_state_service;
		std::shared_ptr<Services::CameraService> m_camera_service;

		bool CalculateIntersection(std::shared_ptr<Renderers::IRenderer> renderer);
		void CalculateIsComponentSelected(std::shared_ptr<Renderers::IRenderer> renderer);
		bool m_keys[SDL_NUM_SCANCODES];

	};
}

#endif