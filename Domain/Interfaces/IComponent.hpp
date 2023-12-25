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
		virtual void Render(std::shared_ptr<Renderers::Triangle> renderer, GLenum const mode, float const line_width) {}
		virtual void Render(std::shared_ptr<Renderers::Square> renderer, GLenum const mode, float const line_width) {}
		virtual void Render(std::shared_ptr<Renderers::ScreenRenderer> renderer, GLenum const mode, float const line_width) {}
		virtual void Render(std::shared_ptr<Renderers::Grid> renderer, GLenum const mode, float const line_width) {}
		virtual void Render(std::shared_ptr < Renderers::Skybox>  renderer, GLenum const mode, float const line_width) {}
		virtual void OnSelectRenderer(std::shared_ptr<Renderers::IRenderer> renderer) {}
		virtual void OnHoverRenderers(std::shared_ptr<Renderers::IRenderer> renderer) {}
		virtual void OnUnSelectedComponents(std::vector<std::shared_ptr<Renderers::IRenderer>> renderers) {}

		

	};
}

#endif