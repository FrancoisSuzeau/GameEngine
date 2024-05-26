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

			std::shared_ptr<Services::CameraService> camera_service = container->GetReference<Services::CameraService>();
			if (!camera_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Camera service is not referenced yet", __FILE__, __FUNCTION__);
			}

			if (component && shader_service && state_service && state_service->getConfigs() && state_service->GetScene() && camera_service)
			{
				bool render_bloom = state_service->getConfigs()->GetBloom();
				shader_service->setInt(shader_name, "render_line", component->GetHovered() || component->GetSelected());
				shader_service->setInt(shader_name, "mixe_texture_color", component->GetMixeTextureColor());
				shader_service->setVec(shader_name, "background_color", component->GetBackgroundColor());
				shader_service->setMat4(shader_name, "model", component->GetModelMat());
				shader_service->setInt(shader_name, "is_light_source", component->GetIsALightSource());
				shader_service->setInt(shader_name, "specular_shininess", component->GetSpecularShininess());
				std::shared_ptr<Component::IComponent> unique_light_source = state_service->GeUniqueLightSource();
				SetLightParameters(unique_light_source, component, shader_service, shader_name);
				shader_service->setInt(shader_name, "render_skybox", state_service->getConfigs()->GetRenderSkybox());
				shader_service->setInt(shader_name, "there_is_light", unique_light_source != nullptr);
				PutViewMapIntoShader(shader_service, shader_name, camera_service);
				shader_service->setMat4(shader_name, "projection", state_service->GetPerspectiveProjectionMatrix());
				shader_service->setTexture(shader_name, "texture0", 0);
				shader_service->setTexture(shader_name, "texture1", 1);
				shader_service->setFloat(shader_name, "near_plane", state_service->getNearPlane());
				shader_service->setFloat(shader_name, "ambiant_strength", component->GetAmbiantOcclusion());

				shader_service->setVec(shader_name, "camera_pos", camera_service->GetPos());
				
				shader_service->setFloat(shader_name, "far_plane", state_service->getFarPlane());
				shader_service->setMat4(shader_name, "projection_ortho", state_service->GetPerspectiveProjectionMatrix());
				if (render_bloom)
				{
					shader_service->setInt(shader_name, "bloom", 1);
					shader_service->setInt(shader_name, "horizontal", component->GetHorizontal());
					shader_service->setFloat(shader_name, "alpha_strength", state_service->getConfigs()->GetMultiSample() ? 0.5f : 0.2f);
				}
				else
				{
					shader_service->setInt(shader_name, "bloom", 0);
					shader_service->setInt(shader_name, "horizontal", false);
					shader_service->setFloat(shader_name, "alpha_strength", 0.8f);

				}

				state_service.reset();
				camera_service.reset();
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
	void Transformer::Resize(std::shared_ptr<Component::IComponent> component, float const offset)
	{
		if (component)
		{
			glm::mat4 model = component->GetModelMat();
			glm::vec3 const actual_size = component->GetSize();
			model = glm::scale(model, glm::vec3(actual_size.x + offset, actual_size.y + offset, actual_size.z + offset));
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
	void Transformer::PutViewMapIntoShader(std::shared_ptr<Services::ShaderService> shader_service, std::string const shader_name, std::shared_ptr<Services::CameraService> camera_service)
	{
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
	void Transformer::SetLightParameters(std::shared_ptr<Component::IComponent> unique_light_source, std::shared_ptr<Component::IComponent> component, std::shared_ptr<Services::ShaderService> shader_service, std::string const shader_name)
	{
		if (unique_light_source != nullptr && component && shader_service)
		{
			shader_service->setVec(shader_name, "light_source_position", unique_light_source->GetPosition());
			shader_service->setVec(shader_name, "light_source_inner_color", glm::vec3(unique_light_source->GetBackgroundColor().r, unique_light_source->GetBackgroundColor().g, unique_light_source->GetBackgroundColor().b));
			Enums::RendererType type = unique_light_source->GetType();
			bool is_textured = type == Enums::RendererType::CUBE_TEXTURED ||
				type == Enums::RendererType::SPHERE_TEXTURED ||
				type == Enums::RendererType::SQUARE_TEXTURED ||
				type == Enums::RendererType::TRIANGLE_TEXTURED;
			shader_service->setInt(shader_name, "is_light_source_textured", is_textured);
		}
	}
}