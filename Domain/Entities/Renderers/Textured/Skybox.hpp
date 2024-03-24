/******************************************************************************************************************************************/
// File : Skybox.hpp
// Purpose : An interface for the SquareTextured renderer
/******************************************************************************************************************************************/
#ifndef SKYBOX_H
#define SKYBOX_H

#include "../../../Interfaces/IRenderer.hpp"

namespace Renderers {



	class Skybox : public IRenderer
	{
	public:

		Skybox();
		~Skybox();

		void Construct() override;
		void Clean() override;
		void Draw(unsigned int const texture_id) override;

	private:
		void Attach();
		void Load();

		typedef IRenderer base;

	};
}

#endif