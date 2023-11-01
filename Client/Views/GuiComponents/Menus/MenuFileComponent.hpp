/******************************************************************************************************************************************/
// File : MenuFileComponent.hpp
// Purpose : The GUI view of the file menu
/******************************************************************************************************************************************/
#ifndef MENUFILECOMPONENT_H
#define MENUFILECOMPONENT_H

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

#include "IView.hpp"
#include "Commands/Commands.hpp"
#include "Services/Services.hpp"
#include "Container/Container.hpp"
#include <functional>


#include <iostream>
#include <list>

namespace Views
{
	class MenuFileComponent : public IView
	{

	public:

		MenuFileComponent();
		~MenuFileComponent() override;
		void Render() override;
		void SetSceneViewModel(ViewModels::IViewModel* scene_viewmodel);
	private:
		std::shared_ptr<Services::StateService> m_state_service;
		std::shared_ptr<ViewModels::IViewModel> m_scene_viewmodel;
		bool show_save_as;
		void ShowSaveAsWindow(int w_width, int w_height);
		void SaveScene();
		char filename[128];
 	};
}

#endif