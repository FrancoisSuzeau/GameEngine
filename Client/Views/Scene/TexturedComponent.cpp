/******************************************************************************************************************************************/
// File : TexturedComponent.cpp
// Purpose : Implementing the basic component view
/******************************************************************************************************************************************/

#include "TexturedComponent.hpp"

namespace Component {
	TexturedComponent::TexturedComponent()
	{
		m_shader_service = IoC::Container::Container::GetInstanceContainer()->make<Services::ShaderService>();
		if (m_shader_service)
		{
			m_shader_service->LoadShader(Constants::SCREEN_SHADER, Enums::NORMAL);
			m_shader_service->LoadShader(Constants::SKYBOX_SHADER, Enums::NORMAL);
		}
	}

	void TexturedComponent::Clean()
	{
		if (m_shader_service)
		{
			m_shader_service->DeInit();
			m_shader_service.reset();
		}
	}

	void TexturedComponent::Render(std::shared_ptr<Renderers::ScreenRenderer> renderer)
	{
		if (m_shader_service && renderer)
		{
			glBindVertexArray(renderer->GetVAO());
			if (glIsVertexArray(renderer->GetVAO()) == GL_TRUE)
			{
				glUseProgram(m_shader_service->GetProgramId(Constants::SCREEN_SHADER));
				Transformer::ReinitModelMat(renderer);
				Transformer::Resize(renderer, glm::vec3(0.9f));
				Transformer::Move(renderer, glm::vec3(-0.1f, 0.f, 0.f));
				Transformer::PutIntoShader(renderer, m_shader_service, Constants::SCREEN_SHADER);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, renderer->GetTextureId());
				if (glIsTexture(renderer->GetTextureId()) == GL_TRUE)
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

	void TexturedComponent::Render(std::shared_ptr < Renderers::Skybox>  renderer)
	{
		if (m_shader_service && renderer)
		{
			
			glBindVertexArray(renderer->GetVAO());
			if (glIsVertexArray(renderer->GetVAO()) == GL_TRUE)
			{
				glDepthMask(GL_FALSE);
				glUseProgram(m_shader_service->GetProgramId(Constants::SKYBOX_SHADER));
				Transformer::PutIntoShader(renderer, m_shader_service, Constants::SKYBOX_SHADER);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_CUBE_MAP, renderer->GetTextureId());
				if (glIsTexture(renderer->GetTextureId()) == GL_TRUE)
				{
					glDrawArrays(GL_TRIANGLES, 0, 36);

					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
				}
				glUseProgram(0);
				glBindVertexArray(0);
				glDepthMask(GL_TRUE);
			}
		}
	}
}