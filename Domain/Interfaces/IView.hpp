/******************************************************************************************************************************************/
// File : IView.hpp
// Purpose : the view interface
/******************************************************************************************************************************************/
#ifndef IVIEW_H
#define IVIEW_H

#include <iostream>
#include <functional>
#include "IViewModel.hpp"

namespace Views {

	class IView
	{
	public:
		virtual ~IView() {}
		virtual void Render() = 0;
		void SetParent(ViewModels::IViewModel* parent) 
		{
			m_parent_view_model = std::shared_ptr<ViewModels::IViewModel>(parent);
		};

	protected:
		std::shared_ptr<ViewModels::IViewModel> m_parent_view_model;

	};
	
}
#endif