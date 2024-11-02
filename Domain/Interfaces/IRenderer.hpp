/******************************************************************************************************************************************/
// File : IRenderer.hpp
// Purpose : An interface for the renderers
/******************************************************************************************************************************************/
#ifndef IRENDERER_H
#define IRENDERER_H

#include <GL/glew.h>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#define MAX_BONE_INFLUENCE 4

namespace Enums {
	enum RendererType { 
		NONE = -1, 
		TRIANGLE = 0, 
		SQUARE = 1, 
		CUBE = 2, 
		SPHERE = 3, 
		CUBE_TEXTURED = 4, 
		SQUARE_TEXTURED = 5, 
		TRIANGLE_TEXTURED = 6,
		SPHERE_TEXTURED = 7,
		GRID = 8, 
		SKYBOX = 9, 
		SUBBGRID = 10, 
		SUBGRID2 = 11,
		MODEL = 12,
		LINEX = 13,
		LINEY = 14,
		LINEZ = 15
	};
}

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
	

	class IRenderer
	{
	public:
		virtual ~IRenderer() { }
		virtual void Construct() = 0;
		virtual void Draw() {}
		virtual void Draw(unsigned int texture_0) {}
		virtual void Draw(size_t index) {}
		virtual void Draw(size_t index, std::vector<unsigned int> light_textures_ids) {}
		virtual void Draw(std::vector<unsigned int> light_textures_ids) {}
		virtual void Draw(unsigned int const texture_0, unsigned int const texture_2) {}
		virtual void Draw(unsigned int const texture_0, std::vector<unsigned int> light_textures_ids) {}
		virtual void Draw(bool first_it, unsigned int const texture_id, unsigned int const ping_pong_texture) {}
		virtual void Actualize(int const grid_scaling_ratio) {}
		virtual void Clean()
		{
			CleanVbo();
			CleanVao();
			CleanEbo();
			m_vertices.clear();
			m_indices.clear();
			m_normals.clear();

			m_bytes_indices_size = 0;
			m_bytes_normals_size = 0;
			m_bytes_vertices_size = 0;
		}

		virtual std::vector<Texturate> GetMeshTextures() const { return std::vector<Texturate>(); } 
		virtual std::vector<Texturate> GetMeshTextures(size_t index) const { return std::vector<Texturate>(); }
		virtual size_t GetNbMeshes() const { return 0; }


	protected:
		std::vector<GLfloat> m_vertices;
		std::vector<GLfloat> m_normals;
		size_t m_bytes_vertices_size;
		size_t m_bytes_normals_size;
		GLuint m_vbo;
		GLuint m_vao;
		GLuint m_ebo;

		std::vector<unsigned int> m_indices;
		unsigned int m_bytes_indices_size;

		virtual void Load() {}

	private:
		virtual void CleanVbo()
		{
			if (m_vbo != 0)
			{
				glDeleteBuffers(1, &m_vbo);
				m_vbo = 0;
			}
		}

		 virtual void CleanVao()
		{
			if (m_vao != 0)
			{
				glDeleteVertexArrays(1, &m_vao);
				m_vao = 0;

			}
		}

		 virtual void CleanEbo()
		 {
			 if (m_ebo != 0)
			 {
				 glDeleteBuffers(1, &m_ebo);
				 m_ebo = 0;
			 }
		 }

		

		
	};
}

#endif