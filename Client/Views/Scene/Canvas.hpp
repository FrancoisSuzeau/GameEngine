/******************************************************************************************************************************************/
// File : Canvas.hpp
// Purpose : The canvas view of the scene
/******************************************************************************************************************************************/
#ifndef CANVAS_H
#define CANVAS_H

#include "IView.hpp"
#include "ComponentBase.hpp"
#include <map>

namespace Views
{
	class Canvas : public IView
	{
	public:
		Canvas();
		void Clean() override;
		void Render(std::vector<std::shared_ptr<Renderers::Triangle>>) override;
	private:
		std::map<std::string, std::unique_ptr<Component::ComponentBase>> m_components_map;
	};
}

#endif