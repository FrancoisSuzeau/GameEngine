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

#include <functional>

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
		void RenderSceneElements(Enums::RendererType element) override;
		
	private:
		std::shared_ptr<Views::IView> m_canvas;
		
		std::map<Enums::RendererType, std::shared_ptr<Renderers::IRenderer>> m_renderers;
		std::shared_ptr<Component::ComponentBase> m_grid_cpt;
		std::shared_ptr<Component::TexturedComponent> m_skybox_cpt;
		std::shared_ptr<Component::TexturedComponent> m_framebuffer_cpt;
		std::shared_ptr<Services::StateService> m_state_service;
		std::shared_ptr<Services::ShaderService> m_shader_service;
		std::shared_ptr<Services::LoaderService> m_loader_service;
		std::shared_ptr<Services::FramebufferService> m_framebuffer_service;
		std::shared_ptr<Services::RunTimeService> m_runtime_service;

		void LambdaRender(std::function<void()> callback, std::string const shader_name, std::shared_ptr<Component::IComponent> cpt);


	};
}

#endif