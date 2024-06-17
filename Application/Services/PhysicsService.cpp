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
		
	}

	void PhysicsService::DeInit()
	{
		this->RemoveLightSources();

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

	std::vector<std::shared_ptr<Component::IComponent>> PhysicsService::GetLigthSources() const
	{
		return m_light_sources;
	}

	void PhysicsService::SetLightSources()
	{
		if (m_state_service && m_state_service->GetScene())
		{
			std::vector<std::shared_ptr<Component::IComponent>> components = m_state_service->GetScene()->GetSceneComponents();

			m_light_sources.clear();

			std::copy_if(components.begin(), components.end(), std::back_inserter(m_light_sources),
				[](const std::shared_ptr<Component::IComponent>& cpt) { return cpt->GetIsALightSource(); });
		}
	}

	void PhysicsService::RemoveLightSources()
	{
		for (std::vector<std::shared_ptr<Component::IComponent>>::iterator it = m_light_sources.begin(); it != m_light_sources.end(); ++it)
		{
			if (it[0])
			{
				it[0]->Clean();
				it->reset();
			}
		}


		m_light_sources.clear();
	}

}

