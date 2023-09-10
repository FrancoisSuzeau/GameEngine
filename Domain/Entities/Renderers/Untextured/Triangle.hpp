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
		Triangle();
		~Triangle();

		void Construct() override;
		void Clean() override;
		void Render(GLuint const program_id) override;

	private:
		void Attach();
		void Load();
		void CleanVbo();
		void CleanVao();

		
	};
}

#endif