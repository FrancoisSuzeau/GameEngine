/******************************************************************************************************************************************/
// File : SphereTextured.hpp
// Purpose : An interface for the SphereTextured renderer
/******************************************************************************************************************************************/
#ifndef SPHERETEXTURED_H
#define SPHERETEXTURED_H

#include "../Untextured/Sphere.hpp"
#include <SDL2/SDL.h>

namespace Renderers {



	class SphereTextured : public Sphere
	{
	public:
		SphereTextured(float radius, unsigned int long_seg, unsigned int lat_seg);
		~SphereTextured();

		void Construct() override;
		void Draw(unsigned int texture_id) override;
		void Draw(unsigned int const texture_id, unsigned int const light_src_texture_id) override;
		void Clean();

	protected:

		void Load() override;

	private:
		void Attach();
		

		typedef Sphere base;

		std::vector<GLfloat> m_texture_coord;
		unsigned int m_bytes_textcoord_size;




	};
}

#endif