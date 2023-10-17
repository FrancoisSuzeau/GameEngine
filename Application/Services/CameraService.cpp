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
		for (int i = 0; i < 8; i++)
		{
			m_mouse_button[i] = false;
		}

        m_camera_up = glm::vec3(0.f, 1.f, 0.f);
        m_camera_target = glm::vec3(0.f, 0.f, -1.f);

		m_x = 0;
		m_y = 0;
		m_x_rel = 0.f;
		m_y_rel = 0.f;

        m_yaw = -90.f;
        m_pitch = 0.f;
        m_fov = 45.f;

	}

	void CameraService::DeInit()
	{
		
	}

	void CameraService::UpdateEvent(SDL_Event event)
	{
        m_x_rel = 0.f;
        m_y_rel = 0.f;

        switch (event.type)
        {

            ////click on the mouse
        case SDL_MOUSEBUTTONDOWN:
            m_mouse_button[event.button.button] = true;

            break;

        case SDL_MOUSEBUTTONUP:
            m_mouse_button[event.button.button] = false;
            break;

            //mouse is moving
        case SDL_MOUSEMOTION:
            m_x = event.motion.x;
            m_y = event.motion.y;

            m_x_rel = (float)event.motion.xrel;
            m_y_rel = (float)event.motion.yrel;
            break;
        case SDL_MOUSEWHEEL:
            if (event.wheel.y > 0) { this->ChangeFov(-1.f); }
            if (event.wheel.y < 0) { this->ChangeFov(1.f); }
            break;

        default:
            break;
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
    float CameraService::GetFov() const
    {
        return m_fov;
    }
    void CameraService::ChangeFov(float offset)
    {
        m_fov += offset;
        if (m_fov < 1.f)
        {
            m_fov = 1.f;
        }
        if (m_fov > 45.f)
        {
            m_fov = 45.f;
        }
    }
    void CameraService::ChangePitch()
    {
        if (m_mouse_button[SDL_BUTTON_RIGHT])
        {
            m_pitch += m_y_rel * 0.1f;
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
            m_yaw += m_x_rel * 0.1f;
            
        }
    }



}

