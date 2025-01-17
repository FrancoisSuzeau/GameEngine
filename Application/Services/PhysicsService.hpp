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

#include "IComponent.hpp"
#include "OpenGLService.hpp"


namespace Services {

	typedef struct
	{
		float constant;
		float linear;
		float quadratic;

	} Attenuation_constants;

	class PhysicsService : public IService
	{

	public:
		void Init() override;
		void DeInit() override;


		glm::vec3 UpdateDirectionalLight(Enums::AngleToUpdate type, float const theta, float const phi);

		float GetTheta() const;
		float GetPhi() const;

		void SetTheta(glm::vec3 const direction);
		void SetPhi(glm::vec3 const direction);

		std::vector<Light> GetLigthSources() const;
		std::vector<unsigned int> GetLightSourcesTextureIds() const;

		void SetLightSourcesGeneralParameters();

		Attenuation_constants GetAttenuationConstant(int const distance);

		void SetLightsAttenuationsParameters();

		void RemoveLightSources();

		glm::vec3 CalculateCameraSpeed(glm::vec3 const current_pos, glm::vec3 const previous_pos);

	private:
		float m_theta;
		float m_phi;
		std::shared_ptr<StateService> m_state_service;
		std::vector<Light> m_light_sources;
		std::vector<Attenuation_constants> m_attenuation_constants;
		std::vector<int> m_attenuation_distance;
		std::vector<unsigned int> m_light_texture_ids;
		float m_delta_time;

		void SetAttenuationConstants();
		
	};
}

#endif