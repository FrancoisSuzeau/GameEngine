/******************************************************************************************************************************************/
// File : IViewModel.hpp
// Purpose : the view model interface
/******************************************************************************************************************************************/
#ifndef IVIEWMODEL_H
#define IVIEWMODEL_H

#include <iostream>
#include <functional>
#include <list>

namespace ViewModels {

	class IViewModel
	{
	public:
		virtual ~IViewModel() {}

		virtual void Construct() = 0;

		virtual void DeConstruct() = 0;

		virtual void RenderViews(std::string const type_view) = 0;

	};

}
#endif