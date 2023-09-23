/******************************************************************************************************************************************/
// File : TexturedComponent.hpp
// Purpose : The Component view implementing basis of element on canvas
/******************************************************************************************************************************************/
#ifndef TEXTUREDCOMPONENT_H
#define TEXTUREDCOMPONENT_H

#include "IComponent.hpp"
#include "Services/ShaderService.hpp"
#include "Container/Container.hpp"
#include "Constants/NumberConstants.hpp"
#include "Renderers/Renderers.hpp"
#include "../Transformer.hpp"
#include <GL/glew.h>

namespace Component
{
	class TexturedComponent : public IComponent
	{
	public:
		TexturedComponent();
		void Clean() override;
		void Render(std::shared_ptr<Renderers::SquareTextured> renderer, unsigned int t) override;

	private:
		std::shared_ptr<Services::ShaderService> m_shader_service;

	};
}

#endif