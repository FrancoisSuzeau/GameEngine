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
		TexturedComponent(glm::vec3 position, glm::vec3 size, Enums::RendererType type);
		unsigned int GetTextureId() const;
		void SetTextureId(unsigned int const texure_id);
		void Clean() override;

	private:
		unsigned int m_texture_id;
		void DestroyTexture();

	};
}

#endif