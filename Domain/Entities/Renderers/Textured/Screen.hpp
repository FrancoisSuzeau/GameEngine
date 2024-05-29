/******************************************************************************************************************************************/
// File : Screen.hpp
// Purpose : An interface for the Screen renderer
/******************************************************************************************************************************************/
#ifndef SCREEN_H
#define SCREEN_H

#include "../Untextured/Square.hpp"

namespace Renderers {



	class Screen : public IRenderer
	{
	public:

		Screen();
		~Screen();

		void Construct() override;
		void Clean() override;
		void Draw(unsigned int const texture_id, unsigned int const ping_pong_texture) override;
		void Draw(bool first_it, unsigned int const texture_id, unsigned int const ping_pong_texture) override;
		void Draw(unsigned int texture_id) override;

	private:
		void Attach();
		void Load();

		std::vector<GLfloat> m_texture_coord;
		unsigned int m_bytes_textcoord_size;
		typedef IRenderer base;



	};
}

#endif