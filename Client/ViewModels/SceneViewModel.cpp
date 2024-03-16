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

		/*if (m_grid_renderer)
		{
			m_grid_renderer->Clean();
			m_grid_renderer.reset();
		}*/

		if (m_shader_service)
		{
			m_shader_service.reset();
		}

		if (m_state_service)
		{
			m_state_service.reset();
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

			m_skybox_cpt = std::make_shared<Component::TexturedComponent>(glm::vec3(0.f), glm::vec3(0.f), Enums::RendererType::SKYBOX);
			if (m_skybox_cpt && m_loader_service)
			{
				m_skybox_cpt->SetTextureId(m_loader_service->LoadSkybox("resources/skybox/calm_lake"));
			}

			m_renderers.insert_or_assign(Enums::RendererType::SKYBOX, std::make_shared<Renderers::Skybox>());
			m_renderers.insert_or_assign(Enums::RendererType::SQUARE_TEXTURED, std::make_shared<Renderers::ScreenRenderer>());
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

			/*m_grid_renderer = std::make_shared<Renderers::Grid>(48);
			if (m_grid_renderer)
			{
				m_grid_renderer->Construct();
			}*/

			

		}
	}

	void SceneViewModel::RenderComponents(GLenum const mode, float const line_width)
	{
		if (m_state_service)
		{
			std::vector<std::shared_ptr<Component::IComponent>> renderers = m_state_service->getRenderers();
			m_canvas->Render(renderers, mode, line_width);
		}
	}
	void SceneViewModel::ManageComponents()
	{
		if (m_state_service)
		{
			std::vector<std::shared_ptr<Component::IComponent>> renderers = m_state_service->getRenderers();
			m_canvas->DragRenderers(renderers);
			m_canvas->TransformRenderers(renderers);
		}
	}
	void SceneViewModel::RenderFrameBuffer(unsigned int fb_texture_id, GLenum const mode, float const line_width)
	{
		if (m_shader_service && m_framebuffer_cpt)
		{
			Component::Transformer::ReinitModelMat(m_framebuffer_cpt);
			Component::Transformer::Resize(m_framebuffer_cpt);
			Component::Transformer::Move(m_framebuffer_cpt);
			glLineWidth(line_width);
			glPolygonMode(GL_FRONT_AND_BACK, mode);
			m_framebuffer_cpt->SetTextureId(fb_texture_id);

			if (m_renderers.contains(Enums::RendererType::SQUARE_TEXTURED) && m_renderers.at(Enums::RendererType::SQUARE_TEXTURED))
			{
				glBindVertexArray(m_renderers.at(Enums::RendererType::SQUARE_TEXTURED)->GetVAO());
				if (glIsVertexArray(m_renderers.at(Enums::RendererType::SQUARE_TEXTURED)->GetVAO()) == GL_TRUE)
				{
					glUseProgram(m_shader_service->GetProgramId(Constants::SCREEN_SHADER));

					Component::Transformer::PutIntoShader(m_framebuffer_cpt, m_shader_service, Constants::SCREEN_SHADER);

					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, m_framebuffer_cpt->GetTextureId());
					if (glIsTexture(m_framebuffer_cpt->GetTextureId()) == GL_TRUE)
					{
						glDrawArrays(GL_TRIANGLES, 0, 6);

						glActiveTexture(GL_TEXTURE0);
						glBindTexture(GL_TEXTURE_2D, 0);
					}
					glUseProgram(0);
					glBindVertexArray(0);
				}
			}

			
		}
	}
	void SceneViewModel::RenderSkybox(GLenum const mode, float const line_width)
	{
		if (m_shader_service && m_skybox_cpt)
		{
			glLineWidth(line_width);
			glPolygonMode(GL_FRONT_AND_BACK, mode);
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
	}

	void SceneViewModel::RenderGrid(GLenum const mode, float const line_width)
	{
		//if (m_shader_service && m_grid_renderer)
		//{
		//	/*Component::Transformer::ReinitModelMat(m_grid_renderer);
		//	Component::Transformer::Move(m_grid_renderer);
		//	Component::Transformer::Resize(m_grid_renderer);*/
		//	glLineWidth(line_width);
		//	glPolygonMode(GL_FRONT_AND_BACK, mode);
		//	glBindVertexArray(m_grid_renderer->GetVAO());
		//	if (glIsVertexArray(m_grid_renderer->GetVAO()) == GL_TRUE)
		//	{
		//		GLuint program_id = m_shader_service->GetProgramId(Constants::UNTEXTURED_SHADER);
		//		glUseProgram(program_id);
		//		//Component::Transformer::PutIntoShader(m_grid_renderer, m_shader_service, Constants::UNTEXTURED_SHADER);
		//		glDrawElements(GL_LINES, m_grid_renderer->GetLength(), GL_UNSIGNED_INT, NULL);
		//		glUseProgram(0);
		//		glBindVertexArray(0);
		//	}
		//}
	}
	
}

