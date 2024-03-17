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
			
			
			if (m_shader_service)
			{
				m_shader_service->LoadShader(Constants::SCREEN_SHADER, Enums::NORMAL);
				m_shader_service->LoadShader(Constants::SKYBOX_SHADER, Enums::NORMAL);
				m_shader_service->LoadShader(Constants::UNTEXTURED_SHADER, Enums::NORMAL);
				m_shader_service->LoadShader(Constants::HOVER_SHADER, Enums::NORMAL);
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
		}
		
	}

	void SceneEngine::RenderScene(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		this->RenderSkybox(view_model_builder);
		this->RenderGrid(view_model_builder);
		
		if (view_model_builder)
		{
			std::shared_ptr<ViewModels::IViewModel> view_model = view_model_builder->GetViewModel(Constants::SCENEVIEWMODEL);
			if (view_model)
			{
				if(m_state_service)
				{
					view_model->RenderComponents(GL_FILL, 0.f);
					view_model->RenderComponents(GL_LINE, 4.f);
					
				}

				view_model.reset();
			}
		}
	}

	void SceneEngine::RefreshScene(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		std::shared_ptr<ViewModels::IViewModel> view_model = view_model_builder->GetViewModel(Constants::SCENEVIEWMODEL);
		if (view_model)
		{
			view_model->ManageComponents();
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
				view_model->RenderFrameBuffer(GL_FILL, 0.f);
				view_model.reset();
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
				view_model->RenderSkybox(GL_FILL, 0.f);
				view_model.reset();
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
				view_model->RenderGrid(GL_LINE, 2.f);
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


