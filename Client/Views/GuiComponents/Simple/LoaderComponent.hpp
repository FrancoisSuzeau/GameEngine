/******************************************************************************************************************************************/
// File : LoaderComponent.hpp
// Purpose : The GUI view of start
/******************************************************************************************************************************************/
#ifndef LOADERCOMPONENT_H
#define LOADERCOMPONENT_H

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
#include "Services/StateService.hpp"
#include "Container/Container.hpp"
#include "IViewModel.hpp"

#include <iostream>
#include <list>
#include "Commands/LoadSceneCommand.hpp"
#include "Commands/ExitCommand.hpp"

namespace Views
{
	class LoaderComponent : public IView
	{

	public:
		~LoaderComponent() override;
		LoaderComponent(std::shared_ptr<ViewModels::IViewModel> parent);
		void Render(int const index) override;
	private:
		std::shared_ptr < Services::StateService> m_state_service;
		int m_selected;
	};
}

#endif