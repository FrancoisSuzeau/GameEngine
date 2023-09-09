/******************************************************************************************************************************************/
// File : IRenderer.hpp
// Purpose : An interface for the renderers
/******************************************************************************************************************************************/
#ifndef IRENDERER_H
#define IRENDERER_H

#include "glm/vec3.hpp"

namespace Renderers {

	class IRenderer
	{
	public:
		virtual ~IRenderer() {}

	protected:
		glm::vec3 m_position;
	};
}

#endif