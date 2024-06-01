/******************************************************************************************************************************************/
// File : PhysicsService.hpp
// Purpose : A service to handle mouse input
/******************************************************************************************************************************************/
#ifndef PHYSICSSERVICE_H
#define PHYSICSSERVICE_H

#include "IService.hpp"
#include "Container/Container.hpp"
#include "Logger.hpp"
#include "StateService.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Services {

	class PhysicsService : public IService
	{

	public:
		void Init() override;
		void DeInit() override;


		glm::vec3 UpdateDirectionalLight(Enums::AngleToUpdate type, float angle);

		float GetTheta() const;
		float GetPhi() const;

		void SetTheta(glm::vec3 const direction);
		void SetPhi(glm::vec3 const direction);

	private:
		float theta;
		float phi;
		std::shared_ptr<StateService> m_state_service;
		
	};
}

#endif