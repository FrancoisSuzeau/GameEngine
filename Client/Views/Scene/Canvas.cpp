/******************************************************************************************************************************************/
// File : Canvas.cpp
// Purpose : Implementing the GUI view app style editor
/******************************************************************************************************************************************/

#include "Canvas.hpp"

namespace Views
{
	Canvas::Canvas()
	{
		m_components_map.insert_or_assign(Constants::COMPONENT_BASE, std::make_unique<Component::ComponentBase >());
	}

	void Canvas::Clean()
	{
		for (std::map<std::string, std::unique_ptr<Component::ComponentBase>>::iterator it = m_components_map.begin(); it != m_components_map.end(); it++)
		{
			if (it->second)
			{
				it->second->Clean();
				it->second.reset();
			}
		}
	}

	void Canvas::Render(std::vector<std::shared_ptr<Renderers::Triangle>> renderer)
	{
		for (std::vector<std::shared_ptr<Renderers::Triangle>>::iterator it = renderer.begin(); it != renderer.end(); it++)
		{
			if (m_components_map.contains(Constants::COMPONENT_BASE) && m_components_map.at(Constants::COMPONENT_BASE))
			{
				m_components_map.at(Constants::COMPONENT_BASE)->Render(it[0]);
			}
		}
	}
}