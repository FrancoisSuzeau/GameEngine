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

		if (m_framebuffer_renderer)
		{
			m_framebuffer_renderer->Clean();
			m_framebuffer_renderer.reset();
		}

		if (m_skybox_renderer)
		{
			m_skybox_renderer->Clean();
			m_skybox_renderer.reset();
		}

		if (m_grid_renderer)
		{
			m_grid_renderer->Clean();
			m_grid_renderer.reset();
		}

		if (m_shader_service)
		{
			m_shader_service.reset();
		}

		if (m_state_service)
		{
			m_state_service.reset();
		}
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
			}
			else
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Canvas component is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_framebuffer_renderer = std::make_shared<Renderers::ScreenRenderer>();
			if (m_framebuffer_renderer)
			{
				m_framebuffer_renderer->Construct();
			}

			m_skybox_renderer = std::make_shared<Renderers::Skybox>();
			if (m_skybox_renderer)
			{
				m_skybox_renderer->Construct();
			}

			m_grid_renderer = std::make_shared<Renderers::Grid>(48);
			if (m_grid_renderer)
			{
				m_grid_renderer->Construct();
			}

			m_shader_service = container->GetReference<Services::ShaderService>();
			if (!m_shader_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Shader service is not referenced yet", __FILE__, __FUNCTION__);
			}

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
		if (m_shader_service && m_framebuffer_renderer)
		{
			m_framebuffer_renderer->SetTextureID(fb_texture_id);
			/*Component::Transformer::ReinitModelMat(m_framebuffer_renderer);
			Component::Transformer::Resize(m_framebuffer_renderer);
			Component::Transformer::Move(m_framebuffer_renderer);*/
			glLineWidth(line_width);
			glPolygonMode(GL_FRONT_AND_BACK, mode);
			glBindVertexArray(m_framebuffer_renderer->GetVAO());
			if (glIsVertexArray(m_framebuffer_renderer->GetVAO()) == GL_TRUE)
			{
				glUseProgram(m_shader_service->GetProgramId(Constants::SCREEN_SHADER));

				//Component::Transformer::PutIntoShader(m_framebuffer_renderer, m_shader_service, Constants::SCREEN_SHADER);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, m_framebuffer_renderer->GetTextureId());
				if (glIsTexture(m_framebuffer_renderer->GetTextureId()) == GL_TRUE)
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
	void SceneViewModel::RenderSkybox(unsigned int skybox_texture_id, GLenum const mode, float const line_width)
	{
		if (m_shader_service && m_skybox_renderer)
		{
			m_skybox_renderer->SetTextureID(skybox_texture_id);
			glLineWidth(line_width);
			glPolygonMode(GL_FRONT_AND_BACK, mode);
			glDepthFunc(GL_LEQUAL);

			glUseProgram(m_shader_service->GetProgramId(Constants::SKYBOX_SHADER));

			glBindVertexArray(m_skybox_renderer->GetVAO());
			if (glIsVertexArray(m_skybox_renderer->GetVAO()) == GL_TRUE)
			{

				//Component::Transformer::PutIntoShader(m_skybox_renderer, m_shader_service, Constants::SKYBOX_SHADER);

				glBindTexture(GL_TEXTURE_CUBE_MAP, m_skybox_renderer->GetTextureId());
				if (glIsTexture(m_skybox_renderer->GetTextureId()) == GL_TRUE)
				{
					glDrawArrays(GL_TRIANGLES, 0, 36);

					glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
				}

				glBindVertexArray(0);
				glUseProgram(0);
			}

			glDepthFunc(GL_LESS);
		}
	}

	void SceneViewModel::RenderGrid(GLenum const mode, float const line_width)
	{
		if (m_shader_service && m_grid_renderer)
		{
			/*Component::Transformer::ReinitModelMat(m_grid_renderer);
			Component::Transformer::Move(m_grid_renderer);
			Component::Transformer::Resize(m_grid_renderer);*/
			glLineWidth(line_width);
			glPolygonMode(GL_FRONT_AND_BACK, mode);
			glBindVertexArray(m_grid_renderer->GetVAO());
			if (glIsVertexArray(m_grid_renderer->GetVAO()) == GL_TRUE)
			{
				GLuint program_id = m_shader_service->GetProgramId(Constants::UNTEXTURED_SHADER);
				glUseProgram(program_id);
				//Component::Transformer::PutIntoShader(m_grid_renderer, m_shader_service, Constants::UNTEXTURED_SHADER);
				glDrawElements(GL_LINES, m_grid_renderer->GetLength(), GL_UNSIGNED_INT, NULL);
				glUseProgram(0);
				glBindVertexArray(0);
			}
		}
	}
	
}

