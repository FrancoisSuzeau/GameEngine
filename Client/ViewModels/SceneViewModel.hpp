/******************************************************************************************************************************************/
// File : SceneViewModel.hpp
// Purpose : The scene view model of the application
/******************************************************************************************************************************************/
#ifndef SCENEVIEWMODEL_H
#define SCENEVIEWMODEL_H

#include "IViewModel.hpp"
#include "../Views/Views.hpp"
#include "Container/Container.hpp"
#include "../Views/Transformer.hpp"


#include <iostream>
#include <map>

namespace ViewModels
{
	class SceneViewModel : public IViewModel
	{

	public:
		~SceneViewModel() override;
		void Construct() override;
		
		void RenderComponents() override;
		void ManageComponents() override;
		void RenderFrameBuffer(unsigned int fb_texture_id) override;
		void RenderSkybox(unsigned int skybox_texture_id) override;
		void RenderGrid() override;
		
	private:
		std::shared_ptr<Views::IView> m_canvas;
		std::unique_ptr<Component::TexturedComponent> m_textured_component;
		std::unique_ptr<Component::ComponentBase> m_untextured_component;
		
		std::shared_ptr<Renderers::ScreenRenderer> m_framebuffer_renderer;
		std::shared_ptr<Renderers::Grid> m_grid_renderer;
		std::shared_ptr<Renderers::Skybox> m_skybox_renderer;
		std::shared_ptr<Services::StateService> m_state_service;
	};
}

#endif