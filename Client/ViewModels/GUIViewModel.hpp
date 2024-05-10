/******************************************************************************************************************************************/
// File : GUIViewModel.hpp
// Purpose : The GUI view model of the application
/******************************************************************************************************************************************/
#ifndef GUIVIEWMODEL_H
#define GUIVIEWMODEL_H

#include "IViewModel.hpp"
#include "Container/Container.hpp"
#include "SceneViewModel.hpp"
#include "IView.hpp"
#include <iostream>
#include "ConfigEntity.hpp"
#include <list>
#include <map>

#include "../Views/GuiComponents/Simple/MetricsComponent.hpp"
#include "../Views/GuiComponents/Simple/StackToolsComponent.hpp"
#include "../Views/GuiComponents/Simple/AppAboutComponent.hpp"
#include "../Views/GuiComponents/Simple/AppStyleEditorComponent.hpp"
#include "../Views/GuiComponents/Menus/MenuFileComponent.hpp"
#include "../Views/GuiComponents/Menus/MenuToolsComponent.hpp"
#include "../Views/GuiComponents/Menus/MenuEditComponent.hpp"
#include "../Views/GuiComponents/Menus/MenuSettingsComponent.hpp"
#include "../Views/GuiComponents/Simple/EventViewerComponent.hpp"
#include "../Views/GuiComponents/Simple/SaveAsComponent.hpp"
#include "../Views/GuiComponents/Simple/ConfirmComponent.hpp"
#include "../Views/GuiComponents/Simple/StartComponent.hpp"
#include "../Views/GuiComponents/Simple/WorkBarComponent.hpp"
#include "../Views/GuiComponents/Simple/PannelComponent.hpp"


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
	};
}

#endif