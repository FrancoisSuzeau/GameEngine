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