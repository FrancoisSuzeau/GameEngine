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
		angle = 0.f;
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
				Transformer::Colorize(renderer, glm::vec3(1.f, 0.f, 0.f));
				Transformer::ReinitModelMat(renderer);
				this->IncrementAngle(0.1f);
				Transformer::Move(renderer, glm::vec3(-0.5f, 0.f, 0.f));
				Transformer::Rotate(renderer, angle, glm::vec3(0.f, 0.f, 1.f));
				Transformer::PutIntoShader(renderer, m_shader_service, Constants::UNTEXTURED_SHADER);
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
				Transformer::Colorize(renderer, glm::vec3(0.f, 1.f, 0.f));
				Transformer::ReinitModelMat(renderer);
				Transformer::Resize(renderer, 0.2f);
				Transformer::Move(renderer, glm::vec3(0.5f, 0.f, 0.f));
				Transformer::PutIntoShader(renderer, m_shader_service, Constants::UNTEXTURED_SHADER);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				glUseProgram(0);
				glBindVertexArray(0);
			}
		}
	}
	void ComponentBase::IncrementAngle(float incr)
	{
		if (angle > 360.f)
		{
			angle = 0.f;
		}
		else
		{
			angle += incr;
		}
	}
}