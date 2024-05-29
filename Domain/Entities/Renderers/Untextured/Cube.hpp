/******************************************************************************************************************************************/
// File : Cube.hpp
// Purpose : An interface for the Cube renderer
/******************************************************************************************************************************************/
#ifndef CUBE_H
#define CUBE_H

#include "../../../Interfaces/IRenderer.hpp"

namespace Renderers {



	class Cube : public IRenderer
	{
	public:
		Cube();
		~Cube();

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