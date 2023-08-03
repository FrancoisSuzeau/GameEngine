/******************************************************************************************************************************************/
// File : GUIViewModel.hpp
// Purpose : The GUI view model of the application
/******************************************************************************************************************************************/
#ifndef GUIVIEWMODEL_H
#define GUIVIEWMODEL_H

#include "IViewModel.hpp"
#include "../Views/GuiComponents/MetricsComponent.hpp"
#include "Container/Container.hpp"

#include <iostream>
#include <list>

namespace ViewModels
{
	class GuiViewModel : public IViewModel
	{

	public:
		void Construct() override;
		void DeConstruct() override;
		void RenderViews() override;
	private:
		std::list<std::shared_ptr<Views::IView>> m_views;
	};
}

#endif