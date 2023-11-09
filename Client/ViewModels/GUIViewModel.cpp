/******************************************************************************************************************************************/
// File : GUIViewModel.cpp
// Purpose : Implementing the GUI view model
/******************************************************************************************************************************************/

#include "GUIViewModel.hpp"

namespace ViewModels
{
	GuiViewModel::~GuiViewModel()
	{
		for (std::map<std::string, std::list<std::shared_ptr<Views::IView>>>::iterator it = m_views_map.begin(); it != m_views_map.end(); it++)
		{
			for (std::list<std::shared_ptr<Views::IView>>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
			{
				if (it2->get())
				{
					it2->get()->Clean();
					it2->reset();
				}
			}

			it->second.clear();
		}

		m_views_map.clear();
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
			std::shared_ptr<Views::EventViewerComponent> component_8 = container->GetReference<Views::EventViewerComponent>();
			std::shared_ptr<Views::SaveAsComponent> component_9 = container->GetReference<Views::SaveAsComponent>();
			std::shared_ptr<Views::ConfirmComponent> component_10 = container->GetReference<Views::ConfirmComponent>();
			m_start_component = container->GetReference<Views::StartComponent>();

			std::list<std::shared_ptr<Views::IView>> simple_views;
			if (component_1)
			{
				component_1->SetParent(this);
				simple_views.push_back(component_1);
				component_1.reset();
			}
			else
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Metrics component is not referenced yet", __FILE__, __FUNCTION__);
			}
			if (component_2)
			{
				component_2->SetParent(this);
				simple_views.push_back(component_2);
				component_2.reset();
			}
			else
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Stack tools component is not referenced yet", __FILE__, __FUNCTION__);
			}
			if (component_3)
			{
				component_3->SetParent(this);
				simple_views.push_back(component_3);
				component_3.reset();
			}
			else
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Application about component is not referenced yet", __FILE__, __FUNCTION__);
			}
			if (component_4)
			{
				component_4->SetParent(this);
				simple_views.push_back(component_4);
				component_4.reset();
			}
			else
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Application style editor component is not referenced yet", __FILE__, __FUNCTION__);
			}
			if (component_8)
			{
				component_8->SetParent(this);
				simple_views.push_back(component_8);
				component_8.reset();
			}
			else
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Event viewer component is not referenced yet", __FILE__, __FUNCTION__);
			}

			if (component_9)
			{
				component_9->SetParent(this);
				simple_views.push_back(component_9);
				component_9.reset();
			}
			else
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Save as component is not referenced yet", __FILE__, __FUNCTION__);
			}
			if (component_10)
			{
				component_10->SetParent(this);
				simple_views.push_back(component_10);
				component_10.reset();
			}
			else
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Save as component is not referenced yet", __FILE__, __FUNCTION__);
			}
			m_views_map.insert_or_assign(Constants::SIMPLECPT, simple_views);
			
			

			std::list<std::shared_ptr<Views::IView>> menu_views;
			if (component_5)
			{
				component_5->SetParent(this);
				component_5->SetSceneViewModel(IoC::Container::Container::GetInstanceContainer()->GetReference<ViewModels::SceneViewModel>().get());
				menu_views.push_back(component_5);
				component_5.reset();
			}
			else
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Menu file component is not referenced yet", __FILE__, __FUNCTION__);
			}
			if (component_6)
			{
				component_6->SetParent(this);
				menu_views.push_back(component_6);
				component_6.reset();
			}
			else
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Menu tools component is not referenced yet", __FILE__, __FUNCTION__);
			}
			if (component_7)
			{
				component_7->SetParent(this);
				menu_views.push_back(component_7);
				component_7.reset();
			}
			else
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Menu edit component is not referenced yet", __FILE__, __FUNCTION__);
			}

			if (m_start_component)
			{
				m_start_component->SetParent(this);
			}
			else
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Start component is not referenced yet", __FILE__, __FUNCTION__);
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

	void GuiViewModel::RenderStartMenu()
	{
		if (m_start_component)
		{
			m_start_component->Render();
		}
	}

}

