/******************************************************************************************************************************************/
// File : GraphicInitializerService.cpp
// Purpose : Implementing service Opengl / SDL  initialisation
/******************************************************************************************************************************************/
#include "GraphicInitializerService.hpp"

using namespace Services;

void GraphicInitializerService::Init()
{
	
	init_succeded = true;
	title = "Graphic Services Initialization";
	InitialiseSDL();
	assert(init_succeded);
	std::cout << ">> Initialise SDL : SUCCESS" << std::endl;
	SetGLAttributes();
	assert(init_succeded);
	std::cout << ">> Initialise SDL GL Attributes : SUCCESS" << std::endl;
	SetDimensions();
	assert(init_succeded);
	std::cout << ">> Initialise Window Dimensions : SUCCESS" << std::endl;
	SetSDLWindow();
	assert(init_succeded);
	std::cout << ">> Initialise SDL Window : SUCCESS" << std::endl;
	SetSDLGLContext();
	assert(init_succeded);
	std::cout << ">> Initialise SDL GL Context : SUCCESS" << std::endl;
	InitGlew();
	assert(init_succeded);
	std::cout << ">> Initialise Glew : SUCCESS" << std::endl;

	int major_version;
	int minor_version;

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major_version);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor_version);

	std::cout << ">> OpenGL version : " << major_version << "." << minor_version << " ready." << std::endl;
	glEnable(GL_DEPTH_TEST);
}

void GraphicInitializerService::DeInit()
{
	title = "Graphic Services De-initialization";
	DestroySDLGLContext();
	DestroySDLWindow();
	DeInitSDL();
	std::cout << ">> All SDL / OpenGL Services destroyed" << std::endl;
}

void GraphicInitializerService::InitialiseSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::string error_message = "Cannot initialize SDL with param : SDL_INIT_VIDEO\n";
		ShowError(error_message);
	}
}

void GraphicInitializerService::SetGLAttributes()
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

void GraphicInitializerService::SetDimensions()
{
	m_width = GetSystemMetrics(SM_CXSCREEN);
	m_height = GetSystemMetrics(SM_CYSCREEN);
}

void GraphicInitializerService::SetSDLWindow()
{
	m_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (m_window == nullptr)
	{
		std::string error_message = "Cannot create SDL window\n";
		ShowError(error_message);
		SDL_Quit();
	}
}

void GraphicInitializerService::SetSDLGLContext()
{
	gl_context = SDL_GL_CreateContext(m_window);
	if (gl_context == 0)
	{
		std::string error_message = "Cannot create SDL GL context\n";
		ShowError(error_message);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}
}

void GraphicInitializerService::InitGlew()
{
	GLenum glew = 0;
	glew = glewInit();
	if (glew != GLEW_OK)
	{
		std::string error_message("Cannot initialize glew\n");
		error_message.append("Glew error : ");
		error_message.append((const char*)glewGetErrorString(glew));
		ShowError(error_message);
		SDL_GL_DeleteContext(gl_context);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}
}

void GraphicInitializerService::DestroySDLWindow()
{
	std::string status_msg = ">> Destroying SDL Window : ";
	SDL_DestroyWindow(m_window);
	std::string sdl_error(SDL_GetError());
	status_msg += (sdl_error == "") ? "SUCCESS" : sdl_error;
	std::cout << status_msg << std::endl;
}

void GraphicInitializerService::DestroySDLGLContext()
{
	std::string status_msg = ">> Destroying SDL GL Context : ";
	if (gl_context == 0)
	{
		status_msg += "ERROR";
	}
	else
	{
		SDL_GL_DeleteContext(gl_context);
		status_msg += "SUCCESS";
	}
	std::cout << status_msg << std::endl;
}

void GraphicInitializerService::DeInitSDL()
{
	SDL_Quit();
}

void GraphicInitializerService::ShowError(std::string error_message)
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


