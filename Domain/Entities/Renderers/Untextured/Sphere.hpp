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
		void Clean();

	private:
		void Attach();
		void Load();

		typedef IRenderer base;

		float m_radius;
		unsigned int m_long_seg;
		unsigned int m_lat_seg;




	};
}

#endif