/******************************************************************************************************************************************/
// File : CameraService.cpp
// Purpose : Implementing service shader
/******************************************************************************************************************************************/
#include "CameraService.hpp"

namespace Services
{
	void CameraService::Init()
	{
		m_camera_pos = glm::vec3(0.f, 0.f, 3.f);
		

        m_camera_up = glm::vec3(0.f, 1.f, 0.f);
        m_camera_target = glm::vec3(0.f, 0.f, -1.f);
        
        m_mouse_motions_dir = glm::vec2(0.f);
        m_yaw = -90.f;
        m_pitch = 0.f;

        m_camera_speed = 0.01f;

	}

	void CameraService::DeInit()
	{
		
	}

	void CameraService::Update(glm::vec2 const mouse_motions_dir, bool const mouse_button[8])
	{
        m_mouse_motions_dir = mouse_motions_dir;
        for (int i = 0; i < 8; i++)
        {
            m_mouse_button[i] = mouse_button[i];
        }
	}
    void CameraService::OrienteCamera()
    {
        this->ChangePitch();
        this->ChangeYaw();
        glm::vec3 dir;
        
        dir.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        dir.y = sin(glm::radians(m_pitch));
        dir.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_camera_target = glm::normalize(dir);
    }
    glm::mat4 CameraService::GetCameraView() const
    {
        return glm::lookAt(m_camera_pos, m_camera_pos + m_camera_target, m_camera_up);
    }

    glm::vec3 CameraService::GetPos() const
    {
        return m_camera_pos;
    }
    glm::vec3 CameraService::GetTarget() const
    {
        return m_camera_target;
    }
   
    void CameraService::MoveCamera()
    {
        if (m_mouse_button[SDL_BUTTON_MIDDLE])
        {
            m_camera_pos -= glm::normalize(glm::cross(m_camera_target, m_camera_up)) * m_camera_speed * m_mouse_motions_dir.x;
            m_camera_pos += m_camera_target * m_mouse_motions_dir.y * m_camera_speed;
        }
    }
    void CameraService::ChangeHigh(float const offset)
    {
        m_camera_pos.y += offset * m_camera_speed * 20.f;
    }
    void CameraService::ChangePitch()
    {
        if (m_mouse_button[SDL_BUTTON_RIGHT] )
        {
            m_pitch += m_mouse_motions_dir.y * m_camera_speed * 10.f;
            if (m_pitch > 89.0f)
            {
                m_pitch = 89.0f;
            }
            else if (m_pitch < -89.f)
            {
                m_pitch = -89.f;
            }
        }
    }

    void CameraService::ChangeYaw()
    {
        if (m_mouse_button[SDL_BUTTON_RIGHT])
        {
            m_yaw += m_mouse_motions_dir.x * m_camera_speed * 10.f;
        }
    }



}

