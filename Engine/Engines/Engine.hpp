/******************************************************************************************************************************************/
// File : Engine.hpp
// Purpose : The main engine of the application
/******************************************************************************************************************************************/
#ifndef ENGINE_H
#define ENGINE_H

#include <string>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#define  IMGUI_INITIALIZE 0
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL2/SDL_opengl.h>
#endif
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

#include "IEngine.hpp"
#include "EngineEnum.hpp"
#include "Container/Container.hpp"
#include "../Services/GraphicInitializerService.hpp"

namespace Engines {

	class Engine : public IEngine
	{
	public:

		~Engine();
		void Construct() override;
		void MainLoop();

	private:
		SDL_Window* m_window;
		Uint32                  start_loop = 0, end_loop = 0, time_past = 0;
		unsigned int            frame_rate = 0;
		int m_width = 0, m_height = 0;


		void InitFrame();
		void EndFrame();
		void FpsCalculation(Enums::EngineEnum ee);
	};
}

#endif