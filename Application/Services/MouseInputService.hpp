/******************************************************************************************************************************************/
// File : MouseInputService.hpp
// Purpose : A service to handle mouse input
/******************************************************************************************************************************************/
#ifndef MOUSEINPUTSERVICE_H
#define MOUSEINPUTSERVICE_H

#include "IService.hpp"
#include "StateService.hpp"
#include "CameraService.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Services {

	class MouseInputService : public IService
	{

	public:
		void Init() override;
		void DeInit() override;
		void Update(SDL_Event event);
		glm::vec3 GetCurrentRay() const;
		bool* GetMouseButton();
		glm::vec2 GetMotionDir() const;

	private:
		glm::vec3 m_current_ray;
		glm::mat4 m_proj_mat;
		glm::mat4 m_view_mat;
		glm::vec3 m_mouse_normalized_pos;
		int m_x_pos;
		int m_y_pos;
		float m_x_motion_dir;
		float m_y_motion_dir;
		bool m_mouse_button[8];

		glm::vec3 CalculateMouseRay();
		void SetNormalizedDeviceCoords();
		glm::vec4 ConvertToEyeCoords(glm::vec4 clip_coords);
		glm::vec3 ConvertToWorldCoords(glm::vec4 eye_coords);

		std::shared_ptr<StateService> m_state_service;
		std::shared_ptr<CameraService> m_camera_service;
	};
}

#endif