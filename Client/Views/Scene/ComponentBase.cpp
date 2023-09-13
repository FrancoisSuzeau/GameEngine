/******************************************************************************************************************************************/
// File : ComponentBase.cpp
// Purpose : Implementing the GUI view app style editor
/******************************************************************************************************************************************/

#include "ComponentBase.hpp"

namespace Component
{
	ComponentBase::ComponentBase()
	{
		m_shader_service = IoC::Container::Container::GetInstanceContainer()->make<Services::ShaderService>();
		if (m_shader_service)
		{
			m_shader_service->LoadShader(Constants::TRIANGLE_SHADER, Enums::NORMAL);
		}

		m_background_color = glm::vec3(0.f, 1.f, 0.f);

		m_position = glm::vec3(0.f);
		m_model_mat = glm::mat4(1.f);
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
				GLuint program_id = m_shader_service->GetProgramId(Constants::TRIANGLE_SHADER);
				glUseProgram(program_id);
				m_shader_service->setVec3(Constants::TRIANGLE_SHADER, "background_color", m_background_color);
				m_shader_service->setMat4(Constants::TRIANGLE_SHADER, "model", m_model_mat);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				glUseProgram(0);
				glBindVertexArray(0);
			}
		}
	}
	void ComponentBase::Transform()
	{
		m_model_mat = glm::mat4(1.f);
		m_model_mat = glm::translate(m_model_mat, m_position);
	}
}