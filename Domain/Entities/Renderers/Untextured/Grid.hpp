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
		Grid(const int grid_size, const float grid_spacing);
		~Grid();

		void Construct() override;
		void Clean() override;
		void Draw() override;


	private:
		void Attach();
		void Load();

		typedef IRenderer base;

		
		int const m_grid_size;
		float const m_grid_spacing;

		std::vector<glm::vec3> m_vec_vertices;
		std::vector<unsigned int> m_vec_indices;


	};
}

#endif