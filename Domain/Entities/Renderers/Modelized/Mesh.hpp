/******************************************************************************************************************************************/
// File : Mesh.hpp
// Purpose : An interface for the Mesh renderer
/******************************************************************************************************************************************/
#ifndef MESH_H
#define MESH_H

#define MAX_BONE_INFLUENCE 4

#include "../../Interfaces/IRenderer.hpp"

namespace Renderers {

	class Mesh : public IRenderer
	{
	public:

		Mesh();
		~Mesh();

		void Construct() override;
		void Clean() override;
		

	protected:
		void Load() override;

	private:
		void Attach();

		typedef IRenderer base;

	};
}

#endif