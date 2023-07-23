/******************************************************************************************************************************************/
// File : GraphicInitializerService.hpp
// Purpose : A service initialising Opengl / SDL
/******************************************************************************************************************************************/
#ifndef GRPHINITSERVICE_H
#define GRPHINITSERVICE_H

#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <cassert>

#include "IService.hpp"
#include "Logger.hpp"
#include "Constants/NumberConstants.hpp"

namespace Services {

	class GraphicInitializerService : public IService
	{

	public : 
		void Init() override;
		void DeInit() override;

		SDL_GLContext GetGLContext() const;
		SDL_Window* GetSDLWindow() const;
		int GetWidth() const;
		int GetHeight() const;
 
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

		int m_width;
		int m_height;
		SDL_Window* m_window = nullptr;
		SDL_GLContext gl_context = 0;
		bool init_succeded;
	};
}

#endif