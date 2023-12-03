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
			m_mouse_picker_service = container->GetReference<Services::MousePickerService>();
			m_state_service = container->GetReference<Services::StateService>();
			
			if (!m_mouse_picker_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Mouse picker service is not referenced yet", __FILE__, __FUNCTION__);
			}

			if (!m_state_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
	}

	void Draggable::Clean()
	{
		if (m_mouse_picker_service)
		{
			m_mouse_picker_service.reset();
		}

		if (m_state_service)
		{
			m_state_service.reset();
		}
	}
	void Draggable::OnSelectRenderer(std::shared_ptr<Renderers::IRenderer> renderer)
	{
		bool is_intersected = false;
		if (renderer)
		{
			switch (renderer->GetType())
			{
			case Enums::RendererType::TRIANGLE:
			{
				std::shared_ptr<Renderers::Triangle> t = std::dynamic_pointer_cast<Renderers::Triangle> (renderer);
				t.reset();
			}
			break;
			case Enums::RendererType::SQUARE:
			{
				std::shared_ptr<Renderers::Square> s = std::dynamic_pointer_cast<Renderers::Square> (renderer);
				is_intersected = CalculateIntersection(s);
				s.reset();
			}
			break;
			case Enums::RendererType::NONE:
			default:
				break;
			}

			renderer->SetSelected(is_intersected);
		}
	}

	bool Draggable::CalculateIntersection(std::shared_ptr<Renderers::Square> renderer)
	{
		if (m_mouse_picker_service && renderer && m_state_service)
		{
			float half_width = renderer->GetSize().x / 2.f;
			float half_height = renderer->GetSize().y / 2.f;
			glm::vec3 ray_origin = m_state_service->getCameraPos();
			glm::vec3 quad_pos = renderer->GetPosition();
			glm::vec3 normal(0.0f, 0.0f, 1.0f);
			glm::vec3 to_quad = quad_pos - ray_origin;

			float distance_to_plane = glm::dot(to_quad, normal) / glm::dot(m_mouse_picker_service->GetCurrentRay(), normal);

			if (distance_to_plane < 0.f)
			{
				return false;
			}

			glm::vec3 intersection_point = ray_origin + distance_to_plane * m_mouse_picker_service->GetCurrentRay();

			if (glm::abs(intersection_point.x - quad_pos.x) <= half_width && glm::abs(intersection_point.y - quad_pos.y) <= half_height)
			{
				return true;
			}

			return false;
		}
	}
}