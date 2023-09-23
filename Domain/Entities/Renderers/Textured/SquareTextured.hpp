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

		
		typedef IRenderer base;
		unsigned int m_texture_id;


	};
}

#endif