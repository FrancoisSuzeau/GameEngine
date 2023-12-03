/******************************************************************************************************************************************/
// File : Canvas.hpp
// Purpose : The canvas view of the scene
/******************************************************************************************************************************************/
#ifndef CANVAS_H
#define CANVAS_H

#include "IView.hpp"
#include "ComponentBase.hpp"
#include "TexturedComponent.hpp"
#include "Draggable.hpp"
#include <map>
#include <iostream>

namespace Views
{
	class Canvas : public IView
	{
	public:
		Canvas();
		void Clean() override;
		void Render(std::vector<std::shared_ptr<Renderers::IRenderer>> renderers) override;
	private:
		std::map<std::string, std::unique_ptr<Component::IComponent>> m_components_map;
	};
}

#endif