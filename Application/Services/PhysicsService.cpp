/******************************************************************************************************************************************/
// File : PhysicsService.cpp
// Purpose : Implementing the mouse input service
/******************************************************************************************************************************************/
#include "PhysicsService.hpp"

namespace Services
{
	void PhysicsService::Init()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_state_service = container->GetReference<StateService>();
			if (!m_state_service)
			{
				SQ_APP_ERROR("Class {} in function {} : State service initializer is not referenced yet", __FILE__, __FUNCTION__);
			}
		}

		this->SetAttenuationConstants();
		
	}

	void PhysicsService::DeInit()
	{
		m_light_sources.clear();

		m_attenuation_constants.clear();

	}

	glm::vec3 PhysicsService::UpdateDirectionalLight(Enums::AngleToUpdate type, float const theta, float const phi)
	{
		m_phi = phi;
		m_theta = theta;
		glm::vec3 axis = glm::vec3(0.f, 1.f, 0.f);
		glm::mat4 dir_mat = glm::mat4(1.f);

		//first rotate from Y axis
		dir_mat = glm::rotate(dir_mat, m_phi, axis);

		//Second rotate from X axis
		axis = glm::vec3(1.f, 0.f, 0.f);
		dir_mat = glm::rotate(dir_mat, m_theta, axis);

		return glm::vec3(dir_mat * glm::vec4(0, 0, -1, 0));
	}

	float PhysicsService::GetTheta() const
	{
		return m_theta;
	}

	float PhysicsService::GetPhi() const
	{
		return m_phi;
	}

	void PhysicsService::SetTheta(glm::vec3 const direction)
	{
		float r = std::sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
		m_theta = std::acos(direction.z / r);
	}

	void PhysicsService::SetPhi(glm::vec3 const direction)
	{
		m_phi = std::atan2(direction.y, direction.x);
	}

	std::vector<Light> PhysicsService::GetLigthSources() const
	{
		return m_light_sources;
	}

	std::vector<unsigned int> PhysicsService::GetLightSourcesTextureIds() const
	{
		return m_light_texture_ids;
	}

	void PhysicsService::SetLightSourcesGeneralParameters()
	{
		if (m_state_service && m_state_service->GetScene())
		{
			std::vector<std::shared_ptr<Component::IComponent>> components = m_state_service->GetScene()->GetSceneComponents();

			m_light_sources.clear();
			m_light_texture_ids.clear();

			bool is_there_directionnal = m_state_service->GetScene()->GetIsThereDirectionLight();
			if (!is_there_directionnal)
			{
				int tex_index = 0;
				for (std::vector<std::shared_ptr<Component::IComponent>>::iterator it = components.begin(); it != components.end(); it++)
				{
					if (it[0] && it[0]->GetIsALightSource())
					{
						Light light;
						light.position[0] = it[0]->GetPosition().x;
						light.position[1] = it[0]->GetPosition().y;
						light.position[2] = it[0]->GetPosition().z;
						light.inner_color[0] = it[0]->GetBackgroundColor().x;
						light.inner_color[1] = it[0]->GetBackgroundColor().y;
						light.inner_color[2] = it[0]->GetBackgroundColor().z;
						light.inner_color[3] = it[0]->GetBackgroundColor().a;
						light.is_textured = it[0]->GetType() == Enums::RendererType::CUBE_TEXTURED ||
							it[0]->GetType() == Enums::RendererType::SPHERE_TEXTURED ||
							it[0]->GetType() == Enums::RendererType::SQUARE_TEXTURED ||
							it[0]->GetType() == Enums::RendererType::TRIANGLE_TEXTURED;
						light.mixe_texture_color = it[0]->GetMixeTextureColor();
						if (light.is_textured == 1)
						{
							light.texture_index = tex_index;
							m_light_texture_ids.push_back(it[0]->GetTextureId());
							tex_index++;
						}
						else
						{
							light.texture_index = -1;
						}
						light.constant = 0.f;
						light.linear = 0.f;
						light.quadratic = 0.f;
						light.is_point_light = it[0]->GetLightType() == Enums::LightType::POINTLIGHT;
						light.is_spot_light = it[0]->GetLightType() == Enums::LightType::SPOTLIGHT;
						light.is_directional = m_state_service->GetScene()->GetIsThereDirectionLight();
						light.direction[0] = it[0]->GetDirection().x;
						light.direction[1] = it[0]->GetDirection().y;
						light.direction[2] = it[0]->GetDirection().z;
						light.cut_off = glm::cos(glm::radians(it[0]->GetCutOff()));
						light.outer_cut_off = glm::cos(glm::radians(it[0]->GetCutOff() + it[0]->GetOuterCutOff()));
						light.is_attenuation = it[0]->GetIsAttenuation();
						light.intensity = it[0]->GetIntensity();
						m_light_sources.push_back(light);
					}
				}
			}
			else
			{
				Light light;
				light.inner_color[0] = 1.f;
				light.inner_color[1] = 1.f;
				light.inner_color[2] = 1.f;
				light.inner_color[3] = 1.f;
				light.mixe_texture_color = 0;
				light.is_textured = 0;
				light.is_point_light = 0;
				light.is_spot_light = 0;
				light.is_directional = 1;
				light.direction[0] = m_state_service->GetScene()->GetDirectionLight().x;
				light.direction[1] = m_state_service->GetScene()->GetDirectionLight().y;
				light.direction[2] = m_state_service->GetScene()->GetDirectionLight().z;
				m_light_sources.push_back(light);
			}

			
		}
	}

	Attenuation_constants PhysicsService::GetAttenuationConstant(int const distance)
	{
		if (distance >= 0 && distance <= 7)
		{
			return m_attenuation_constants.front();
		}

		if (distance > 600 && distance <= 3250)
		{
			return m_attenuation_constants.back();
		}
		if (!m_attenuation_constants.empty() && !m_attenuation_distance.empty() && m_attenuation_constants.size() == m_attenuation_distance.size())
		{
			for (int i = 1; i < m_attenuation_distance.size() - 1; i++)
			{
				if (distance > m_attenuation_distance[i - 1] && distance <= m_attenuation_distance[i])
				{
					return m_attenuation_constants[i];
				}
			}
		}

		return { 1.f, 0.7f, 1.8f };
	}
	void PhysicsService::SetLightsAttenuationsParameters()
	{
		std::vector<std::shared_ptr<Component::IComponent>> components = m_state_service->GetScene()->GetSceneComponents();

		for (std::vector<std::shared_ptr<Component::IComponent>>::iterator it = components.begin(); it != components.end(); it++)
		{
			if (it[0] && !it[0]->GetIsALightSource())
			{
				for (std::vector<Light>::iterator it2 = m_light_sources.begin(); it2 != m_light_sources.end(); it2++)
				{
					glm::vec3 light_distance = glm::vec3(it2->position[0], it2->position[1], it2->position[2]);
					Attenuation_constants attenuation_constant = this->GetAttenuationConstant((int)glm::distance(it[0]->GetPosition(), it[0]->GetPosition()));
					it2->constant = attenuation_constant.constant;
					it2->linear = attenuation_constant.linear;
					it2->quadratic = attenuation_constant.quadratic;
				}

			}
		}
	}
	void PhysicsService::SetAttenuationConstants()
	{
		m_attenuation_constants = {

			{1.f, 0.7f, 1.8f},
			{1.f, 0.35f, 0.44f},
			{1.f, 0.22f, 0.2f},
			{1.f, 0.14f, 0.07f},
			{1.f, 0.09f, 0.032f},
			{1.f, 0.07f, 0.017f},
			{1.f, 0.045f, 0.0075f},
			{1.f, 0.027f, 0.0028f},
			{1.f, 0.022f, 0.0019f},
			{1.f, 0.014f, 0.0007f},
			{1.f, 0.007f, 0.0002f},
			{1.f, 0.0014f, 0.000007f}
		};

		m_attenuation_distance = { 7, 13, 20, 32, 50, 65, 100, 160, 200, 325, 600, 3250 };
	}

	void PhysicsService::RemoveLightSources()
	{
		if (m_state_service)
		{
			std::vector<std::shared_ptr<Component::IComponent>> components = m_state_service->GetScene()->GetSceneComponents();
			for (std::vector<std::shared_ptr<Component::IComponent>>::iterator it = components.begin(); it != components.end(); ++it)
			{
				if (it[0])
				{
					it[0]->SetIsALigthSource(false);
				}
			}
		}
	}

}

