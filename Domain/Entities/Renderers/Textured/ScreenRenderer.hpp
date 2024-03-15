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

	private:
		void Attach();
		void Load();

		std::vector<GLfloat> m_texture_coord;
		unsigned int m_bytes_textcoord_size;
		typedef IRenderer base;


	};
}

#endif