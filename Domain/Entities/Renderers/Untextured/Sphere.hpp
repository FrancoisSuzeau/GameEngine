/******************************************************************************************************************************************/
// File : Sphere.hpp
// Purpose : An interface for the Sphere renderer
/******************************************************************************************************************************************/
#ifndef SPHERE_H
#define SPHERE_H

#include "../../../Interfaces/IRenderer.hpp"
#include <SDL2/SDL.h>

namespace Renderers {



	class Sphere : public IRenderer
	{
	public:
		Sphere(float radius, unsigned int long_seg, unsigned int lat_seg);
		~Sphere();

		void Construct() override;
		void Draw() override;
		void Draw(unsigned int const light_src_texture_id) override;
		void Clean();

	protected:

		void Load() override;

		float m_radius;
		unsigned int m_long_seg;
		unsigned int m_lat_seg;

	private:
		void Attach();
		

		typedef IRenderer base;






	};
}

#endif