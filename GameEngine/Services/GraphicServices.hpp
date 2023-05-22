/******************************************************************************************************************************************/
// File : GraphicService.hpp
// Purpose : A service initialising Opengl / SDL
/******************************************************************************************************************************************/
#ifndef GRAPHICSERVICES_H
#define GRAPHICSERVICES_H

#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <windows.h>
#include <cassert>

#include "IService.hpp"

#define QUIT_SDL 1

namespace Services {

	class GraphicServices : public IService
	{

	public : 
		void Init() override;
		void DeInit() override;
 
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

		void ShowError(std::string error_message) override;

		int m_width;
		int m_height;
		SDL_Window* m_window = nullptr;
		SDL_GLContext gl_context = 0;
	};
}

#endif