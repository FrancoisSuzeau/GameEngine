/******************************************************************************************************************************************/
// File : ComponentBase.cpp
// Purpose : Implementing the basic component view
/******************************************************************************************************************************************/

#include "ComponentBase.hpp"

namespace Component
{
	ComponentBase::ComponentBase()
	{
		m_shader_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::ShaderService>();
		if (!m_shader_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : Shader service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}

	void ComponentBase::Clean()
	{
		if (m_shader_service)
		{
			m_shader_service->DeInit();
			m_shader_service.reset();
		}
	}

	void ComponentBase::Render(std::shared_ptr<Renderers::Triangle> renderer, GLenum const mode, float const line_width)
	{
		glLineWidth(line_width);
		glPolygonMode(GL_FRONT_AND_BACK, mode);
		if (m_shader_service && renderer)
		{
			glBindVertexArray(renderer->GetVAO());
			if (glIsVertexArray(renderer->GetVAO()) == GL_TRUE)
			{
				GLuint program_id = m_shader_service->GetProgramId(Constants::UNTEXTURED_SHADER);
				glUseProgram(program_id);
				Transformer::PutIntoShader(renderer, m_shader_service, Constants::UNTEXTURED_SHADER);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				glUseProgram(0);
				glBindVertexArray(0);
			}
		}
	}
	void ComponentBase::Render(std::shared_ptr<Renderers::Square> renderer, GLenum const mode, float const line_width)
	{
		glLineWidth(line_width);
		glPolygonMode(GL_FRONT_AND_BACK, mode);
		if (m_shader_service && renderer)
		{
			glBindVertexArray(renderer->GetVAO());
			if (glIsVertexArray(renderer->GetVAO()) == GL_TRUE)
			{
				GLuint program_id = m_shader_service->GetProgramId(Constants::UNTEXTURED_SHADER);
				glUseProgram(program_id);
				Transformer::PutIntoShader(renderer, m_shader_service, Constants::UNTEXTURED_SHADER);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				glUseProgram(0);
				glBindVertexArray(0);
			}
		}
	}

	void ComponentBase::Render(std::shared_ptr<Renderers::Grid> renderer, GLenum const mode, float const line_width)
	{
		glLineWidth(line_width);
		glPolygonMode(GL_FRONT_AND_BACK, mode);
		if (m_shader_service && renderer)
		{
			glBindVertexArray(renderer->GetVAO());
			if (glIsVertexArray(renderer->GetVAO()) == GL_TRUE)
			{
				GLuint program_id = m_shader_service->GetProgramId(Constants::UNTEXTURED_SHADER);
				glUseProgram(program_id);
				Transformer::PutIntoShader(renderer, m_shader_service, Constants::UNTEXTURED_SHADER);
				glDrawElements(GL_LINES, renderer->GetLength(), GL_UNSIGNED_INT, NULL);
				glUseProgram(0);
				glBindVertexArray(0);
			}
		}
	}
}