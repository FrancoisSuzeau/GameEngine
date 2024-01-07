/******************************************************************************************************************************************/
// File : Draggable.cpp
// Purpose : Implementing the draggable component
/******************************************************************************************************************************************/

#include "Draggable.hpp"

namespace Component
{
	Draggable::Draggable()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_mouse_input_service = container->GetReference<Services::MouseInputService>();
			m_state_service = container->GetReference<Services::StateService>();
			m_camera_service = container->GetReference < Services::CameraService>();
			m_keyboard_input_service = container->GetReference<Services::KeyboardInputService>();
			
			if (!m_mouse_input_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Mouse picker service is not referenced yet", __FILE__, __FUNCTION__);
			}

			if (!m_state_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}

			if (!m_camera_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Camera service is not referenced yet", __FILE__, __FUNCTION__);
			}

			if (!m_keyboard_input_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Keyboard input service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
	}

	void Draggable::Clean()
	{
		if (m_mouse_input_service)
		{
			m_mouse_input_service.reset();
		}

		if (m_state_service)
		{
			m_state_service.reset();
		}

		if (m_camera_service)
		{
			m_camera_service.reset();
		}

		if (m_keyboard_input_service)
		{
			m_keyboard_input_service.reset();
		}
	}
	void Draggable::OnSelectRenderer(std::shared_ptr<Renderers::IRenderer> renderer)
	{
		this->CalculateIsComponentSelected(renderer);
	}

	void Draggable::OnHoverRenderers(std::shared_ptr<Renderers::IRenderer> renderer)
	{
		if (renderer)
		{
			bool is_intersected = CalculateIntersection(renderer);
			renderer->SetHovered(is_intersected);
		}
	}

	void Draggable::OnUnSelectedComponents(std::vector<std::shared_ptr<Renderers::IRenderer>> renderers)
	{
		if (m_mouse_input_service && m_keyboard_input_service)
		{
			if (m_mouse_input_service->GetMouseButton()[SDL_BUTTON_LEFT] && !m_keyboard_input_service->GetKeys()[SDL_SCANCODE_LCTRL])
			{
				for (std::vector<std::shared_ptr<Renderers::IRenderer>>::iterator it = renderers.begin(); it != renderers.end(); it++)
				{
					if (it[0])
					{
						it[0]->SetSelected(false);
					}
				}

				m_state_service->setMouseClicked(true);
			}

			if (m_mouse_input_service->GetMouseButton()[SDL_BUTTON_LEFT] == false)
			{
				m_state_service->setMouseClicked(false);
			}
		}
	}

	bool Draggable::CalculateIntersection(std::shared_ptr<Renderers::IRenderer> renderer)
	{
		if (m_mouse_input_service && renderer && m_state_service && m_camera_service)
		{
			float half_width = renderer->GetSize().x / 2.f;
			float half_height = renderer->GetSize().y / 2.f;
			glm::vec3 ray_origin = m_camera_service->GetPos();
			glm::vec3 quad_pos = renderer->GetPosition();
			glm::vec3 normal(0.0f, 0.0f, 1.0f);
			glm::vec3 to_quad = quad_pos - ray_origin;

			float distance_to_plane = glm::dot(to_quad, normal) / glm::dot(m_mouse_input_service->GetCurrentRay(), normal);

			if (distance_to_plane < 0.f)
			{
				return false;
			}

			glm::vec3 intersection_point = ray_origin + distance_to_plane * m_mouse_input_service->GetCurrentRay();

			if (glm::abs(intersection_point.x - quad_pos.x) <= half_width && glm::abs(intersection_point.y - quad_pos.y) <= half_height)
			{
				return true;
			}

			return false;
		}

		return false;
	}
	void Draggable::CalculateIsComponentSelected(std::shared_ptr<Renderers::IRenderer> renderer)
	{
		if (renderer && m_mouse_input_service && m_state_service && m_keyboard_input_service)
		{
			if (renderer->GetHovered() && m_mouse_input_service->GetMouseButton()[SDL_BUTTON_LEFT] && m_keyboard_input_service->GetKeys()[SDL_SCANCODE_LCTRL] && !m_state_service->getMouseClicked())
			{
				bool selected_status = renderer->GetSelected();
				renderer->SetSelected(!selected_status);
				m_state_service->setMouseClicked(true);

			}

			if (m_mouse_input_service->GetMouseButton()[SDL_BUTTON_LEFT] == false)
			{
				m_state_service->setMouseClicked(false);
			}
		}
	}
}