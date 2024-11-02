/******************************************************************************************************************************************/
// File : SceneEngine.cpp
// Purpose : Implementing the scene engine where object will be rendered
/******************************************************************************************************************************************/
#include "SceneEngine.hpp"

namespace Engines 
{
	SceneEngine::~SceneEngine()
	{
		if (m_runtime_service)
		{
			m_runtime_service.reset();
		}
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

		if (m_screen_renderer)
		{
			m_screen_renderer->Clean();
			m_screen_renderer.reset();
		}
		if (m_screen_component)
		{
			m_screen_component->Clean();
			m_screen_component.reset();
		}

		if (m_framebuffer_service)
		{
			m_framebuffer_service.reset();
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
			m_framebuffer_service = container->GetReference<Services::FramebufferService>();
			m_physic_service = container->GetReference<Services::PhysicsService>();
			
			if (m_shader_service)
			{
				m_shader_service->AddShader(Constants::SCREEN_SHADER, Enums::NORMAL);
				m_shader_service->AddShader(Constants::SKYBOX_SHADER, Enums::NORMAL);
				m_shader_service->AddShader(Constants::UNTEXTURED_SHADER, Enums::NORMAL);
				m_shader_service->AddShader(Constants::HOVER_SHADER, Enums::NORMAL);
				m_shader_service->AddShader(Constants::GAUSSIAN_BLUR_SHADER, Enums::NORMAL);
				m_shader_service->AddShader(Constants::GRID_SHADER, Enums::NORMAL);
				m_shader_service->AddShader(Constants::DEPTH_SHADER, Enums::NORMAL);
				m_shader_service->AddShader(Constants::TEXTURED_SHADER, Enums::NORMAL);
				m_shader_service->AddShader(Constants::TEXTURED_SPHERE_SHADER, Enums::NORMAL);
				m_shader_service->AddShader(Constants::MODEL_SHADER, Enums::NORMAL);
				m_shader_service->AddShader(Constants::CAMERA_SHADER, Enums::NORMAL);
				m_shader_service->AddShader(Constants::LINE_SHADER, Enums::NORMAL);
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
			if (!m_framebuffer_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Framebuffer service is not referenced yet", __FILE__, __FUNCTION__);
			}

			if (!m_physic_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Physic service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
		
		m_screen_renderer = std::make_unique<Renderers::Screen>();
		if (m_screen_renderer)
		{
			m_screen_renderer->Construct();
		}

		m_screen_component = std::make_shared<Component::TexturedComponent>(glm::vec3(0.f), glm::vec3(1.f), Enums::RendererType::SQUARE_TEXTURED, "");
	}

	void SceneEngine::RenderScene(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		if (view_model_builder && m_runtime_service)
		{
			std::shared_ptr<ViewModels::IViewModel> view_model = view_model_builder->GetViewModel(Constants::SCENEVIEWMODEL);
			Enums::StencilType stencil_pass = m_runtime_service->GetStencilPass();
			Enums::FramebufferType buffer_pass = m_runtime_service->GetPass();

			if (buffer_pass == Enums::FramebufferType::CAMERABUFFER && stencil_pass == Enums::StencilType::STENCILBUFFERDISABLE && m_camera_service)
			{
				m_camera_service->SetCameraState(Enums::CameraLocked::LOCKED);
				view_model->RenderSceneElements(Enums::RendererType::MODEL);
				view_model->RenderSceneElements(Enums::RendererType::LINEX);
				view_model->RenderSceneElements(Enums::RendererType::LINEY);
				view_model->RenderSceneElements(Enums::RendererType::LINEZ);
				m_camera_service->SetCameraState(Enums::CameraLocked::UNLOCKED);
			}

			if ((buffer_pass == Enums::FramebufferType::NORMALCOLORBUFFER && stencil_pass == Enums::StencilType::STENCILBUFFERDISABLE) ||
				buffer_pass == Enums::FramebufferType::MULTISAMPLECOLORBUFFER && stencil_pass == Enums::StencilType::STENCILBUFFERDISABLE)
			{
				if (view_model)
				{
					view_model->RenderSceneElements(Enums::RendererType::SKYBOX);
					m_runtime_service->RenderingInLine(1.f);
					view_model->RenderSceneElements(Enums::RendererType::SUBBGRID);
					view_model->RenderSceneElements(Enums::RendererType::SUBGRID2);
					m_runtime_service->RenderingInLine(2.f);
					m_runtime_service->RenderingInFill();

					view_model.reset();
				}
			}

			if (buffer_pass == Enums::FramebufferType::DEPTHBUFFER || 
				(buffer_pass == Enums::FramebufferType::NORMALCOLORBUFFER && stencil_pass == Enums::StencilType::STENCILBUFFERWRITE) ||
				(buffer_pass == Enums::FramebufferType::NORMALCOLORBUFFER && stencil_pass == Enums::StencilType::STENCILBUFFERREAD) || 
				(buffer_pass == Enums::FramebufferType::MULTISAMPLECOLORBUFFER && stencil_pass == Enums::StencilType::STENCILBUFFERWRITE) ||
				(buffer_pass == Enums::FramebufferType::MULTISAMPLECOLORBUFFER && stencil_pass == Enums::StencilType::STENCILBUFFERREAD))
			{
				view_model->RenderComponents();

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

		if (m_screen_component)
		{
			Component::Transformer::ReinitModelMat(m_screen_component);
			Component::Transformer::Resize(m_screen_component);
			Component::Transformer::Move(m_screen_component);
		}

		if (m_shader_service && m_physic_service)
		{
			m_physic_service->SetLightSourcesGeneralParameters();
			m_physic_service->SetLightsAttenuationsParameters();

			m_shader_service->UpdateLightBufferStorage(m_physic_service->GetLigthSources());
		}
	}

	void SceneEngine::LoadAvailableModel(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder, const int index)
	{
		std::shared_ptr<ViewModels::IViewModel> view_model = view_model_builder->GetViewModel(Constants::SCENEVIEWMODEL);
		if (view_model)
		{
			view_model->LoadModel(index);
			view_model.reset();
		}
	}

	void SceneEngine::RenderScreen()
	{
		if (m_screen_renderer && m_shader_service && m_screen_component && m_framebuffer_service && m_runtime_service && m_state_service && m_state_service->getConfigs())
		{
			if (m_state_service->getConfigs()->GetBloom())
			{
				bool horizontal = true;
				bool first_it = true;
				m_screen_component->SetHorizontal(horizontal);
				m_shader_service->BindShaderProgram(Constants::GAUSSIAN_BLUR_SHADER);
				for (size_t i = 0; i < m_state_service->getConfigs()->GetBloomStrength(); i++)
				{
					m_framebuffer_service->BindFramebuffer(horizontal);

					Component::Transformer::PutIntoShader(m_screen_component, m_shader_service, Constants::GAUSSIAN_BLUR_SHADER);
					m_screen_renderer->Draw(first_it, m_framebuffer_service->GetTextureId(1), 
						m_framebuffer_service->GetTextureId(!horizontal));
					if (first_it)
					{
						first_it = false;
					}
					horizontal = !horizontal;
					m_screen_component->SetHorizontal(horizontal);
				}

				m_shader_service->UnbindShaderProgram();
				m_framebuffer_service->UnbindFramebuffer();

				m_shader_service->BindShaderProgram(Constants::SCREEN_SHADER);
				Component::Transformer::PutIntoShader(m_screen_component, m_shader_service, Constants::SCREEN_SHADER);
				m_screen_renderer->Draw(m_framebuffer_service->GetTextureId(0),
					m_framebuffer_service->GetTextureId((bool)!horizontal));
				m_shader_service->UnbindShaderProgram();
			}
			else
			{
				m_shader_service->BindShaderProgram(Constants::SCREEN_SHADER);
				Component::Transformer::PutIntoShader(m_screen_component, m_shader_service, Constants::SCREEN_SHADER);
				m_screen_renderer->Draw(m_framebuffer_service->GetTextureId(0));
				m_shader_service->UnbindShaderProgram();
			}

			
		}
	}
	

	void SceneEngine::UpdateAll(SDL_Event event)
	{
		if (m_mouse_input_service && m_camera_service && m_keyboad_input_service && m_state_service && m_state_service->GetScene())
		{
			m_mouse_input_service->Update(event);
			m_keyboad_input_service->Update(event);
			if (!m_state_service->getGuiOpen())
			{
				m_camera_service->Update(m_mouse_input_service->GetMotionDir(), m_mouse_input_service->GetMouseButton());
				m_camera_service->OrienteCamera();
				m_camera_service->MoveCamera();
				m_state_service->GetScene()->SetCameraParameters(std::make_tuple<glm::vec3, float, float>(m_camera_service->GetPos(), m_camera_service->GetPitch(), m_camera_service->GetYaw()));

			}
		}
	}

	void SceneEngine::UpdateAll()
	{
		if (m_mouse_input_service && m_camera_service && m_keyboad_input_service && m_state_service && m_state_service->GetScene())
		{
			if (!m_state_service->getGuiOpen())
			{
				m_camera_service->Update(m_mouse_input_service->GetMotionDir(), m_mouse_input_service->GetMouseButton());
				m_camera_service->OrienteCamera();
				m_camera_service->MoveCamera();
				m_state_service->GetScene()->SetCameraParameters(std::make_tuple<glm::vec3, float, float>(m_camera_service->GetPos(), m_camera_service->GetPitch(), m_camera_service->GetYaw()));

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


