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
		m_components_map.insert_or_assign(Constants::COMPONENT_DRAGGABLE, std::make_unique<Component::Draggable >());
	}

	void Canvas::Clean()
	{
		for (std::map<std::string, std::unique_ptr<Component::IComponent>>::iterator it = m_components_map.begin(); it != m_components_map.end(); it++)
		{
			if (it->second)
			{
				it->second->Clean();
				it->second.reset();
			}
		}
	}

	void Canvas::Render(std::vector<std::shared_ptr<Renderers::IRenderer>> renderers)
	{
		for (std::vector<std::shared_ptr<Renderers::IRenderer>>::iterator it = renderers.begin(); it != renderers.end(); it++)
		{
			if (m_components_map.contains(Constants::COMPONENT_BASE) && m_components_map.at(Constants::COMPONENT_BASE))
			{
				switch (it[0]->GetType())
				{
				case Enums::RendererType::TRIANGLE:
				{
					std::shared_ptr<Renderers::Triangle> t = std::dynamic_pointer_cast<Renderers::Triangle> (it[0]);
					m_components_map.at(Constants::COMPONENT_BASE)->Render(t);
					t.reset();
				}
				break;
				case Enums::RendererType::SQUARE:
				{
					std::shared_ptr<Renderers::Square> s = std::dynamic_pointer_cast<Renderers::Square> (it[0]);
					m_components_map.at(Constants::COMPONENT_BASE)->Render(s);
					s.reset();
				}
				break;
				case Enums::RendererType::NONE:
				default:
					break;
				}

			}
			if (m_components_map.contains(Constants::COMPONENT_DRAGGABLE) && m_components_map.at(Constants::COMPONENT_DRAGGABLE))
			{
				m_components_map.at(Constants::COMPONENT_DRAGGABLE)->OnHoverRenderers(it[0]);
			}
		}
	}
	void Canvas::TransformRenderers(std::vector<std::shared_ptr<Renderers::IRenderer>> renderers)
	{
		if (m_components_map.contains(Constants::COMPONENT_DRAGGABLE) && m_components_map.at(Constants::COMPONENT_DRAGGABLE))
		{
			for (std::vector<std::shared_ptr<Renderers::IRenderer>>::iterator it = renderers.begin(); it != renderers.end(); it++)
			{
				m_components_map.at(Constants::COMPONENT_DRAGGABLE)->OnSelectRenderer(it[0]);
				Component::Transformer::ReinitModelMat(it[0]);
				//this->IncrementAngle(0.1f);
				Component::Transformer::Move(it[0], it[0]->GetPosition());
				Component::Transformer::Resize(it[0], it[0]->GetSize());
				//Component::Transformer::Rotate(renderer, angle, glm::vec3(0.f, 0.f, 1.f));
			}

			m_components_map.at(Constants::COMPONENT_DRAGGABLE)->OnUnSelectedComponents(renderers);
		}
	}
}