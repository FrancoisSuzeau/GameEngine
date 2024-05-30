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

	protected:
		void Load() override;

	private:
		void Attach();
		

		typedef IRenderer base;


	};
}

#endif