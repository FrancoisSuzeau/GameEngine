/******************************************************************************************************************************************/
// File : GUIViewModel.cpp
// Purpose : Implementing the GUI view model
/******************************************************************************************************************************************/

#include "GUIViewModel.hpp"

namespace ViewModels
{
	GuiViewModel::~GuiViewModel()
	{
		for (std::vector<std::unique_ptr<Views::IView>>::iterator it = m_simple_components.begin(); it != m_simple_components.end(); it++)
		{
			if (it[0])
			{
				it[0]->Clean();
				it[0].reset();
			}
		}

		for (std::vector<std::unique_ptr<Views::IView>>::iterator it = m_menu_components.begin(); it != m_menu_components.end(); it++)
		{
			if (it[0])
			{
				it[0]->Clean();
				it[0].reset();
			}
		}
		m_simple_components.clear();
		m_menu_components.clear();

		if (m_loader_component)
		{
			m_loader_component->Clean();
			m_loader_component.reset();
		}
	}
	void GuiViewModel::Construct()
	{
		m_simple_components.push_back(std::make_unique< Views::MetricsComponent>(shared_from_this()));
		m_simple_components.push_back(std::make_unique< Views::StackToolsComponent>(shared_from_this()));
		m_simple_components.push_back(std::make_unique< Views::AppAboutComponent>(shared_from_this()));
		m_simple_components.push_back(std::make_unique< Views::AppStyleEditorComponent>(shared_from_this()));
		m_menu_components.push_back(std::make_unique<Views::MenuFileComponent>(shared_from_this()));
		m_menu_components.push_back(std::make_unique< Views::MenuToolsComponent>(shared_from_this()));
		m_menu_components.push_back(std::make_unique< Views::MenuEditComponent>(shared_from_this()));
		m_menu_components.push_back(std::make_unique< Views::MenuSettingsComponent>(shared_from_this()));
		m_simple_components.push_back(std::make_unique<Views::EventViewerComponent>(shared_from_this()));
		m_simple_components.push_back(std::make_unique<Views::SaveAsComponent>(shared_from_this()));
		m_simple_components.push_back(std::make_unique<Views::ConfirmComponent>(shared_from_this()));
		m_simple_components.push_back(std::make_unique<Views::StartComponent>(shared_from_this()));
		m_simple_components.push_back(std::make_unique<Views::WorkBarComponent>(shared_from_this()));
		m_simple_components.push_back(std::make_unique<Views::PannelComponent>(shared_from_this()));

		m_loader_component = std::make_unique<Views::LoaderComponent>(shared_from_this());
	}

	void GuiViewModel::RenderComponents(Enums::ComponentType component_type)
	{
		switch (component_type)
		{
		case Enums::SIMPLE:
			for (std::vector<std::unique_ptr<Views::IView>>::iterator it = m_simple_components.begin(); it != m_simple_components.end(); it++)
			{
				if (it[0])
				{
					it[0]->Render();
				}
			}
			break;
		case Enums::MENUS:
			for (std::vector<std::unique_ptr<Views::IView>>::iterator it = m_menu_components.begin(); it != m_menu_components.end(); it++)
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

	void GuiViewModel::RenderLoadComponent(int const index)
	{
		if (m_loader_component)
		{
			m_loader_component->Render(index);
		}
	}

}

