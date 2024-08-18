/******************************************************************************************************************************************/
// File : Mesh.hpp
// Purpose : An interface for the Mesh renderer
/******************************************************************************************************************************************/
#ifndef MESH_H
#define MESH_H

#define MAX_BONE_INFLUENCE 4

#include "../../../Interfaces/IRenderer.hpp"

#include <iostream>
#include <string>

namespace Renderers {

    typedef struct Vertex {

        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texture_coords;

        // tangent
        glm::vec3 tangent;
        // bitangent
        glm::vec3 bitangent;
        //bone indexes which will influence this vertex
        int m_bone_ids[MAX_BONE_INFLUENCE];
        //weights from each bone
        float m_weights[MAX_BONE_INFLUENCE];

    } Vertex;

    typedef struct Texturate {

        unsigned int id = 0;
        std::string type;
        std::string path;

    } Texturate;

	class Mesh : public IRenderer
	{
	public:

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texturate> textures);
        Mesh();
		~Mesh();

		void Construct() override;
		void Clean() override;

        void Draw() override;
		

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