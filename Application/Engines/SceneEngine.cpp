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
		if (m_state_service)
		{
			m_state_service.reset();
		}
		if (m_mouse_picker_service)
		{
			m_mouse_picker_service.reset();
		}
	}
	void SceneEngine::Construct()
	{
		IoC::Container::Container *container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_camera_service = container->GetReference<Services::CameraService>();
			m_shader_service = container->GetReference<Services::ShaderService>();
			m_state_service = container->GetReference<Services::StateService>();
			m_mouse_picker_service = container->GetReference<Services::MousePickerService>();
			
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

			if (!m_state_service)
			{
				SQ_APP_ERROR("Class {} in function {} : State service service is not referenced yet", __FILE__, __FUNCTION__);
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

			if (!m_mouse_picker_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Mouse Picker service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
		
	}

	void SceneEngine::RenderScene(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (m_state_service)
		{
			m_state_service->setRenderLine(false);
		}
		this->RenderSkybox(view_model_builder);
		glLineWidth(2.f);
		this->RenderGrid(view_model_builder);

		
		if (view_model_builder)
		{
			std::shared_ptr<ViewModels::IViewModel> view_model = view_model_builder->GetViewModel(Constants::SCENEVIEWMODEL);
			if (view_model)
			{
				glLineWidth(0.f);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				if (m_state_service)
				{
					m_state_service->setRenderLine(false);
				}
				view_model->RenderViews(Enums::ComponentType::CANVAS);

				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glLineWidth(4.f);
				if (m_state_service)
				{
					m_state_service->setRenderLine(true);
				}
				view_model->RenderViews(Enums::ComponentType::CANVAS);
				
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

	void SceneEngine::RenderGrid(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		if (view_model_builder)
		{
			std::shared_ptr<ViewModels::IViewModel> view_model = view_model_builder->GetViewModel(Constants::SCENEVIEWMODEL);
			if (view_model)
			{
				view_model->RenderGrid();
			}
		}
	}
	

	void SceneEngine::UpdateAll(SDL_Event event)
	{
		if (m_camera_service)
		{
			m_camera_service->UpdateEvent(event);
			m_camera_service->OrienteCamera();
			m_camera_service->MoveCamera();
		}
		if (m_mouse_picker_service)
		{
			m_mouse_picker_service->Update();
			std::cout << m_mouse_picker_service->GetCurrentRay().x << std::endl;
		}
	}

	void SceneEngine::InitFrame()
	{
	}
	void SceneEngine::EndFrame()
	{
	}
}


