/******************************************************************************************************************************************/
// File : Axis.hpp
// Purpose : An interface for the Axis renderer
/******************************************************************************************************************************************/
#ifndef AXIS_H
#define AXIS_H

#include "../../../Interfaces/IRenderer.hpp"

namespace Renderers {



	class Axis : public IRenderer
	{
	public:

		Axis();
		~Axis();

		void Construct() override;
		void Draw() override;
		void Clean();

	protected:
		void Load() override;

	private:
		void Attach();


		size_t m_bytes_colors_size;
		std::vector<GLfloat> m_colors;
		typedef IRenderer base;



	};
}

#endif