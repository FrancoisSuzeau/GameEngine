/******************************************************************************************************************************************/
// File : IView.hpp
// Purpose : the view interface
/******************************************************************************************************************************************/
#ifndef IVIEW_H
#define IVIEW_H

#include <iostream>
#include <functional>
#include "IViewModel.hpp"
#include <vector>
#include "../Entities/Renderers/Renderers.hpp"

namespace Views {

	class IView
	{
	public:
		virtual ~IView() { SetParent(nullptr); }
		virtual void Render() {};
		virtual void Render(std::vector<std::shared_ptr<Renderers::IRenderer>> renderers) {};
		virtual void Clean() {};
		void SetParent(ViewModels::IViewModel* parent) 
		{
			m_parent_view_model = std::shared_ptr<ViewModels::IViewModel>(parent);
		};

	protected:
		std::shared_ptr<ViewModels::IViewModel> m_parent_view_model;

	};
	
}
#endif