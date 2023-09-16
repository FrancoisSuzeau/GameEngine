/******************************************************************************************************************************************/
// File : ComponentBase.cpp
// Purpose : Implementing the basic component view
/******************************************************************************************************************************************/

#include "ComponentBase.hpp"

namespace Component
{
	ComponentBase::ComponentBase()
	{
		m_shader_service = IoC::Container::Container::GetInstanceContainer()->make<Services::ShaderService>();
		if (m_shader_service)
		{
			m_shader_service->LoadShader(Constants::UNTEXTURED_SHADER, Enums::NORMAL);
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

	void ComponentBase::Render(std::shared_ptr<Renderers::Triangle> renderer)
	{
		if (m_shader_service && renderer)
		{
			glBindVertexArray(renderer->GetVAO());
			if (glIsVertexArray(renderer->GetVAO()) == GL_TRUE)
			{
				GLuint program_id = m_shader_service->GetProgramId(Constants::UNTEXTURED_SHADER);
				glUseProgram(program_id);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				glUseProgram(0);
				glBindVertexArray(0);
			}
		}
	}
	void ComponentBase::Render(std::shared_ptr<Renderers::Square> renderer)
	{
		if (m_shader_service && renderer)
		{
			glBindVertexArray(renderer->GetVAO());
			if (glIsVertexArray(renderer->GetVAO()) == GL_TRUE)
			{
				GLuint program_id = m_shader_service->GetProgramId(Constants::UNTEXTURED_SHADER);
				glUseProgram(program_id);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				glUseProgram(0);
				glBindVertexArray(0);
			}
		}
	}
}