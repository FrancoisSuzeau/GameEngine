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
#include "Services/MousePickerService.hpp"

namespace Component
{
	class Draggable : public IComponent
	{
	public:
		Draggable();
		void Clean() override;
		void OnSelectRenderer(std::shared_ptr<Renderers::IRenderer> renderer) override;

	private:
		std::shared_ptr<Services::MousePickerService> m_mouse_picker_service;
		std::shared_ptr<Services::StateService> m_state_service;

		bool CalculateIntersection(std::shared_ptr<Renderers::Square> renderer);

	};
}

#endif