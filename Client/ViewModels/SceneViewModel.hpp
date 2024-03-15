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
#include "Services/ShaderService.hpp"


#include <iostream>
#include <map>

namespace ViewModels
{
	class SceneViewModel : public IViewModel
	{

	public:
		~SceneViewModel() override;
		void Construct() override;
		
		void RenderComponents(GLenum const mode, float const line_width) override;
		void ManageComponents() override;
		void RenderFrameBuffer(unsigned int fb_texture_id, GLenum const mode, float const line_width) override;
		void RenderSkybox(GLenum const mode, float const line_width) override;
		void RenderGrid(GLenum const mode, float const line_width) override;
		
	private:
		std::shared_ptr<Views::IView> m_canvas;
		
		std::map<Enums::RendererType, std::shared_ptr<Renderers::IRenderer>> m_renderers;
		std::shared_ptr<Renderers::Grid> m_grid_renderer;
		std::shared_ptr<Component::TexturedComponent> m_skybox_cpt;
		std::shared_ptr<Component::TexturedComponent> m_framebuffer_cpt;
		std::shared_ptr<Services::StateService> m_state_service;
		std::shared_ptr<Services::ShaderService> m_shader_service;
		std::shared_ptr<Services::LoaderService> m_loader_service;
	};
}

#endif