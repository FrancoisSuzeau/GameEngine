/******************************************************************************************************************************************/
// File : HWorkBarComponent.hpp
// Purpose : The GUI view of work bar vertical
/******************************************************************************************************************************************/
#ifndef HWORRKBARCOMPONENT_H
#define HWORRKBARCOMPONENT_H

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
#include "Services/CameraService.hpp"
#include "Container/Container.hpp"
#include "Services/FramebufferService.hpp"
#include "Services/LoaderService.hpp"
#include "Services/PhysicsService.hpp"
#include "Services/ShaderService.hpp"
#include "IComponent.hpp"
#include "IViewModel.hpp"

#include <iostream>
#include <list>
#include "Commands/ModifySceneCommand.hpp"


#include <map>

namespace Views
{
	class HWorkBarComponent : public IView
	{

	public:
		~HWorkBarComponent() override;
		HWorkBarComponent(std::shared_ptr<ViewModels::IViewModel> parent);
		void Render() override;
	private:
		std::shared_ptr < Services::StateService> m_state_service;
	};
}

#endif