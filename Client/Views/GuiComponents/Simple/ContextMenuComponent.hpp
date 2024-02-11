/******************************************************************************************************************************************/
// File : ContextMenuComponent.hpp
// Purpose : The GUI view of save as
/******************************************************************************************************************************************/
#ifndef CONTEXTMENUCOMPONENT_H
#define CONTEXTMENUCOMPONENT_H

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
	class ContextMenuComponent : public IView
	{

	public:
		~ContextMenuComponent() override;
		ContextMenuComponent();
		void Render() override;
	private:
		std::shared_ptr < Services::StateService> m_state_service;
		void RenderColorPicker(std::shared_ptr<Renderers::IRenderer> selected_renderer);
		void RenderSizer(std::shared_ptr<Renderers::IRenderer> selected_renderer);
		bool show_color_picker;
	};
}

#endif