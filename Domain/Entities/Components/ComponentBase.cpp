/******************************************************************************************************************************************/
// File : ComponentBase.cpp
// Purpose : Implementing the basic component view
/******************************************************************************************************************************************/

#include "ComponentBase.hpp"

namespace Component
{
	ComponentBase::ComponentBase(glm::vec3 const position, glm::vec3 const size, Enums::RendererType const type, glm::vec4 const color, 
		bool const is_light_source, float const ambiant_occlusion, int const specular_shininess, float const specular_strength)
	{
		m_type = type;

		m_model_mat = glm::mat4(1.f);
		m_position = position;
		m_size = size;
		m_hovered = false;
		m_selected = false;
		m_angle = 0.f;
		m_back_ground_color = color;
		m_is_light_source = is_light_source;
		m_ambiant_occlusion = ambiant_occlusion;
		m_specular_shininess = specular_shininess;
		m_specular_strength = specular_strength;
	}

	void ComponentBase::Clean()
	{

	}
}