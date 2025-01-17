/******************************************************************************************************************************************/
// File : SceneViewModel.hpp
// Purpose : The scene view model of the application
/******************************************************************************************************************************************/
#ifndef SCENEVIEWMODEL_H
#define SCENEVIEWMODEL_H

#include "IViewModel.hpp"
#include "Container/Container.hpp"
#include "Transformer.hpp"
#include "Services/ShaderService.hpp"
#include "Services/StateService.hpp"
#include "Services/FramebufferService.hpp"
#include "Services/RunTimeService.hpp"
#include "Services/CameraService.hpp"
#include "Services/LoaderService.hpp"
#include "Services/PhysicsService.hpp"

#include "IComponent.hpp"

#include "Components/ComponentBase.hpp"
#include "Components/TexturedComponent.hpp"

#include "../Views/Scene/Canvas.hpp"
#include <functional>

#include "Commands/ActualizeCommand.hpp"

#include "Renderers/Textured/Skybox.hpp"

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
		void ManageScene() override;
		void RenderSceneElements(Enums::RendererType element) override;
		void LoadModel(const int index) override;
		
	private:
		std::shared_ptr<Views::IView> m_canvas;
		
		std::map<Enums::RendererType, std::unique_ptr<Renderers::IRenderer>> m_renderers;

		std::shared_ptr<Services::StateService> m_state_service;
		std::shared_ptr<Services::ShaderService> m_shader_service;
		std::shared_ptr<Services::FramebufferService> m_framebuffer_service;
		std::shared_ptr<Services::RunTimeService> m_runtime_service;
		std::shared_ptr<Services::CameraService> m_camera_service;
		std::shared_ptr<Services::LoaderService> m_loader_service;
		std::shared_ptr<Services::PhysicsService> m_physic_service;
		int m_grid_size;
		std::map<Enums::RendererType, std::shared_ptr<Component::IComponent>> m_components;

		void TransformSceneElements();
		void ManageGridScaling(glm::vec3 const cam_pos);
		void ManageGridPosition(glm::vec3 const cam_pos);
		void ManageAxix();
		void ManageSphereAxis();
		void ManageCameraCapture();
		float m_current_relative_distance_from_cam;
		glm::vec3 m_current_cam_pos;

	};
}

#endif