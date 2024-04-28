/******************************************************************************************************************************************/
// File : TexturedComponent.cpp
// Purpose : Implementing the basic component view
/******************************************************************************************************************************************/

#include "TexturedComponent.hpp"

namespace Component {
	TexturedComponent::TexturedComponent(glm::vec3 position, glm::vec3 size, Enums::RendererType type, unsigned int texure_id) : m_texture_id(texure_id)
	{
		m_type = type;

		m_model_mat = glm::mat4(1.f);
		m_position = position;
		m_size = size;
		m_hovered = false;
		m_selected = false;
		m_angle = 0.f;
		m_horizontal = true;
	}

	void TexturedComponent::Clean()
	{
		this->DestroyTexture();
	}

	bool TexturedComponent::GetHorizontal()
	{
		return m_horizontal;
	}

	void TexturedComponent::SetHorizontal(bool const new_val)
	{
		m_horizontal = new_val;
	}
	
	unsigned int TexturedComponent::GetTextureId() const
	{
		return m_texture_id;
	}

	void TexturedComponent::DestroyTexture()
	{
		if (m_texture_id != 0)
		{
			glDeleteTextures(1, &m_texture_id);
			m_texture_id = 0;
		}
	}
}