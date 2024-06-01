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

	glm::vec3 PhysicsService::UpdateDirectionalLight(Enums::AngleToUpdate type, float angle)
	{
		glm::vec3 axis = glm::vec3(0.f);
		switch (type)
		{
		case Enums::AZYMUTH:
			axis = glm::vec3(0.f, 1.f, 0.f);
			theta = angle;
			break;
		case Enums::POLAR:
			axis = glm::vec3(1.f, 0.f, 0.f);
			phi = angle;
			break;
		default:
			break;
		}

		glm::mat4 dir_mat = glm::rotate(glm::mat4(1.f), angle, axis);


		return glm::vec3(dir_mat * glm::vec4(0, 0, -1, 0));
	}

	float PhysicsService::GetTheta() const
	{
		return theta;
	}

	float PhysicsService::GetPhi() const
	{
		return phi;
	}

	void PhysicsService::SetTheta(glm::vec3 const direction)
	{
		theta = std::atan2(direction.y, direction.x);
	}

	void PhysicsService::SetPhi(glm::vec3 const direction)
	{
		float r = std::sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
		phi = std::acos(direction.z / r);
	}

}

