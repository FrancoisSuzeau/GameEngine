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
		if (m_mouse_input_service)
		{
			m_mouse_input_service.reset();
		}
		if (m_keyboad_input_service)
		{
			m_keyboad_input_service.reset();
		}

		if (m_runtime_service)
		{
			m_runtime_service.reset();
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
			m_mouse_input_service = container->GetReference<Services::MouseInputService>();
			m_keyboad_input_service = container->GetReference<Services::KeyboardInputService>();
			m_runtime_service = container->GetReference<Services::RunTimeService>();
			
			if (m_shader_service)
			{
				m_shader_service->AddShader(Constants::SCREEN_SHADER, Enums::NORMAL);
				m_shader_service->AddShader(Constants::SKYBOX_SHADER, Enums::NORMAL);
				m_shader_service->AddShader(Constants::UNTEXTURED_SHADER, Enums::NORMAL);
				m_shader_service->AddShader(Constants::HOVER_SHADER, Enums::NORMAL);
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

			if (!m_mouse_input_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Mouse input service is not referenced yet", __FILE__, __FUNCTION__);
			}

			if (!m_keyboad_input_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Keyboard input service is not referenced yet", __FILE__, __FUNCTION__);
			}

			if (!m_runtime_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Runtime service is not referenced yet", __FILE__, __FUNCTION__);
			}
			else
			{
				m_runtime_service->RenderingInFill();
			}
		}
		
	}

	void SceneEngine::RenderScene(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		if (view_model_builder)
		{
			std::shared_ptr<ViewModels::IViewModel> view_model = view_model_builder->GetViewModel(Constants::SCENEVIEWMODEL);
			if (view_model && m_runtime_service)
			{
				view_model->RenderSceneElements(Enums::RendererType::SKYBOX);
				m_runtime_service->RenderingInLine(2.f);
				view_model->RenderSceneElements(Enums::RendererType::GRID);
				m_runtime_service->RenderingInLine(1.f);
				view_model->RenderSceneElements(Enums::RendererType::SUBBGRID);
				view_model->RenderSceneElements(Enums::RendererType::SUBGRID2);
				m_runtime_service->RenderingInFill();
				view_model->RenderComponents();
				m_runtime_service->RenderingInLine(4.f);
				view_model->RenderComponents();
				m_runtime_service->RenderingInFill();

				view_model.reset();
			}
		}
	}

	void SceneEngine::RefreshScene(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		std::shared_ptr<ViewModels::IViewModel> view_model = view_model_builder->GetViewModel(Constants::SCENEVIEWMODEL);
		if (view_model)
		{
			view_model->ManageScene();
			view_model.reset();
		}
	}

	void SceneEngine::RenderFrameBuffer(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		if (view_model_builder)
		{
			std::shared_ptr<ViewModels::IViewModel> view_model = view_model_builder->GetViewModel(Constants::SCENEVIEWMODEL);
			if (view_model)
			{
				//view_model->RenderSceneElements(Enums::RendererType::SQUARE_TEXTURED);
				view_model.reset();
			}

		}
	}
	

	void SceneEngine::UpdateAll(SDL_Event event)
	{
		if (m_mouse_input_service && m_camera_service && m_keyboad_input_service && m_state_service)
		{
			m_mouse_input_service->Update(event);
			m_keyboad_input_service->Update(event);
			if (!m_state_service->getGuiOpen())
			{
				m_camera_service->Update(m_mouse_input_service->GetMotionDir(), m_mouse_input_service->GetMouseButton());
				m_camera_service->OrienteCamera();
				m_camera_service->MoveCamera();
			}
		}
	}

	void SceneEngine::InitFrame()
	{
	}
	void SceneEngine::EndFrame()
	{
	}
}


