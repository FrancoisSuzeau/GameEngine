/******************************************************************************************************************************************/
// File : SquareTextured.hpp
// Purpose : An interface for the SquareTextured renderer
/******************************************************************************************************************************************/
#ifndef SQUARETEXTURED_H
#define SQUARETEXTURED_H

#include "../Untextured/Square.hpp"

namespace Renderers {

	

	class SquareTextured : public IRenderer
	{
	public:

		SquareTextured();
		~SquareTextured();

		void Construct() override;
		void Clean() override;
		void Draw(unsigned int const texture_id, unsigned int const light_src_texture_id) override;
		void Draw(unsigned int texture_id) override;

	private:
		void Attach();
		void Load();

		std::vector<GLfloat> m_texture_coord;
		unsigned int m_bytes_textcoord_size;
		typedef IRenderer base;
		


	};
}

#endif