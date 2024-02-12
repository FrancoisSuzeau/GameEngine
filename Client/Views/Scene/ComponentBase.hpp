/******************************************************************************************************************************************/
// File : ComponentBase.hpp
// Purpose : The Component view implementing basis of element on canvas
/******************************************************************************************************************************************/
#ifndef COMPONENTBASE_H
#define COMPONENTBASE_H

#include "IComponent.hpp"
#include "Services/ShaderService.hpp"
#include "Container/Container.hpp"
#include "Constants/NumberConstants.hpp"
#include "Renderers/Renderers.hpp"
#include "../Transformer.hpp"
#include <GL/glew.h>

namespace Component
{
	class ComponentBase : public IComponent
	{
	public:
		ComponentBase();
		void Clean() override;
		void Render(std::shared_ptr<Renderers::Triangle> renderer, GLenum const mode, float const line_width) override;
		void Render(std::shared_ptr<Renderers::Square> renderer, GLenum const mode, float const line_width) override;
		void Render(std::shared_ptr<Renderers::Grid> renderer, GLenum const mode, float const line_width) override;

	private:
		std::shared_ptr<Services::ShaderService> m_shader_service;
		
	};
}

#endif