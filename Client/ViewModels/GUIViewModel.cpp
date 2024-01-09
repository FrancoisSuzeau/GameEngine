/******************************************************************************************************************************************/
// File : GUIViewModel.cpp
// Purpose : Implementing the GUI view model
/******************************************************************************************************************************************/

#include "GUIViewModel.hpp"

namespace ViewModels
{
	GuiViewModel::~GuiViewModel()
	{
		this->PopComponent(m_simple_components);
		m_simple_components.clear();
		this->PopComponent(m_menu_components);
		m_menu_components.clear();
	}
	void GuiViewModel::Construct()
	{
		
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{


			this->PushSimpleComponent(container->GetReference< Views::MetricsComponent>(), "Metrics");
			this->PushSimpleComponent(container->GetReference< Views::StackToolsComponent>(), "Stack Tools");
			this->PushSimpleComponent(container->GetReference< Views::AppAboutComponent>(), "About app");
			this->PushSimpleComponent(container->GetReference< Views::AppStyleEditorComponent>(), "Style editor");
			this->PushMenuComponent(container->GetReference<Views::MenuFileComponent>(), "Menu file");
			this->PushMenuComponent(container->GetReference< Views::MenuToolsComponent>(), "Menu tools");
			this->PushMenuComponent(container->GetReference< Views::MenuEditComponent>(), "Menu edit");
			this->PushSimpleComponent(container->GetReference<Views::EventViewerComponent>(), "Event viewer");
			this->PushSimpleComponent(container->GetReference<Views::SaveAsComponent>(), "Save as");
			this->PushSimpleComponent(container->GetReference<Views::ConfirmComponent>(), "Confirm");
			this->PushSimpleComponent(container->GetReference<Views::StartComponent>(), "Start screen");
			this->PushSimpleComponent(container->GetReference<Views::SingleRendererContextMenu>(), "Context menu");
		}
	}

	void GuiViewModel::RenderComponents(Enums::ComponentType component_type)
	{
		switch (component_type)
		{
		case Enums::SIMPLE:
			for (std::vector<std::shared_ptr<Views::IView>>::iterator it = m_simple_components.begin(); it != m_simple_components.end(); it++)
			{
				if (it[0])
				{
					it[0]->Render();
				}
			}
			break;
		case Enums::MENUS:
			for (std::vector<std::shared_ptr<Views::IView>>::iterator it = m_menu_components.begin(); it != m_menu_components.end(); it++)
			{
				if (it[0])
				{
					it[0]->Render();
				}
			}
			break;
		case Enums::CANVAS:
		default:
			break;
		}
	}

	void GuiViewModel::PushSimpleComponent(std::shared_ptr<Views::IView> component, std::string const cpt_name)
	{
		if (component)
		{
			component->SetParent(this);
			m_simple_components.push_back(component);
		}
		else
		{
			SQ_CLIENT_ERROR("Class {} in function {} : {} component is not referenced yet", __FILE__, __FUNCTION__, cpt_name);
		}
	}

	void GuiViewModel::PushMenuComponent(std::shared_ptr<Views::IView> component, std::string const cpt_name)
	{
		if (component)
		{
			component->SetParent(this);
			m_menu_components.push_back(component);
		}
		else
		{
			SQ_CLIENT_ERROR("Class {} in function {} : {} component is not referenced yet", __FILE__, __FUNCTION__, cpt_name);
		}
	}

	void GuiViewModel::PopComponent(std::vector<std::shared_ptr<Views::IView>> components)
	{
		for (std::vector<std::shared_ptr<Views::IView>>::iterator it = components.begin(); it != components.end(); it++)
		{
			if (it[0])
			{
				it[0]->Clean();
				it[0].reset();
			}
		}
	}

}

