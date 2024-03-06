/******************************************************************************************************************************************/
// File : WorkBarComponent.hpp
// Purpose : The GUI view of start
/******************************************************************************************************************************************/
#ifndef WORKBARCOMPONENT_H
#define WORKBARCOMPONENT_H

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

#include <iostream>
#include <list>
#include "Commands/Commands.hpp"

namespace Views
{
	class WorkBarComponent : public IView
	{

	public:
		~WorkBarComponent() override;
		WorkBarComponent();
		void Render() override;
	private:
		std::shared_ptr < Services::StateService> m_state_service;
		void RenderPropertiesTab(std::shared_ptr<Renderers::IRenderer> selected_renderer);
		void RenderInfosTab(std::shared_ptr<Renderers::IRenderer> selected_renderer);
		void RenderAppearanceTab(std::shared_ptr<Renderers::IRenderer> selected_renderer);
		void RenderCustomizeSelectedCpSection(ImGuiTabBarFlags tab_bar_flags, ImGuiWindowFlags window_flags2);
		void RenderGeneralFunctionnalities(ImGuiWindowFlags window_flags2);
		bool show_color_picker;
		int item_current;
	};
}

#endif