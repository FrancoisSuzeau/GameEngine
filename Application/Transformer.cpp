/******************************************************************************************************************************************/
// File : Transformer.cpp
// Purpose : Implementing the transformer 
/******************************************************************************************************************************************/

#include "Transformer.hpp"

namespace Component
{
	void Transformer::PutIntoShader(std::shared_ptr<Component::IComponent> component, std::shared_ptr<Services::ShaderService> shader_service, std::string const shader_name)
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			std::shared_ptr<Services::StateService> state_service = container->GetReference<Services::StateService>();
			if (!state_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}
			if (component && shader_service && state_service)
			{
				shader_service->setInt(shader_name, "render_line", component->GetHovered() || component->GetSelected());
				shader_service->setVec(shader_name, "background_color", component->GetBackgroundColor());
				shader_service->setMat4(shader_name, "model", component->GetModelMat());
				PutViewMapIntoShader(shader_service, shader_name);
				shader_service->setMat4(shader_name, "projection", state_service->GetProjectionMatrix());
				shader_service->setTexture(shader_name, "texture0", 0);
				shader_service->setTexture(shader_name, "texture1", 1);
				if (state_service->getConfigs()->GetBloom())
				{
					shader_service->setInt(shader_name, "bloom", 1);
					shader_service->setInt(shader_name, "horizontal", component->GetHorizontal());
				}
				else
				{
					shader_service->setInt(shader_name, "bloom", 0);
					shader_service->setInt(shader_name, "horizontal", false);
				}

				state_service.reset();
			}
			
		}
		
	}

	void Transformer::Move(std::shared_ptr<Component::IComponent> component)
	{
		if (component)
		{
			glm::mat4 model = component->GetModelMat();
			model = glm::translate(model, component->GetPosition());
			component->SetModelMat(model);
		}
	}
	void Transformer::Resize(std::shared_ptr<Component::IComponent> component)
	{
		if (component)
		{
			glm::mat4 model = component->GetModelMat();
			model = glm::scale(model, component->GetSize());
			component->SetModelMat(model);
		}
	}
	void Transformer::Rotate(std::shared_ptr<Component::IComponent> component, glm::vec3 axis)
	{
		glm::mat4 model = component->GetModelMat();
		model = glm::rotate(model, glm::radians(component->GetAngle()), axis);
		component->SetModelMat(model);
	}
	void Transformer::ReinitModelMat(std::shared_ptr<Component::IComponent> component)
	{
		if (component)
		{
			component->SetModelMat(glm::mat4(1.f));
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