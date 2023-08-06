/******************************************************************************************************************************************/
// File : GUIViewModel.hpp
// Purpose : The GUI view model of the application
/******************************************************************************************************************************************/
#ifndef GUIVIEWMODEL_H
#define GUIVIEWMODEL_H

#include "IViewModel.hpp"
#include "../Views/Views.hpp"
#include "Container/Container.hpp"
#include "Commands/Commands.hpp"

#include <iostream>
#include <list>
#include <map>

namespace ViewModels
{
	class GuiViewModel : public IViewModel
	{

	public:
		void Construct() override;
		void DeConstruct() override;
		void RenderViews(std::string const type_view) override;
		void OnCommand(Commands::ICommand* command) override;

	private:
		std::map<std::string, std::list<std::shared_ptr<Views::IView>>> m_views_map;
	};
}

#endif