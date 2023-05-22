/******************************************************************************************************************************************/
// File : GraphicService.hpp
// Purpose : A service initialising Opengl / SDL
/******************************************************************************************************************************************/
#ifndef GRAPHICSERVICES_H
#define GRAPHICSERVICES_H

#include <iostream>
#include <SDL2/SDL.h>
#include <windows.h>

#include "IService.hpp"

#define QUIT_SDL 1

namespace Services {

	class GraphicServices : public IService
	{

	public : 
		bool Init() override;
		void DeInit() override;
 
	private: 
		void InitialiseSDL();
		void SetGLAttributes();
		void SetDimensions();
		void SetSDLWindow();

		void DestroySDLWindow();
		void DeInitSDL();
		void ShowError(std::string error_message) override;

		int m_width;
		int m_height;
		SDL_Window* m_window = nullptr;
	};
}

#endif