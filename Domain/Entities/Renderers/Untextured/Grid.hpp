/******************************************************************************************************************************************/
// File : Grid.hpp
// Purpose : An interface for the Grid renderer
/******************************************************************************************************************************************/
#ifndef GRID_H
#define GRID_H

#include "../../../Interfaces/IRenderer.hpp"

namespace Renderers {



	class Grid : public IRenderer
	{
	public:
		Grid(int slices);
		~Grid();

		void Construct() override;
		void Clean() override;
		void Draw() override;
		GLint GetLength() const override;


	private:
		void Attach();
		void Load();

		typedef IRenderer base;

		std::vector<glm::vec3> m_vec_vertices;
		std::vector<glm::uvec4> m_vec_indices;
		size_t m_bytes_indices_size;
		GLint m_lenght;
		int m_slices;



	};
}

#endif