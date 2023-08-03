/******************************************************************************************************************************************/
// File : GUIViewModel.cpp
// Purpose : Implementing the GUI view model
/******************************************************************************************************************************************/

#include "GUIViewModel.hpp"

namespace ViewModels
{
	void GuiViewModel::Construct()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		std::shared_ptr<Views::MetricsComponent> component_1 = container->make< Views::MetricsComponent>();
		std::shared_ptr<Views::StackToolsComponent> component_2 = container->make< Views::StackToolsComponent>();
		std::shared_ptr<Views::AppAboutComponent> component_3 = container->make< Views::AppAboutComponent>();
		std::shared_ptr<Views::AppStyleEditorComponent> component_4 = container->make< Views::AppStyleEditorComponent>();
		std::shared_ptr<Views::MenuToolsComponent> component_5 = container->make< Views::MenuToolsComponent>();
		std::shared_ptr<Views::MenuEditComponent> component_6 = container->make< Views::MenuEditComponent>();

		std::list<std::shared_ptr<Views::IView>> simple_views;
		simple_views.push_back(component_1);
		simple_views.push_back(component_2);
		simple_views.push_back(component_3);
		simple_views.push_back(component_4);
		m_views_map.insert_or_assign(Constants::SIMPLECPT, simple_views);
		std::list<std::shared_ptr<Views::IView>> menu_views;
		menu_views.push_back(component_5);
		menu_views.push_back(component_6);
		m_views_map.insert_or_assign(Constants::MENUSCPT, menu_views);
	}

	void GuiViewModel::DeConstruct()
	{
		m_views_map.clear();
	}
	void GuiViewModel::RenderViews(std::string const type_view)
	{
		for (std::list<std::shared_ptr<Views::IView>>::iterator it = m_views_map.at(type_view).begin(); 
			it != m_views_map.at(type_view).end(); it++)
		{
			it->get()->Render();
		}
	}
}

