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
		std::shared_ptr<Views::MenuFileComponent> component_5 = container->make<Views::MenuFileComponent>();
		std::shared_ptr<Views::MenuToolsComponent> component_6 = container->make< Views::MenuToolsComponent>();
		std::shared_ptr<Views::MenuEditComponent> component_7 = container->make< Views::MenuEditComponent>();

		component_1->SetParent(this);
		component_2->SetParent(this);
		component_3->SetParent(this);
		component_4->SetParent(this);
		component_5->SetParent(this);
		component_6->SetParent(this);
		component_7->SetParent(this);

		std::list<std::shared_ptr<Views::IView>> simple_views;
		simple_views.push_back(component_1);
		simple_views.push_back(component_2);
		simple_views.push_back(component_3);
		simple_views.push_back(component_4);
		m_views_map.insert_or_assign(Constants::SIMPLECPT, simple_views);
		std::list<std::shared_ptr<Views::IView>> menu_views;
		menu_views.push_back(component_5);
		menu_views.push_back(component_6);
		menu_views.push_back(component_7);
		m_views_map.insert_or_assign(Constants::MENUSCPT, menu_views);

		m_state_service = IoC::Container::Container::GetInstanceContainer()->make<Services::StateService>();
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
	void GuiViewModel::OnCommand(Commands::ICommand* command)
	{
		m_command = std::unique_ptr<Commands::ICommand>(command);
		m_command->Execute();
		m_command.reset();
	}
}

