/******************************************************************************************************************************************/
// File : IView.hpp
// Purpose : the view interface
/******************************************************************************************************************************************/
#ifndef IVIEW_H
#define IVIEW_H

#include <iostream>
#include <functional>
#include "IViewModel.hpp"
#include "ICommand.hpp"
#include "IComponent.hpp"
#include <vector>

namespace Views {

	class IView
	{
	public:
		virtual ~IView() {};
		virtual void Render() {};
		virtual void Render(int const index) {};
		virtual void Render(std::vector<std::shared_ptr<Component::IComponent>> components) {};
		virtual void TransformComponents(std::vector<std::shared_ptr<Component::IComponent>> components) {};
		virtual void DragComponents(std::vector<std::shared_ptr<Component::IComponent>> components) {};
		virtual void ConstructRenderer() {};
		virtual void AddModelRenderer(std::unique_ptr<Renderers::IRenderer> new_renderer, std::string const model_type) {};
		virtual void Clean() {};

	protected:
		std::shared_ptr<ViewModels::IViewModel> m_parent_view_model;
		int w_height;
		int w_width;
		float frame_rounding_save;
	};
	
}
#endif