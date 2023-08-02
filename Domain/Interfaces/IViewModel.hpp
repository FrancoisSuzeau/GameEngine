/******************************************************************************************************************************************/
// File : IViewModel.hpp
// Purpose : the view model interface
/******************************************************************************************************************************************/
#ifndef IVIEWMODEL_H
#define IVIEWMODEL_H

#include <iostream>
#include <functional>
#include <list>

#include "IView.hpp"

namespace ViewModels {

	class IViewModel
	{
	public:
		virtual ~IViewModel() {}

		virtual void Construct() = 0;

	};

}
#endif