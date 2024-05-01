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
#include "SceneViewModel.hpp"

#include <iostream>
#include "ConfigEntity.hpp"
#include <list>
#include <map>

namespace ViewModels
{
	class GuiViewModel : public IViewModel
	{

	public:
		~GuiViewModel() override;
		void Construct() override;
		
		void RenderComponents(Enums::ComponentType component_type) override;

 
	private:
		std::vector<std::unique_ptr<Views::IView>> m_simple_components;
		std::vector<std::unique_ptr<Views::IView>> m_menu_components;
		std::shared_ptr<Services::LoaderService> m_loader_service;
	};
}

#endif