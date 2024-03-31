/******************************************************************************************************************************************/
// File : ConfirmComponent.cpp
// Purpose : Implementing the GUI view tools
/******************************************************************************************************************************************/

#include "ConfirmComponent.hpp"

namespace Views
{
	ConfirmComponent::~ConfirmComponent()
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
	ConfirmComponent::ConfirmComponent(std::shared_ptr<ViewModels::IViewModel> parent)
	{
		m_parent_view_model = parent;
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
		w_width = 400;
		w_height = 120;
	}
	void ConfirmComponent::Render()
	{
		if (m_state_service && m_parent_view_model)
		{
			
			bool show_confirm = m_state_service->getShowConfirm();
			if (show_confirm)
			{
				ImGui::SetNextWindowPos(ImVec2((float)((m_state_service->getWidth() / 2.f) - (w_width / 2.f)), (float)((m_state_service->getHeight() / 2.f) - (w_height / 2.f))));
				ImGui::SetNextWindowSize(ImVec2((float)w_width, (float)w_height));

				ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar
					| ImGuiWindowFlags_NoResize
					| ImGuiWindowFlags_NoCollapse;

				if (ImGui::Begin(" ", &show_confirm, window_flags))
				{
					ImGui::Text(m_state_service->getConfirmMessage().c_str());
					ImGuiStyle& style = ImGui::GetStyle();
					frame_rounding_save = style.FrameRounding;
					style.FrameRounding = 20.f;
					ImGui::SetCursorPosY((float)(w_height - 45.f));
					if (ImGui::Button("Accept", ImVec2((float)(w_width / 2.f - 15.f), 30.f)) && m_state_service)
					{
						m_parent_view_model->OnCommand();
						show_confirm = false;
					}
					ImGui::SetCursorPos(ImVec2((float)(w_width / 2.f), (float)(w_height - 45.f)));
					if (ImGui::Button("Cancel", ImVec2((float)(w_width / 2.f - 15.f), 30.f)) && m_state_service)
					{
						m_parent_view_model->DeleteCommmands();
						show_confirm = false;
					}
					style.FrameRounding = frame_rounding_save;

					ImGui::End();
				}
				
			}
			m_state_service->setShowConfirm(show_confirm);
		}
	}
}