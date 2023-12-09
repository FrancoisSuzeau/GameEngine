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

		void Update(glm::vec2 const mouse_motions_dir, bool const mouse_button[8], bool const keys[SDL_NUM_SCANCODES]);
		void OrienteCamera();
		glm::mat4 GetCameraView() const;

		glm::vec3 GetPos() const;
		glm::vec3 GetTarget() const;
		void MoveCamera();
		void ChangeHigh(float const offset);

	private:
		glm::vec2 m_mouse_motions_dir;
		glm::vec3 m_camera_pos;
		glm::vec3 m_camera_target;
		glm::vec3 m_camera_up;
		bool m_mouse_button[8];
		bool m_keys[SDL_NUM_SCANCODES];

		
		float m_yaw;
		float m_pitch;
		float m_camera_speed;

		
		void ChangePitch();
		void ChangeYaw();

	};
}

#endif