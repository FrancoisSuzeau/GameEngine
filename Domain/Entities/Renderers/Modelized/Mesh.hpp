/******************************************************************************************************************************************/
// File : Mesh.hpp
// Purpose : An interface for the Mesh renderer
/******************************************************************************************************************************************/
#ifndef MESH_H
#define MESH_H



#include "../../../Interfaces/IRenderer.hpp"

#include <iostream>
#include <string>

namespace Renderers {

    

	class Mesh : public IRenderer
	{
	public:

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texturate> textures);
        Mesh();
		~Mesh();

		void Construct() override;
		void Clean() override;

        void Draw() override;
		void Draw(std::vector<unsigned int> light_textures_ids) override;

		std::vector<Texturate> GetMeshTextures() const override;
		
		

	protected:
		void Load() override;

	private:
		void Attach();

        std::vector<Vertex>         m_mesh_vertices;
        std::vector<Texturate>      m_mesh_textures;

		typedef IRenderer base;

	};
}

#endif