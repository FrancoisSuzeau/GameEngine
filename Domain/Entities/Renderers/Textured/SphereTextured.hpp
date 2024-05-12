/******************************************************************************************************************************************/
// File : SphereTextured.hpp
// Purpose : An interface for the SphereTextured renderer
/******************************************************************************************************************************************/
#ifndef SPHERETEXTURED_H
#define SPHERETEXTURED_H

#include "../../../Interfaces/IRenderer.hpp"
#include <SDL2/SDL.h>

namespace Renderers {



	class SphereTextured : public IRenderer
	{
	public:
		SphereTextured(float radius, unsigned int long_seg, unsigned int lat_seg);
		~SphereTextured();

		void Construct() override;
		void Draw(unsigned int texture_id) override;
		void Clean();

	private:
		void Attach();
		void Load();

		typedef IRenderer base;

		float m_radius;
		unsigned int m_long_seg;
		unsigned int m_lat_seg;

		std::vector<GLfloat> m_texture_coord;
		unsigned int m_bytes_textcoord_size;




	};
}

#endif