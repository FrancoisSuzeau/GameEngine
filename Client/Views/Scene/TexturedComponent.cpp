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

	void TexturedComponent::Render(std::shared_ptr<Renderers::SquareTextured> renderer)
	{
		if (m_shader_service && renderer)
		{
			glBindVertexArray(renderer->GetVAO());
			if (glIsVertexArray(renderer->GetVAO()) == GL_TRUE)
			{
				GLuint program_id = m_shader_service->GetProgramId(Constants::SCREEN_SHADER);
				glUseProgram(program_id);
				Transformer::PutIntoShader(renderer, m_shader_service, Constants::SCREEN_SHADER);
				glBindTexture(GL_TEXTURE_2D, renderer->GetTextureId());
				
				glDrawArrays(GL_TRIANGLES, 0, 6);
				
				
				glUseProgram(0);
				glBindVertexArray(0);
			}
		}
	}
}