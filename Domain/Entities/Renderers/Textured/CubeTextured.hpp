/******************************************************************************************************************************************/
// File : CubeTextured.hpp
// Purpose : An interface for the CubeTextured renderer
/******************************************************************************************************************************************/
#ifndef CUBETEXTURED_H
#define CUBETEXTURED_H

#include "../Untextured/Cube.hpp"

namespace Renderers {



	class CubeTextured : public Cube
	{
	public:

		CubeTextured();
		~CubeTextured();

		void Construct() override;
		void Clean() override;
		void Draw(unsigned int const texture_id) override;
		void Draw(unsigned int const texture_id, unsigned int const light_src_texture_id) override;

	protected:
		void Load() override;

	private:
		void Attach();

		std::vector<GLfloat> m_texture_coord;
		unsigned int m_bytes_textcoord_size;

		typedef Cube base;

	};
}

#endif