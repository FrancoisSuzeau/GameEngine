/******************************************************************************************************************************************/
// File : ImGUIServiceInitializer.hpp
// Purpose : A service initialising ImGUI
/******************************************************************************************************************************************/
#ifndef IMGUIINITSERVICE_H
#define IMGUIINITSERVICE_H

#include "IService.hpp"
#include "Container/Container.hpp"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "GraphicInitializerService.hpp"

#define  IMGUI_INITIALIZE 0
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL2/SDL_opengl.h>
#endif
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

namespace Services {
	class ImGUIServiceInitializer : public IService
	{
	public:
		void Init() override;
		void DeInit() override;
	private:
		ImGuiIO m_io;
	};
}
#endif