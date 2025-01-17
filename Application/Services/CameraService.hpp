/******************************************************************************************************************************************/
// File : CameraService.hpp
// Purpose : A service for communicate between loader and shader
/******************************************************************************************************************************************/
#ifndef CAMERASERVICE_H
#define CAMERASERVICE_H

#include "IService.hpp"
#include "Logger.hpp"
#include "Enums/EngineEnum.hpp"

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

		void Update(glm::vec2 const mouse_motions_dir, bool const mouse_button[8]);
		void OrienteCamera();
		glm::mat4 GetCameraView() const;

		void  SetCameraState(Enums::CameraLocked state);


		void SetCameraParameters(glm::vec3 const camera_pos, float const camera_pitch, float const camera_yaw);

		glm::vec3 GetPos() const;
		glm::vec3 GetTarget() const;
		float  GetPitch() const;
		float GetYaw() const;
		void MoveCamera();
		void ChangeHigh(float const offset);

	private:
		glm::vec2 m_mouse_motions_dir;
		glm::vec3 m_camera_pos;
		glm::vec3 m_camera_target;
		glm::vec3 m_camera_up;
		bool m_mouse_button[8];
		
		Enums::CameraLocked m_lock_state;
		
		float m_yaw;
		float m_pitch;
		float m_camera_speed;

		
		void ChangePitch();
		void ChangeYaw();

	};
}

#endif