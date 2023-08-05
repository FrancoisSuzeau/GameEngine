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

	protected:
		

	};
	
}
#endif