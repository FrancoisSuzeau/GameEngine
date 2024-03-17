/******************************************************************************************************************************************/
// File : SceneViewModel.cpp
// Purpose : Implementing the GUI view model
/******************************************************************************************************************************************/

#include "SceneViewModel.hpp"

namespace ViewModels
{
	SceneViewModel::~SceneViewModel()
	{
		if (m_canvas)
		{
			m_canvas->Clean();
			m_canvas.reset();
		}

		if (m_framebuffer_cpt)
		{
			m_framebuffer_cpt->Clean();
			m_framebuffer_cpt.reset();
		}

		if (m_loader_service)
		{
			m_loader_service.reset();
		}

		if (m_skybox_cpt)
		{
			m_skybox_cpt->Clean();
			m_skybox_cpt.reset();
		}

		if (m_grid_cpt)
		{
			m_grid_cpt->Clean();
			m_grid_cpt.reset();
		}

		if (m_shader_service)
		{
			m_shader_service.reset();
		}

		if (m_state_service)
		{
			m_state_service.reset();
		}

		if (m_framebuffer_service)
		{
			m_framebuffer_service.reset();
		}

		for (std::map<Enums::RendererType, std::shared_ptr<Renderers::IRenderer>>::iterator it = m_renderers.begin(); it != m_renderers.end(); it++)
		{
			if (it->second)
			{
				it->second->Clean();
				it->second.reset();
			}
		}

		m_renderers.clear();
	}
	void SceneViewModel::Construct()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_state_service = container->GetReference<Services::StateService>();
			if (!m_state_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}
			
			m_canvas = container->GetReference<Views::Canvas>();
			if (m_canvas)
			{
				m_canvas->SetParent(this);
				m_canvas->ConstructRenderer();
			}
			else
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Canvas component is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_shader_service = container->GetReference<Services::ShaderService>();
			if (!m_shader_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Shader service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_loader_service = container->GetReference<Services::LoaderService>();
			if (!m_loader_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Loader service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_framebuffer_service = container->GetReference<Services::FramebufferService>();
			if (!m_framebuffer_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Framebuffer service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_skybox_cpt = std::make_shared<Component::TexturedComponent>(glm::vec3(0.f), glm::vec3(0.f), Enums::RendererType::SKYBOX);
			if (m_skybox_cpt && m_loader_service)
			{
				m_skybox_cpt->SetTextureId(m_loader_service->LoadSkybox("resources/skybox/calm_lake"));
			}

			m_renderers.insert_or_assign(Enums::RendererType::SKYBOX, std::make_shared<Renderers::Skybox>());
			m_renderers.insert_or_assign(Enums::RendererType::SQUARE_TEXTURED, std::make_shared<Renderers::ScreenRenderer>());
			m_renderers.insert_or_assign(Enums::RendererType::GRID, std::make_shared<Renderers::Grid>(48));
			for (std::map<Enums::RendererType, std::shared_ptr<Renderers::IRenderer>>::iterator it = m_renderers.begin(); it != m_renderers.end(); it++)
			{
				if (it->second)
				{
					it->second->Construct();
				}
			}

			m_framebuffer_cpt = std::make_shared<Component::TexturedComponent>(glm::vec3(-0.1f), glm::vec3(0.9f), Enums::RendererType::SKYBOX);
			if (m_framebuffer_cpt)
			{
				m_framebuffer_cpt->SetTextureId(0);
			}

			m_grid_cpt = std::make_shared<Component::ComponentBase>(glm::vec3(-10.f, -1.f, -5.f), glm::vec3(20.f), Enums::RendererType::GRID, glm::vec4(1.f));
		}
	}

	void SceneViewModel::RenderComponents(GLenum const mode, float const line_width)
	{
		if (m_state_service)
		{
			std::vector<std::shared_ptr<Component::IComponent>> renderers = m_state_service->getComponents();
			m_canvas->Render(renderers, mode, line_width);
		}
	}
	void SceneViewModel::ManageComponents()
	{
		if (m_state_service)
		{
			std::vector<std::shared_ptr<Component::IComponent>> renderers = m_state_service->getComponents();
			m_canvas->DragRenderers(renderers);
			m_canvas->TransformRenderers(renderers);
		}

		if (m_framebuffer_cpt && m_framebuffer_service)
		{
			m_framebuffer_cpt->SetTextureId(m_framebuffer_service->GetTextureId());
		}
	}

	void SceneViewModel::RenderSceneElements(GLenum const mode, float const line_width, Enums::RendererType element)
	{
		glLineWidth(line_width);
		glPolygonMode(GL_FRONT_AND_BACK, mode);

		switch (element)
		{
		case Enums::SQUARE_TEXTURED:
			if (m_renderers.contains(Enums::RendererType::SQUARE_TEXTURED) && m_renderers.at(Enums::RendererType::SQUARE_TEXTURED))
			{
				glUseProgram(m_shader_service->GetProgramId(Constants::SCREEN_SHADER));
				Component::Transformer::ReinitModelMat(m_framebuffer_cpt);
				Component::Transformer::Move(m_framebuffer_cpt);
				Component::Transformer::Resize(m_framebuffer_cpt);
				Component::Transformer::PutIntoShader(m_framebuffer_cpt, m_shader_service, Constants::SCREEN_SHADER);
				m_renderers.at(Enums::RendererType::SQUARE_TEXTURED)->Draw(m_framebuffer_cpt->GetTextureId());

				glUseProgram(0);
			}
			break;
		case Enums::GRID:
			if (m_renderers.contains(Enums::RendererType::GRID) && m_renderers.at(Enums::RendererType::GRID))
			{
				glUseProgram(m_shader_service->GetProgramId(Constants::UNTEXTURED_SHADER));
				Component::Transformer::ReinitModelMat(m_grid_cpt);
				Component::Transformer::Move(m_grid_cpt);
				Component::Transformer::Resize(m_grid_cpt);
				Component::Transformer::PutIntoShader(m_grid_cpt, m_shader_service, Constants::UNTEXTURED_SHADER);

				m_renderers.at(Enums::RendererType::GRID)->Draw();
				glUseProgram(0);
			}
			break;
		case Enums::SKYBOX:
			if (m_shader_service && m_skybox_cpt)
			{
				glDepthFunc(GL_LEQUAL);

				if (m_renderers.contains(Enums::RendererType::SKYBOX) && m_renderers.at(Enums::RendererType::SKYBOX))
				{
					glUseProgram(m_shader_service->GetProgramId(Constants::SKYBOX_SHADER));
					Component::Transformer::PutIntoShader(m_skybox_cpt, m_shader_service, Constants::SKYBOX_SHADER);

					m_renderers.at(Enums::RendererType::SKYBOX)->Draw(m_skybox_cpt->GetTextureId());
					glUseProgram(0);
				}

				glDepthFunc(GL_LESS);
			}
			break;
		case Enums::TRIANGLE:
		case Enums::SQUARE:
		case Enums::NONE:
		default:
			break;
		}
		
		
	}
	
}

