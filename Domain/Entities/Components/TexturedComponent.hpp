/******************************************************************************************************************************************/
// File : TexturedComponent.hpp
// Purpose : The Component view implementing basis of element on canvas
/******************************************************************************************************************************************/
#ifndef TEXTUREDCOMPONENT_H
#define TEXTUREDCOMPONENT_H


#include "../../Interfaces/IComponent.hpp"

namespace Component
{
	class TexturedComponent : public IComponent
	{
	public:
		TexturedComponent(glm::vec3 position, glm::vec3 size, Enums::RendererType type, std::string texture_name);
		unsigned int GetTextureId() const override;
		void Clean() override;
		bool GetHorizontal() override;
		void SetHorizontal(bool const new_val) override;
		std::string GetTextureName() const override;
		void SetTextureId(unsigned int texture_id) override;
		void SetTextureName(std::string const new_name) override;

	private:
		unsigned int m_texture_id;
		std::string m_texture_name;
		void DestroyTexture();
		bool m_horizontal;

	};
}

#endif