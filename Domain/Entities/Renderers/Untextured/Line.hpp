/******************************************************************************************************************************************/
// File : Line.hpp
// Purpose : An interface for the Line renderer
/******************************************************************************************************************************************/
#ifndef LINE_H
#define LINE_H

#include "../../../Interfaces/IRenderer.hpp"

namespace Renderers {



	class Line : public IRenderer
	{
	public:

		Line();
		~Line();

		void Construct() override;
		void Draw() override;
		void Draw(std::vector<unsigned int> light_texture_ids) override;
		void Clean();

	protected:
		void Load() override;

	private:
		void Attach();

		/*GLuint m_cbo;*/
		size_t m_bytes_colors_size;
		std::vector<GLfloat> m_colors;
		typedef IRenderer base;



	};
}

#endif