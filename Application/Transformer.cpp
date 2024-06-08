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

			std::shared_ptr<Services::RunTimeService> runtime_service = container->GetReference<Services::RunTimeService>();
			if (!runtime_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Runtime service is not referenced yet", __FILE__, __FUNCTION__);
			}

			if (component && shader_service && state_service && state_service->getConfigs() && state_service->GetScene() && camera_service && runtime_service)
			{
				std::shared_ptr<Component::IComponent> unique_light_source = state_service->GeUniqueLightSource();

				SetLightParameters(unique_light_source, runtime_service, component, state_service, shader_service, shader_name);
				SetWorldParameters(shader_service, shader_name, camera_service, state_service);
				SetComponentParameters(component, shader_service, state_service, shader_name);

				shader_service->setInt(shader_name, "render_skybox", state_service->getConfigs()->GetRenderSkybox());
				shader_service->setVec(shader_name, "camera_pos", camera_service->GetPos());
				shader_service->setInt(shader_name, "there_is_light", unique_light_source != nullptr || state_service->GetScene()->GetIsThereDirectionLight());
				shader_service->setInt(shader_name, "bloom", state_service->getConfigs()->GetBloom());

				

				state_service.reset();
				camera_service.reset();
				runtime_service.reset();

				if (unique_light_source)
				{
					unique_light_source.reset();
				}
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
	void Transformer::SetWorldParameters(std::shared_ptr<Services::ShaderService> shader_service, std::string const shader_name, std::shared_ptr<Services::CameraService> camera_service, std::shared_ptr<Services::StateService> state_service)
	{
		if (camera_service && shader_service && state_service)
		{
			shader_service->setMat4(shader_name, "projection", state_service->GetPerspectiveProjectionMatrix());

			if (shader_name == Constants::SKYBOX_SHADER)
			{
				shader_service->setMat4(shader_name, "view", glm::mat4(glm::mat3(camera_service->GetCameraView())));
			}
			else
			{
				shader_service->setMat4(shader_name, "view", camera_service->GetCameraView());

			}
		}
	}
	void Transformer::SetLightParameters(std::shared_ptr<Component::IComponent> unique_light_source, std::shared_ptr<Services::RunTimeService> runtime_service, std::shared_ptr<Component::IComponent> component, std::shared_ptr<Services::StateService> state_service, std::shared_ptr<Services::ShaderService> shader_service, std::string const shader_name)
	{
		if (component && shader_service && state_service && runtime_service && state_service->GetScene())
		{
			bool is_light_directional = state_service->GetScene()->GetIsThereDirectionLight();
			shader_service->setInt(shader_name, "src_light.is_directional", is_light_directional);
			if (unique_light_source != nullptr && !is_light_directional)
			{
				shader_service->setVec(shader_name, "src_light.position", unique_light_source->GetPosition());
				shader_service->setVec(shader_name, "src_light.inner_color", unique_light_source->GetBackgroundColor());
				Enums::RendererType type = unique_light_source->GetType();
				bool is_textured = type == Enums::RendererType::CUBE_TEXTURED ||
					type == Enums::RendererType::SPHERE_TEXTURED ||
					type == Enums::RendererType::SQUARE_TEXTURED ||
					type == Enums::RendererType::TRIANGLE_TEXTURED;
				shader_service->setInt(shader_name, "src_light.is_point_light", unique_light_source->GetLightType() == Enums::LightType::POINTLIGHT);
				shader_service->setInt(shader_name, "src_light.is_spot_light", unique_light_source->GetLightType() == Enums::LightType::SPOTLIGHT);
				shader_service->setVec(shader_name, "src_light.direction", unique_light_source->GetDirection());
				shader_service->setInt(shader_name, "src_light.is_textured", is_textured);
				shader_service->setInt(shader_name, "src_light.mixe_texture_color", unique_light_source->GetMixeTextureColor());
				shader_service->setInt(shader_name, "src_light.is_attenuation", unique_light_source->GetIsAttenuation());
				Services::Attenuation_constants attenuation_constant = runtime_service->GetAttenuationConstant((int)glm::distance(unique_light_source->GetPosition(), component->GetPosition()));
				shader_service->setFloat(shader_name, "src_light.constant", attenuation_constant.constant);
				shader_service->setFloat(shader_name, "src_light.linear", attenuation_constant.linear);
				shader_service->setFloat(shader_name, "src_light.quadratic", attenuation_constant.quadratic);
				shader_service->setFloat(shader_name, "src_light.cut_off", glm::cos(glm::radians(unique_light_source->GetCutOff())));
				shader_service->setFloat(shader_name, "src_light.outer_cut_off", glm::cos(glm::radians(unique_light_source->GetCutOff() + unique_light_source->GetOuterCutOff())));
				shader_service->setTexture(shader_name, "src_light.texture", 2);
			}

			if (unique_light_source == nullptr && is_light_directional)
			{
				shader_service->setVec(shader_name, "src_light.inner_color", glm::vec4(1.f));
				shader_service->setVec(shader_name, "src_light.direction", state_service->GetScene()->GetDirectionLight());
				shader_service->setInt(shader_name, "src_light.is_textured", false);
				shader_service->setInt(shader_name, "src_light.is_point_light", false);
				shader_service->setInt(shader_name, "src_light.is_spot_light", false);
				shader_service->setInt(shader_name, "src_light.is_spot", false);
				shader_service->setInt(shader_name, "src_light.mixe_texture_color", false);
			}
		}

		
	}
	void Transformer::SetComponentParameters(std::shared_ptr<Component::IComponent> component, std::shared_ptr<Services::ShaderService> shader_service, std::shared_ptr<Services::StateService> state_service, std::string const shader_name)
	{
		if (component && shader_service && state_service && state_service->getConfigs())
		{
			shader_service->setInt(shader_name, "component.render_line", component->GetHovered() || component->GetSelected());
			shader_service->setInt(shader_name, "component.mixe_texture_color", component->GetMixeTextureColor());
			shader_service->setVec(shader_name, "component.background_color", component->GetBackgroundColor());
			shader_service->setMat4(shader_name, "model", component->GetModelMat());
			shader_service->setInt(shader_name, "component.is_light_source", component->GetIsALightSource());
			shader_service->setInt(shader_name, "component.is_spot_light", component->GetLightType() == Enums::LightType::SPOTLIGHT);
			shader_service->setInt(shader_name, "component.specular_shininess", component->GetSpecularShininess());
			shader_service->setFloat(shader_name, "component.specular_strength", component->GetSpecularStrength());
			shader_service->setFloat(shader_name, "component.ambiant_strength", component->GetAmbiantOcclusion());
			shader_service->setTexture(shader_name, "component.texture0", 0);
			shader_service->setTexture(shader_name, "component.texture1", 1);

			bool render_bloom = state_service->getConfigs()->GetBloom();
			if (render_bloom)
			{
				shader_service->setInt(shader_name, "component.horizontal", component->GetHorizontal());
				shader_service->setFloat(shader_name, "component.alpha_strength", state_service->getConfigs()->GetMultiSample() ? 0.5f : 0.2f);
			}
			else
			{
				shader_service->setInt(shader_name, "component.horizontal", false);
				shader_service->setFloat(shader_name, "component.alpha_strength", 0.8f);

			}
		}
	}
}