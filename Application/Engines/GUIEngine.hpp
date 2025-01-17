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
#include "../Services/LoaderService.hpp"

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

		void RenderGuiComponents(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder);
		void RenderMainMenuBar(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder);
		void RenderLoader(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder, int const index);
		void LoadAvailableSkyboxChoices(int const index) const;
		void LoadSkyboxCube(int const index) const;
		void LoadAvailableTextures(int const index) const;
		void LoadConfigs();

	private:
		ImGuiIO m_io;
		std::shared_ptr<Services::StateService> m_state_service;
		std::shared_ptr<Services::LoaderService> m_loader_service;
		
		
	};
}

#endif