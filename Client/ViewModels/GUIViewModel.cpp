/******************************************************************************************************************************************/
// File : GUIViewModel.cpp
// Purpose : Implementing the GUI view model
/******************************************************************************************************************************************/

#include "GUIViewModel.hpp"

namespace ViewModels
{
	GuiViewModel::~GuiViewModel()
	{
		
	}
	void GuiViewModel::Construct()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			std::shared_ptr<Views::MetricsComponent> component_1 = container->GetReference< Views::MetricsComponent>();
			std::shared_ptr<Views::StackToolsComponent> component_2 = container->GetReference< Views::StackToolsComponent>();
			std::shared_ptr<Views::AppAboutComponent> component_3 = container->GetReference< Views::AppAboutComponent>();
			std::shared_ptr<Views::AppStyleEditorComponent> component_4 = container->GetReference< Views::AppStyleEditorComponent>();
			std::shared_ptr<Views::MenuFileComponent> component_5 = container->GetReference<Views::MenuFileComponent>();
			std::shared_ptr<Views::MenuToolsComponent> component_6 = container->GetReference< Views::MenuToolsComponent>();
			std::shared_ptr<Views::MenuEditComponent> component_7 = container->GetReference< Views::MenuEditComponent>();

			std::list<std::shared_ptr<Views::IView>> simple_views;
			if (component_1)
			{
				component_1->SetParent(this);
				simple_views.push_back(component_1);
			}
			if (component_2)
			{
				component_2->SetParent(this);
				simple_views.push_back(component_2);
			}
			if (component_3)
			{
				component_3->SetParent(this);
				simple_views.push_back(component_3);
			}
			if (component_4)
			{
				component_4->SetParent(this);
				simple_views.push_back(component_4);
			}
			m_views_map.insert_or_assign(Constants::SIMPLECPT, simple_views);

			std::list<std::shared_ptr<Views::IView>> menu_views;
			if (component_5)
			{
				component_5->SetParent(this);
				menu_views.push_back(component_5);
			}
			if (component_6)
			{
				component_6->SetParent(this);
				menu_views.push_back(component_6);
			}
			if (component_7)
			{
				component_7->SetParent(this);
				menu_views.push_back(component_7);
			}
			m_views_map.insert_or_assign(Constants::MENUSCPT, menu_views);
		}
	}

	void GuiViewModel::RenderViews(std::string const type_view)
	{
		for (std::list<std::shared_ptr<Views::IView>>::iterator it = m_views_map.at(type_view).begin(); 
			it != m_views_map.at(type_view).end(); it++)
		{
			if (it->get())
			{
				it->get()->Render();
			}
		}
	}
	void GuiViewModel::OnCommand(Commands::ICommand* command)
	{
		if (command)
		{
			m_command = std::unique_ptr<Commands::ICommand>(command);
			if (m_command)
			{
				m_command->Execute();
				m_command.reset();
			}
		}
	}
}

