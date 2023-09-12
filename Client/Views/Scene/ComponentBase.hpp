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
#include <GL/glew.h>

namespace Component
{
	class ComponentBase : public IComponent
	{
	public:
		ComponentBase();
		void Clean() override;
		void Render(std::shared_ptr<Renderers::Triangle> renderer) override;
		void Transform() override;
	private:
		std::shared_ptr<Services::ShaderService> m_shader_service;
		glm::vec3 m_background_color;
	};
}

#endif