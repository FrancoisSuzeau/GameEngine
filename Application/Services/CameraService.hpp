/******************************************************************************************************************************************/
// File : CameraService.hpp
// Purpose : A service for communicate between loader and shader
/******************************************************************************************************************************************/
#ifndef CAMERASERVICE_H
#define CAMERASERVICE_H

#include "IService.hpp"
#include "Logger.hpp"

#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Services {

	class CameraService : public IService
	{

	public:
		void Init() override;
		void DeInit() override;

		void UpdateEvent(SDL_Event event);
		void OrienteCamera();
		glm::mat4 GetCameraView() const;

		glm::vec3 GetPos() const;
		glm::vec3 GetTarget() const;
		void MoveCamera();

	private:
		
		glm::vec3 m_camera_pos;
		glm::vec3 m_camera_target;
		glm::vec3 m_camera_up;
		bool m_mouse_button[8];

		float m_x_rel;
		float m_y_rel;
		float m_yaw;
		float m_pitch;
		float m_camera_speed;

		void ChangeHigh(float offset);
		void ChangePitch();
		void ChangeYaw();

	};
}

#endif