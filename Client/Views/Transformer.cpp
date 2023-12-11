/******************************************************************************************************************************************/
// File : Transformer.cpp
// Purpose : Implementing the transformer 
/******************************************************************************************************************************************/

#include "Transformer.hpp"

namespace Component
{
	void Transformer::PutIntoShader(std::shared_ptr<Renderers::IRenderer> renderer, std::shared_ptr<Services::ShaderService> shader_service, std::string const shader_name)
	{
		std::shared_ptr<Services::StateService> state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
		else
		{
			if (renderer && shader_service)
			{
				if (state_service->getRenderLine() && (renderer->GetHovered() || renderer->GetSelected()))
				{
					shader_service->setVec3(shader_name, "background_color", glm::vec3(1.f));
				}
				else
				{
					shader_service->setVec3(shader_name, "background_color", renderer->GetBackgroundColor());
				}
				shader_service->setMat4(shader_name, "model", renderer->GetModelMat());
				PutViewMapIntoShader(shader_service, shader_name);
				shader_service->setMat4(shader_name, "projection", state_service->GetProjectionMatrix());
				if (shader_name == Constants::SCREEN_SHADER || shader_name == Constants::SKYBOX_SHADER)
				{
					shader_service->setTexture(shader_name, "texture0", 0);
				}
			}
			state_service.reset();
		}
		
	}

	void Transformer::Move(std::shared_ptr<Renderers::IRenderer> renderer, glm::vec3 new_position)
	{
		if (renderer)
		{
			glm::mat4 model = renderer->GetModelMat();
			model = glm::translate(model, renderer->GetPosition());
			renderer->SetModelMat(model);
		}
	}
	void Transformer::Resize(std::shared_ptr<Renderers::IRenderer> renderer, glm::vec3 size_vector)
	{
		if (renderer)
		{
			glm::mat4 model = renderer->GetModelMat();
			model = glm::scale(model, renderer->GetSize());
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
	void Transformer::PutViewMapIntoShader(std::shared_ptr<Services::ShaderService> shader_service, std::string const shader_name)
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			std::shared_ptr<Services::CameraService> camera_service = container->GetReference<Services::CameraService>();
			if (camera_service)
			{
				if (shader_name == Constants::SKYBOX_SHADER)
				{
					shader_service->setMat4(shader_name, "view", glm::mat4(glm::mat3(camera_service->GetCameraView())));
				}
				else
				{
					shader_service->setMat4(shader_name, "view", camera_service->GetCameraView());
				}

				camera_service.reset();
			}
		}
	}
}