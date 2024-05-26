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
		ComponentBase(glm::vec3 const position, glm::vec3 const size, Enums::RendererType const type, glm::vec4 const color, bool const is_light_source = false, float const ambiant_occlusion = 0.1f);

		
		void Clean() override;

	private:
		
		
	};
}

#endif