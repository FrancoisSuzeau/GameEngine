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
		void Draw(std::vector<unsigned int> light_texture_ids) override;
		void Clean();

	protected:
		void Load() override;

	private:
		void Attach();
		

		typedef IRenderer base;


	};
}

#endif