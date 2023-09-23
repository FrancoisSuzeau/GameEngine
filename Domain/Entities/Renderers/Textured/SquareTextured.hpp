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