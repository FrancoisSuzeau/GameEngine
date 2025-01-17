/******************************************************************************************************************************************/
// File : SquareTextured.hpp
// Purpose : An interface for the SquareTextured renderer
/******************************************************************************************************************************************/
#ifndef SQUARETEXTURED_H
#define SQUARETEXTURED_H

#include "../Untextured/Square.hpp"

namespace Renderers {

	

	class SquareTextured : public Square
	{
	public:

		SquareTextured();
		~SquareTextured();

		void Construct() override;
		void Clean() override;
		void Draw(unsigned int const texture_0, std::vector<unsigned int> light_texture_ids) override;
		void Draw(unsigned int texture_id) override;

	protected:
		void Load() override;

	private:
		void Attach();
		

		std::vector<GLfloat> m_texture_coord;
		unsigned int m_bytes_textcoord_size;
		typedef Square base;
		


	};
}

#endif