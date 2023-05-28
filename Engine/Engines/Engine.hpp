/******************************************************************************************************************************************/
// File : Engine.hpp
// Purpose : The main engine of the application
/******************************************************************************************************************************************/
#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "IEngine.hpp"
#include "EngineEnum.hpp"

namespace Engines {

	class Engine : public IEngine
	{
	public:
		Engine(SDL_Window *window);
		~Engine();
		void MainLoop();

	private:
		SDL_Window* m_window;
		Uint32                  start_loop = 0, end_loop = 0, time_past = 0;
		unsigned int            frame_rate = 0;


		void InitFrame();
		void EndFrame();
		void FpsCalculation(Enums::EngineEnum ee);
	};
}

#endif