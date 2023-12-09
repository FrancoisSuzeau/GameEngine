/******************************************************************************************************************************************/
// File : MouseInputService.cpp
// Purpose : Implementing the mouse input service
/******************************************************************************************************************************************/
#include "MouseInputService.hpp"

namespace Services
{
	void MouseInputService::Init()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_state_service = container->GetReference<StateService>();
			m_camera_service = container->GetReference<CameraService>();
			if (!m_state_service)
			{
				SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}
			else
			{
				m_proj_mat = m_state_service->GetProjectionMatrix();

			}

			if (!m_camera_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Camera service is not referenced yet", __FILE__, __FUNCTION__);
			}
			else
			{
				m_view_mat = m_camera_service->GetCameraView();
			}
		}

		m_x_pos = 0;
		m_y_pos = 0;

		m_x_motion_dir = 0.f;
		m_y_motion_dir = 0.f;

		for (int i = 0; i < 8; i++)
		{
			m_mouse_button[i] = false;
		}
	}

	void MouseInputService::DeInit()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}

		if (m_camera_service)
		{
			m_camera_service.reset();
		}
	}
	void MouseInputService::Update(SDL_Event event)
	{
		m_x_motion_dir = 0.f;
		m_y_motion_dir = 0.f;

		if (m_camera_service)
		{
			switch (event.type)
			{
				//click on the mouse
				case SDL_MOUSEBUTTONDOWN:
					m_mouse_button[event.button.button] = true;

					break;

				case SDL_MOUSEBUTTONUP:
					m_mouse_button[event.button.button] = false;
					break;

				//mouse is moving
				case SDL_MOUSEMOTION:
					m_x_motion_dir = (float)event.motion.xrel;
					m_y_motion_dir = (float)event.motion.yrel;

					m_x_pos = event.motion.x;
					m_y_pos = event.motion.y;
					break;
				case SDL_MOUSEWHEEL:
					if (event.wheel.y > 0) { m_camera_service->ChangeHigh(-1.f); }
					if (event.wheel.y < 0) { m_camera_service->ChangeHigh(1.f); }
					break;

				default:
					break;
			}
			
			m_view_mat = m_view_mat = m_camera_service->GetCameraView();
			this->SetNormalizedDeviceCoords();
			m_current_ray = this->CalculateMouseRay();
		}
	}

	glm::vec3 MouseInputService::GetCurrentRay() const
	{
		return m_current_ray;
	}
	bool* MouseInputService::GetMouseButton()
	{
		return m_mouse_button;
	}
	glm::vec2 MouseInputService::GetMotionDir() const
	{
		return glm::vec2(m_x_motion_dir, m_y_motion_dir);
	}
	glm::vec3 MouseInputService::CalculateMouseRay()
	{
		if (m_state_service)
		{
			glm::vec4 clip_coords = glm::vec4(m_mouse_normalized_pos.x, m_mouse_normalized_pos.y, -1.f, 1.f);
			glm::vec4 eye_coords = this->ConvertToEyeCoords(clip_coords);
			glm::vec3 world_ray = this->ConvertToWorldCoords(eye_coords);

			return world_ray;
		}
		return glm::vec3(0.f);
	}
	void MouseInputService::SetNormalizedDeviceCoords()
	{
		if (m_state_service)
		{
			float mouse_x = (float)m_x_pos;
			float mouse_y = (float)m_y_pos;

			float x = (2.f * mouse_x) / m_state_service->getWidth() - 1.f;
			float y = (2.f * mouse_y) / m_state_service->getHeight() - 1.f;
			m_mouse_normalized_pos = glm::vec3(x, -y, 0.f);
		}

	}
	glm::vec4 MouseInputService::ConvertToEyeCoords(glm::vec4 clip_coords)
	{
		if (m_state_service)
		{
			glm::mat4 inverted_proj_mat = glm::inverse(m_state_service->GetProjectionMatrix());
			glm::vec4 eye_coords = inverted_proj_mat * clip_coords;

			return glm::vec4(eye_coords.x, eye_coords.y, -1.f, 0.f);
		}
		return glm::vec4(0.f);
	}
	glm::vec3 MouseInputService::ConvertToWorldCoords(glm::vec4 eye_coords)
	{
		glm::mat4 inverted_view_mat = glm::inverse(m_view_mat);
		glm::vec4 ray_world = inverted_view_mat * eye_coords;
		return glm::normalize(glm::vec3(ray_world));

	}
}

