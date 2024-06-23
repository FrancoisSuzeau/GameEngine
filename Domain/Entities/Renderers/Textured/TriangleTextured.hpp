/******************************************************************************************************************************************/
// File : TriangleTextured.hpp
// Purpose : An interface for the TriangleTextured renderer
/******************************************************************************************************************************************/
#ifndef TRIANGLETEXTURED_H
#define TRIANGLETEXTURED_H

#include "../Untextured/Triangle.hpp"

namespace Renderers {



	class TriangleTextured : public Triangle
	{
	public:

		TriangleTextured();
		~TriangleTextured();

		void Construct() override;
		void Clean() override;
		void Draw(unsigned int const texture_id) override;
		void Draw(unsigned int const texture_0, std::vector<unsigned int> light_texture_ids) override;

	protected:
		void Load() override;

	private:
		void Attach();
		

		std::vector<GLfloat> m_texture_coord;
		unsigned int m_bytes_textcoord_size;

		typedef Triangle base;

	};
}

#endif