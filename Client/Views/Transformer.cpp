/******************************************************************************************************************************************/
// File : Transformer.cpp
// Purpose : Implementing the transformer 
/******************************************************************************************************************************************/

#include "Transformer.hpp"

namespace Component
{
	void Transformer::PutIntoShader(std::shared_ptr<Renderers::IRenderer> renderer, std::shared_ptr<Services::ShaderService> shader_service, std::string const shader_name)
	{
		std::shared_ptr<Services::StateService> state_service = IoC::Container::Container::GetInstanceContainer()->make<Services::StateService>();
		if (renderer && shader_service && state_service)
		{
			shader_service->setVec3(shader_name, "background_color", renderer->GetBackgroundColor());
			shader_service->setMat4(shader_name, "model", renderer->GetModelMat());
			shader_service->setMat4(shader_name, "view", state_service->GetViewMatrix());
			shader_service->setMat4(shader_name, "projection", state_service->GetProjectionMatrix());
			if (shader_name == Constants::SCREEN_SHADER || shader_name == Constants::SKYBOX_SHADER)
			{
				shader_service->setTexture(shader_name, "texture0", 0);
			}
		}
	}

	void Transformer::Move(std::shared_ptr<Renderers::IRenderer> renderer, glm::vec3 new_position)
	{
		if (renderer)
		{
			glm::mat4 model = renderer->GetModelMat();
			model = glm::translate(model, new_position);
			renderer->SetModelMat(model);
		}
	}

	void Transformer::Colorize(std::shared_ptr<Renderers::IRenderer> renderer, glm::vec3 new_color)
	{
		if (renderer)
		{
			renderer->SetBackgroundColor(new_color);
		}
	}
	void Transformer::Resize(std::shared_ptr<Renderers::IRenderer> renderer, glm::vec3 size_vector)
	{
		if (renderer)
		{
			glm::mat4 model = renderer->GetModelMat();
			model = glm::scale(model, size_vector);
			renderer->SetModelMat(model);
		}
	}
	void Transformer::Rotate(std::shared_ptr<Renderers::IRenderer> renderer, float angle, glm::vec3 axis)
	{
		glm::mat4 model = renderer->GetModelMat();
		model = glm::rotate(model, glm::radians(angle), axis);
		renderer->SetModelMat(model);
	}
	void Transformer::ReinitModelMat(std::shared_ptr<Renderers::IRenderer> renderer)
	{
		if (renderer)
		{
			renderer->SetModelMat(glm::mat4(1.f));
		}
	}
}