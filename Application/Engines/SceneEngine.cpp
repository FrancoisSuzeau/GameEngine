/******************************************************************************************************************************************/
// File : SceneEngine.cpp
// Purpose : Implementing the scene engine where object will be rendered
/******************************************************************************************************************************************/
#include "SceneEngine.hpp"

namespace Engines 
{
	void SceneEngine::Construct()
	{
		IoC::Container::Container *container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_camera_service = container->GetReference<Services::CameraService>();
			m_shader_service = container->GetReference<Services::ShaderService>();
			if (m_shader_service)
			{
				m_shader_service->LoadShader(Constants::SCREEN_SHADER, Enums::NORMAL);
				m_shader_service->LoadShader(Constants::SKYBOX_SHADER, Enums::NORMAL);
				m_shader_service->LoadShader(Constants::UNTEXTURED_SHADER, Enums::NORMAL);
			}
		}
		
	}

	void SceneEngine::RenderScene(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		if (view_model_builder)
		{
			std::shared_ptr<ViewModels::IViewModel> view_model = view_model_builder->GetViewModel(Constants::SCENEVIEWMODEL);
			if (view_model)
			{
				view_model->RenderViews(Constants::CANVAS);
			}

		}
	}

	void SceneEngine::RenderFrameBuffer(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder, unsigned int fb_texture_id)
	{
		if (view_model_builder)
		{
			std::shared_ptr<ViewModels::IViewModel> view_model = view_model_builder->GetViewModel(Constants::SCENEVIEWMODEL);
			if (view_model)
			{
				view_model->RenderFrameBuffer(fb_texture_id);
			}

		}
	}

	void SceneEngine::RenderSkybox(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder, unsigned int skybox_texture_id)
	{
		if (view_model_builder)
		{
			std::shared_ptr<ViewModels::IViewModel> view_model = view_model_builder->GetViewModel(Constants::SCENEVIEWMODEL);
			if (view_model)
			{
				view_model->RenderSkybox(skybox_texture_id);
			}

		}
	}

	void SceneEngine::MoveCamera(SDL_Event event)
	{
		if (m_camera_service)
		{
			m_camera_service->UpdateEvent(event);
			m_camera_service->OrienteCamera();
		}
	}

	void SceneEngine::InitFrame()
	{
	}
	void SceneEngine::EndFrame()
	{
	}
}


