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
		virtual void Render(bool show = true) = 0;

	protected:
		

	};
	
}
#endif