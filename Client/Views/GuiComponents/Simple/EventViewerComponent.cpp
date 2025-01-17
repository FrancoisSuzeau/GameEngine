/******************************************************************************************************************************************/
// File : EventViewerComponent.cpp
// Purpose : Implementing the GUI view metrics
/******************************************************************************************************************************************/

#include "EventViewerComponent.hpp"

namespace Views
{
	EventViewerComponent::~EventViewerComponent()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}

		if (m_parent_view_model)
		{
			m_parent_view_model.reset();
		}
	}
	EventViewerComponent::EventViewerComponent(std::shared_ptr<ViewModels::IViewModel> parent)
	{
		m_parent_view_model = parent;
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}
	void EventViewerComponent::Render()
	{
		if (m_state_service)
		{
			bool show_event = m_state_service->getShowEvent();

			if (show_event) 
			{
				if (ImGui::Begin("Event viewer", &show_event, ImGuiWindowFlags_NoCollapse))
				{
					ImGuiIO& io = ImGui::GetIO();

					// Display Mouse state
					if (ImGui::IsMousePosValid())
						ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
					else
						ImGui::Text("Mouse pos: <INVALID>");
					ImGui::Text("Mouse delta: (%g, %g)", io.MouseDelta.x, io.MouseDelta.y);

					int count = IM_ARRAYSIZE(io.MouseDown);
					ImGui::Text("Mouse down:");         for (int i = 0; i < count; i++) if (ImGui::IsMouseDown(i)) { ImGui::SameLine(); ImGui::Text("b%d (%.02f secs)", i, io.MouseDownDuration[i]); }
					ImGui::Text("Mouse clicked:");      for (int i = 0; i < count; i++) if (ImGui::IsMouseClicked(i)) { ImGui::SameLine(); ImGui::Text("b%d (%d)", i, ImGui::GetMouseClickedCount(i)); }
					ImGui::Text("Mouse released:");     for (int i = 0; i < count; i++) if (ImGui::IsMouseReleased(i)) { ImGui::SameLine(); ImGui::Text("b%d", i); }
					ImGui::Text("Mouse wheel: %.1f", io.MouseWheel);
					ImGui::Text("Pen Pressure: %.1f", io.PenPressure); // Note: currently unused
				}
				ImGui::End();
			}
			m_state_service->setShowEvent(show_event);
		}
	}
}