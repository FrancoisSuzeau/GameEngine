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
		virtual ~IView() { SetParent(nullptr); }
		virtual void Render() {};
		virtual void Render(std::vector<std::shared_ptr<Component::IComponent>> renderers) {};
		virtual void TransformRenderers(std::vector<std::shared_ptr<Component::IComponent>> renderers) {};
		virtual void DragRenderers(std::vector<std::shared_ptr<Component::IComponent>> renderers) {};
		virtual void ConstructRenderer() {};
		virtual void Clean() {};
		virtual void SetParent(ViewModels::IViewModel* parent) 
		{
			m_parent_view_model = std::shared_ptr<ViewModels::IViewModel>(parent);
		};

		virtual void SetSceneViewModel(ViewModels::IViewModel* scene_viewmodel) {};

	protected:
		std::shared_ptr<ViewModels::IViewModel> m_parent_view_model;
		int w_height;
		int w_width;
		float frame_rounding_save;
	};
	
}
#endif