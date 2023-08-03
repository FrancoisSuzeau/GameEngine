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
		std::shared_ptr<Views::MetricsComponent> component = container->make< Views::MetricsComponent>();

		m_views.push_back(component);
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

