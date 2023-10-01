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
		virtual void Render(std::shared_ptr<Renderers::Triangle> renderer) {}
		virtual void Render(std::shared_ptr<Renderers::Square> renderer) {}
		virtual void Render(std::shared_ptr<Renderers::ScreenRenderer> renderer) {}
		virtual void Render(std::shared_ptr<Renderers::Grid> renderer) {}
		virtual void Render(std::shared_ptr < Renderers::Skybox>  renderer) {}

		

	};
}

#endif