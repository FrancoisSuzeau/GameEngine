/******************************************************************************************************************************************/
// File : ComponentBase.hpp
// Purpose : The Component view implementing basis of element on canvas
/******************************************************************************************************************************************/
#ifndef COMPONENTBASE_H
#define COMPONENTBASE_H

#include "../../Interfaces/IComponent.hpp"

namespace Component
{
	class ComponentBase : public IComponent
	{
	public:
		ComponentBase(glm::vec3 position, glm::vec3 size, Enums::RendererType type, glm::vec4 color);
		void Clean() override;

		glm::vec4 GetBackgroundColor() const;

	private:
		glm::vec4 m_back_ground_color;
		
	};
}

#endif