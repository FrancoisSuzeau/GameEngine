/******************************************************************************************************************************************/
// File : GraphicService.hpp
// Purpose : A service initialising Opengl / SDL
/******************************************************************************************************************************************/
#ifndef GRAPHICSERVICES_H
#define GRAPHICSERVICES_H

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <cassert>
#include <windows.h>

namespace Services {

	class GraphicServices 
	{

	public : 
		void Init();
		void DeInit();
 
	private:
		void InitialiseSDL();
		void SetGLAttributes();
		void SetDimensions();
		void SetSDLWindow();
		void SetSDLGLContext();
		void InitGlew();

		void DestroySDLWindow();
		void DestroySDLGLContext();
		void DeInitSDL();

		void ShowError(std::string error_message);

		int m_width;
		int m_height;
		SDL_Window* m_window = nullptr;
		SDL_GLContext gl_context = 0;
		bool init_succeded;
		std::string title;
	};
}

#endif