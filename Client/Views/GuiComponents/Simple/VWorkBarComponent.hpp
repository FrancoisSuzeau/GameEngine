/******************************************************************************************************************************************/
// File : VWorkBarComponent.hpp
// Purpose : The GUI view of work bar vertical
/******************************************************************************************************************************************/
#ifndef VWORRKBARCOMPONENT_H
#define VWORRKBARCOMPONENT_H

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
	class VWorkBarComponent : public IView
	{

	public:
		~VWorkBarComponent() override;
		VWorkBarComponent(std::shared_ptr<ViewModels::IViewModel> parent);
		void Render() override;
	private:
		std::shared_ptr < Services::StateService> m_state_service;
		std::shared_ptr<Services::FramebufferService> m_framebuffer_service;
		std::shared_ptr<Services::LoaderService> m_loader_service;
		std::shared_ptr<Services::RunTimeService> m_runtime_service;
		std::shared_ptr<Services::PhysicsService> m_physics_service;
		std::shared_ptr<Services::ShaderService> m_shader_service;
		std::shared_ptr<Services::CameraService> m_camera_service;
		void RenderPropertiesTab(std::shared_ptr<Component::IComponent> selected_renderer);
		void RenderOtherFunTab(std::shared_ptr<Component::IComponent> selected_renderer);
		void RenderAppearanceTab(std::shared_ptr<Component::IComponent> selected_renderer);
		void RenderLightTab(std::shared_ptr<Component::IComponent> selected_renderer);
		void RenderCustomizeSelectedCpSection(ImGuiTabBarFlags tab_bar_flags, ImGuiWindowFlags window_flags2);
		void RenderGeneralFunctionnalities(ImGuiWindowFlags window_flags2);
		void RenderDebugFunctionnalities(ImGuiWindowFlags window_flags2);
		void RenderCameraDatas(ImGuiWindowFlags window_flags2);
		bool show_color_picker;
		int item_current;
		int item_model_current;
		int current_tab;
		std::vector<ImVec2> tabs_size;
		std::string m_selected_skybox;
		bool is_there_light_directional_source;
	};
}

#endif