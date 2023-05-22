/******************************************************************************************************************************************/
// File : GraphicService.cpp
// Purpose : Implementing service Opengl / SDL  initialisation
/******************************************************************************************************************************************/
#include "GraphicServices.hpp"

using namespace Services;

bool GraphicServices::Init()
{
	init_succeded = true;
	title = "Graphic Services Initialization";
	InitialiseSDL();
	SetGLAttributes();
	SetDimensions();
	SetSDLWindow();
	return init_succeded;
}

void GraphicServices::DeInit()
{
	title = "Graphic Services De-initialization";
	DestroySDLWindow();
	DeInitSDL();
	std::cout << ">> All SDL Services destroyed" << std::endl;
}

void GraphicServices::InitialiseSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::string error_message = "Cannot initialize SDL with param : SDL_INIT_VIDEO\n";
		ShowError(error_message);
	}
}

void GraphicServices::SetGLAttributes()
{
	std::string error_message;
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) < 0)
	{
		error_message = "Cannot set Open GL Major version to 4\n";
		ShowError(error_message);
		SDL_Quit();
	}

	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0) < 0)
	{
		error_message = "Cannot set Open GL minor version to 0\n";
		ShowError(error_message);
		SDL_Quit();
	}

	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY) < 0)
	{
		error_message = "Cannot set Open GL Attributes with param : SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY\n";
		ShowError(error_message);
		SDL_Quit();
	}
}

void GraphicServices::SetDimensions()
{
	m_width = GetSystemMetrics(SM_CXSCREEN);
	m_height = GetSystemMetrics(SM_CYSCREEN);
}

void GraphicServices::SetSDLWindow()
{
	m_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (m_window == nullptr)
	{
		std::string error_message = "Cannot create SDL window\n";
		ShowError(error_message);
		SDL_Quit();
	}
}

void GraphicServices::DestroySDLWindow()
{
	std::string status_msg = ">> Destroying SDL Window : ";
	SDL_DestroyWindow(m_window);
	std::string sdl_error(SDL_GetError());
	status_msg += (sdl_error == "") ? "SUCCESS" : sdl_error;
	std::cout << status_msg << std::endl;
}

void GraphicServices::DeInitSDL()
{
	SDL_Quit();
}

void GraphicServices::ShowError(std::string error_message)
{
	std::string sdl_error(SDL_GetError());
	if (sdl_error != "")
	{
		error_message.append("SDL Error : ");
		error_message.append(sdl_error.c_str());
		error_message.append("\n");
	}
	
	MessageBoxA(0, error_message.c_str(), title.c_str(), MB_ICONERROR | MB_OK);
	init_succeded = false;
}


