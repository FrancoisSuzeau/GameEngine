/******************************************************************************************************************************************/
// File : MousePickerService.hpp
// Purpose : A service to handle picking object in scene
/******************************************************************************************************************************************/
#ifndef MOUSEPICKERSERVVICE_H
#define MOUSEPICKERSERVVICE_H

#include "IService.hpp"
#include "Services.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Services {

	class MousePickerService : public IService
	{

	public:
		void Init() override;
		void DeInit() override;
		void Update();
		glm::vec3 GetCurrentRay() const;

	private:
		glm::vec3 m_current_ray;
		glm::mat4 m_proj_mat;
		glm::mat4 m_view_mat;
		glm::vec3 m_mouse_normalized_pos;

		glm::vec3 CalculateMouseRay();
		void SetNormalizedDeviceCoords();
		glm::vec4 ConvertToEyeCoords(glm::vec4 clip_coords);
		glm::vec3 ConvertToWorldCoords(glm::vec4 eye_coords);

		std::shared_ptr<StateService> m_state_service;
	};
}

#endif