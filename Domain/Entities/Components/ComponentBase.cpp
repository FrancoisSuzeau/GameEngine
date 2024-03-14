/******************************************************************************************************************************************/
// File : ComponentBase.cpp
// Purpose : Implementing the basic component view
/******************************************************************************************************************************************/

#include "ComponentBase.hpp"

namespace Component
{
	ComponentBase::ComponentBase(glm::vec3 position, glm::vec3 size, Enums::RendererType type, glm::vec4 color) : m_back_ground_color(color)
	{
		m_type = type;

		m_model_mat = glm::mat4(1.f);
		m_position = position;
		m_size = size;
		m_hovered = false;
		m_selected = false;
		m_angle = 0.f;
	}

	void ComponentBase::Clean()
	{
		
	}
	void ComponentBase::Construct()
	{
	}
	glm::vec4 ComponentBase::GetBackgroundColor() const
	{
		return m_back_ground_color;
	}
	void ComponentBase::SetBackgroundColor(glm::vec4 new_bacground_color)
	{
		m_back_ground_color = new_bacground_color;
	}
}