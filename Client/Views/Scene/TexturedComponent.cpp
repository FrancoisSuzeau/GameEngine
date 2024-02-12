/******************************************************************************************************************************************/
// File : TexturedComponent.cpp
// Purpose : Implementing the basic component view
/******************************************************************************************************************************************/

#include "TexturedComponent.hpp"

namespace Component {
	TexturedComponent::TexturedComponent()
	{
		m_shader_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::ShaderService>();
		if (!m_shader_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : Shader service is not referenced yet", __FILE__, __FUNCTION__);
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

	void TexturedComponent::Render(std::shared_ptr<Renderers::ScreenRenderer> renderer, GLenum const mode, float const line_width)
	{
		glLineWidth(line_width);
		glPolygonMode(GL_FRONT_AND_BACK, mode);
		if (m_shader_service && renderer)
		{
			glBindVertexArray(renderer->GetVAO());
			if (glIsVertexArray(renderer->GetVAO()) == GL_TRUE)
			{
				glUseProgram(m_shader_service->GetProgramId(Constants::SCREEN_SHADER));
				
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

	void TexturedComponent::Render(std::shared_ptr < Renderers::Skybox>  renderer, GLenum const mode, float const line_width)
	{
		glLineWidth(line_width);
		glPolygonMode(GL_FRONT_AND_BACK, mode);
		if (m_shader_service && renderer)
		{
			glDepthFunc(GL_LEQUAL);

			glUseProgram(m_shader_service->GetProgramId(Constants::SKYBOX_SHADER));

			glBindVertexArray(renderer->GetVAO());
			if (glIsVertexArray(renderer->GetVAO()) == GL_TRUE)
			{
				
				Transformer::PutIntoShader(renderer, m_shader_service, Constants::SKYBOX_SHADER);

				glBindTexture(GL_TEXTURE_CUBE_MAP, renderer->GetTextureId());
				if (glIsTexture(renderer->GetTextureId()) == GL_TRUE)
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
}