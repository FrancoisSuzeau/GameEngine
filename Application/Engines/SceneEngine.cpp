/******************************************************************************************************************************************/
// File : SceneEngine.cpp
// Purpose : Implementing the scene engine where object will be rendered
/******************************************************************************************************************************************/
#include "SceneEngine.hpp"

namespace Engines 
{
	SceneEngine::~SceneEngine()
	{
		if (m_camera_service)
		{
			m_camera_service.reset();
		}
		if (m_shader_service)
		{
			m_shader_service.reset();
		}
	}
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
			else
			{
				SQ_APP_ERROR("Class {} in function {} : Shader service is not referenced yet", __FILE__, __FUNCTION__);
			}

			if (!m_camera_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Camera service is not referenced yet", __FILE__, __FUNCTION__);
			}

			std::shared_ptr<Services::TextureLoaderService> tex = container->GetReference<Services::TextureLoaderService>();
			if (tex)
			{
				
				m_skybox_texture = tex->BuildSkyboxTexture("resources/skybox/calm_lake");
				tex.reset();
			}
			else
			{
				SQ_APP_ERROR("Class {} in function {} : Texture service loader is not referenced yet", __FILE__, __FUNCTION__);
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

	void SceneEngine::RenderSkybox(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		if (view_model_builder)
		{
			std::shared_ptr<ViewModels::IViewModel> view_model = view_model_builder->GetViewModel(Constants::SCENEVIEWMODEL);
			if (view_model)
			{
				view_model->RenderSkybox(m_skybox_texture);
			}

		}
	}

	void SceneEngine::UpdateCamera(SDL_Event event)
	{
		if (m_camera_service)
		{
			m_camera_service->UpdateEvent(event);
			m_camera_service->OrienteCamera();
			m_camera_service->MoveCamera();
		}
	}

	void SceneEngine::InitFrame()
	{
	}
	void SceneEngine::EndFrame()
	{
	}
}


