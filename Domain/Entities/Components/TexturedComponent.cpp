/******************************************************************************************************************************************/
// File : TexturedComponent.cpp
// Purpose : Implementing the basic component view
/******************************************************************************************************************************************/

#include "TexturedComponent.hpp"

namespace Component {
	TexturedComponent::TexturedComponent(glm::vec3 const position, glm::vec3 const size, Enums::RendererType const type, std::string const texture_name,
		bool const mixe, bool const is_light_source, float const ambiant_occlusion) : m_texture_id(0), m_texture_name(texture_name),
		m_mixe_texture_and_color(mixe)
	{
		m_type = type;

		m_model_mat = glm::mat4(1.f);
		m_position = position;
		m_size = size;
		m_hovered = false;
		m_selected = false;
		m_angle = 0.f;
		m_horizontal = true;
		m_back_ground_color = glm::vec4(0.f, 0.f, 0.f, 1.f);
		m_is_light_source = is_light_source;
		m_ambiant_occlusion = ambiant_occlusion;
	}

	void TexturedComponent::Clean()
	{
		m_texture_id = 0;
	}

	bool TexturedComponent::GetHorizontal()
	{
		return m_horizontal;
	}

	void TexturedComponent::SetHorizontal(bool const new_val)
	{
		m_horizontal = new_val;
	}

	std::string TexturedComponent::GetTextureName() const
	{
		return m_texture_name;
	}

	void TexturedComponent::SetTextureId(unsigned int texture_id)
	{
		m_texture_id = texture_id;
	}

	void TexturedComponent::SetTextureName(std::string const new_name)
	{
		m_texture_name = new_name;
	}

	bool TexturedComponent::GetMixeTextureColor() const
	{
		return m_mixe_texture_and_color;
	}

	void TexturedComponent::SetMixeTextureColor(const bool new_val)
	{
		m_mixe_texture_and_color = new_val;
	}
	
	unsigned int TexturedComponent::GetTextureId() const
	{
		return m_texture_id;
	}
}