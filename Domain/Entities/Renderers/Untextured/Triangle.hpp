/******************************************************************************************************************************************/
// File : Triangle.hpp
// Purpose : An interface for the triangle renderer
/******************************************************************************************************************************************/
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../../../Interfaces/IRenderer.hpp"

namespace Renderers {

	typedef IRenderer base;

	class Triangle : public IRenderer
	{
	public:
		Triangle();
		~Triangle();

		void Construct() override;
		void Clean();
		

	private:
		void Attach();
		void Load();
		
		
	};
}

#endif