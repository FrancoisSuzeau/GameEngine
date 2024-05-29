/******************************************************************************************************************************************/
// File : Triangle.hpp
// Purpose : An interface for the triangle renderer
/******************************************************************************************************************************************/
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../../../Interfaces/IRenderer.hpp"

namespace Renderers {

	

	class Triangle : public IRenderer
	{
	public:
		Triangle() ;
		~Triangle();

		void Construct() override;
		void Draw() override;
		void Draw(unsigned int const light_src_texture_id) override;
		void Clean();

	private:
		void Attach();
		void Load();

		typedef IRenderer base;
		
		
	};
}

#endif