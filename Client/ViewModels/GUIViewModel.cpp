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

		m_views.push_back(component_1);
		m_views.push_back(component_2);
	}

	void GuiViewModel::DeConstruct()
	{
		m_views.clear();
	}
	void GuiViewModel::RenderViews()
	{
		for (std::list<std::shared_ptr<Views::IView>>::iterator it = m_views.begin(); it != m_views.end(); it++)
		{
			it->get()->Render();
		}
	}
}

