/******************************************************************************************************************************************/
// File : TriangleTextured.hpp
// Purpose : An interface for the TriangleTextured renderer
/******************************************************************************************************************************************/
#ifndef TRIANGLETEXTURED_H
#define TRIANGLETEXTURED_H

#include "../../../Interfaces/IRenderer.hpp"

namespace Renderers {



	class TriangleTextured : public IRenderer
	{
	public:

		TriangleTextured();
		~TriangleTextured();

		void Construct() override;
		void Clean() override;
		void Draw(unsigned int const texture_id) override;

	private:
		void Attach();
		void Load();

		std::vector<GLfloat> m_texture_coord;
		unsigned int m_bytes_textcoord_size;

		typedef IRenderer base;

	};
}

#endif