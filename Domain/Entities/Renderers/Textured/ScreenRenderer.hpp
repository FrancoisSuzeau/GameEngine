/******************************************************************************************************************************************/
// File : ScreenRenderer.hpp
// Purpose : An interface for the SquareTextured renderer
/******************************************************************************************************************************************/
#ifndef SCREENRENDERER_H
#define SCREENRENDERER_H

#include "../Untextured/Square.hpp"

namespace Renderers {

	

	class ScreenRenderer : public IRenderer
	{
	public:

		ScreenRenderer();
		~ScreenRenderer();

		void Construct() override;
		void Clean() override;
		void Draw() override;

		unsigned int GetTextureId() const;
		void SetTextureID(unsigned int const texture_id);

	private:
		void Attach();
		void Load();

		std::vector<GLfloat> m_texture_coord;
		unsigned int m_bytes_textcoord_size;
		typedef IRenderer base;
		unsigned int m_texture_id;


	};
}

#endif