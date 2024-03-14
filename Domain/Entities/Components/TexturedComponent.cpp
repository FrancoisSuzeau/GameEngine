/******************************************************************************************************************************************/
// File : TexturedComponent.cpp
// Purpose : Implementing the basic component view
/******************************************************************************************************************************************/

#include "TexturedComponent.hpp"

namespace Component {
	TexturedComponent::TexturedComponent(glm::vec3 position, glm::vec3 size, Enums::RendererType type, unsigned int texture_id) : m_texture_id(texture_id)
	{
		m_type = type;

		m_model_mat = glm::mat4(1.f);
		m_position = position;
		m_size = size;
		m_hovered = false;
		m_selected = false;
		m_angle = 0.f;
	}
	
	unsigned int TexturedComponent::GetTextureId() const
	{
		return m_texture_id;
	}
}