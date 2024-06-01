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


		/*glm::vec3 axis = glm::vec3(0.f);
		switch (type)
		{
		case Enums::AZYMUTH:
			axis = glm::vec3(0.f, 1.f, 0.f);
			phi = phi;
			break;
		case Enums::POLAR:
			axis = glm::vec3(1.f, 0.f, 0.f);
			theta = angle;
			break;
		default:
			break;
		}

		glm::mat4 dir_mat = glm::rotate(glm::mat4(1.f), angle, axis);


		return glm::vec3(dir_mat * glm::vec4(0, 0, -1, 0));*/
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

}

