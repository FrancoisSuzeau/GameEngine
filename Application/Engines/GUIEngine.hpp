/******************************************************************************************************************************************/
// File : GUIEngine.hpp
// Purpose : The GUI engine of the application
/******************************************************************************************************************************************/
#ifndef GUIENGINE_H
#define GUIENGINE_H

#include <string>

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

#include "IEngine.hpp"
#include "Container/Container.hpp"
#include "../Services/ImGUIServiceInitalizer.hpp"
#include "../Services/StateService.hpp"
#include "../Commands/ExitCommand.hpp"
#include "../Builders/ViewModelBuilder.hpp"


#include <iostream>

namespace Engines {

	class GUIEngine : public IEngine
	{
	public:

		~GUIEngine();
		void Construct() override;

		void InitFrame() override; 
		void EndFrame() override;

		void RenderGuiComponents();

		

	private:
		ImGuiIO m_io;
		void RenderMainMenuBar();
		void RenderMenuFile();
		void RenderMenuEdit();
		void RenderMenuTools();
		std::shared_ptr<Services::StateService> m_state_service;
		bool show_app_style_editor = false;
		bool show_app_about = false;
	};
}

#endif