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

		glm::vec4 GetBackgroundColor() const;
		void SetBackgroundColor(glm::vec4 new_bacground_color);

	private:
		glm::vec4 m_back_ground_color;
		
	};
}

#endif