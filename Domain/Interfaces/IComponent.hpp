/******************************************************************************************************************************************/
// File : IComponent.hpp
// Purpose : An interface for the renderers
/******************************************************************************************************************************************/
#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "../Entities/Renderers/Renderers.hpp"

namespace Component {

	class IComponent
	{
	public:
		virtual ~IComponent() {}
		virtual void Clean() = 0;
		virtual void OnSelectRenderer(std::shared_ptr<Renderers::IRenderer> renderer) {}
		virtual void OnHoverRenderer(std::shared_ptr<Renderers::IRenderer> renderer) {}
		virtual void OnUnSelectRenderer(std::shared_ptr<Renderers::IRenderer> renderer) {}
		virtual void OnSelectRenderers(std::vector<std::shared_ptr<Renderers::IRenderer>> renderers) {}

		

	};
}

#endif