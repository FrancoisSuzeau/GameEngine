/******************************************************************************************************************************************/
// File : Square.hpp
// Purpose : An interface for the Square renderer
/******************************************************************************************************************************************/
#ifndef SQUARE_H
#define SQUARE_H

#include "../../../Interfaces/IRenderer.hpp"

namespace Renderers {

	

	class Square : public IRenderer
	{
	public:
		
		Square();
		~Square();

		void Construct() override;
		void Clean() override;
		void Draw() override;
		void Draw(std::vector<unsigned int> light_texture_ids) override;


	protected:
		
		void Load() override;

	private:

		void Attach();
		typedef IRenderer base;


	};
}

#endif