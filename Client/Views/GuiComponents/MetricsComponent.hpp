/******************************************************************************************************************************************/
// File : MetricsComponent.hpp
// Purpose : The GUI view model of the application
/******************************************************************************************************************************************/
#ifndef METRICSCOMPONENT_H
#define METRICSCOMPONENT_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

#define  IMGUI_INITIALIZE 0
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL2/SDL_opengl.h>
#endif
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include "IGuiComponent.hpp"

#include <iostream>
#include <list>

namespace Views
{
	class MetricsComponent : public IGuiComponent
	{

	public:
		void Render(bool show = true) override;
	};
}

#endif