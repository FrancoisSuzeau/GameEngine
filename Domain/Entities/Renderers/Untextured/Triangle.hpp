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
		void Clean();
		glm::vec3 GetVertex1() const;
		glm::vec3 GetVertex2() const;
		glm::vec3 GetVertex3() const;

	private:
		void Attach();
		void Load();

		typedef IRenderer base;
		
		
	};
}

#endif