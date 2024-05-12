/******************************************************************************************************************************************/
// File : LoaderComponent.cpp
// Purpose : Implementing the GUI view tools
/******************************************************************************************************************************************/

#include "LoaderComponent.hpp"

namespace Views
{
	LoaderComponent::~LoaderComponent()
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
	LoaderComponent::LoaderComponent(std::shared_ptr<ViewModels::IViewModel> parent) : m_selected(-1)
	{
		m_parent_view_model = parent;
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
		w_width = 1000;
		w_height = 800;
	}
	void LoaderComponent::Render(int const index)
	{
		if (m_state_service)
		{
			float img_size = 500.f;
			ImGui::SetNextWindowPos(ImVec2((float)((m_state_service->getWidth() / 2) - (w_width / 2)), (float)((m_state_service->getHeight() / 2.f) - (w_height / 2))));
			ImGui::SetNextWindowSize(ImVec2((float)w_width, (float)w_height));

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar
				| ImGuiWindowFlags_NoScrollbar
				| ImGuiWindowFlags_NoResize
				| ImGuiWindowFlags_NoBackground;

			ImGuiStyle& style = ImGui::GetStyle();
			frame_rounding_save = style.FrameRounding;
			style.FrameRounding = 50.f;

			if (ImGui::Begin("Icon+ProgressBar", NULL, window_flags))
			{
				ImGui::SetCursorPosX((w_width / 2.f) - (img_size / 2.f));
				ImGui::SetCursorPosY(5.f);

				ImVec2 p_min = ImGui::GetCursorScreenPos();                 // Top-left
				ImVec2 p_max = ImVec2(p_min.x + img_size, p_min.y + img_size);
				ImVec2 uv_min = ImVec2(1.0f, 1.0f);                 // Top-left
				ImVec2 uv_max = ImVec2(0.0f, 0.0f);                 // Lower-right
				ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 0.8f);
				ImGui::GetWindowDrawList()->AddImageRounded((ImTextureID)(intptr_t)m_state_service->GetSqueamishTextureId(), p_min, p_max, uv_min, uv_max, ImGui::GetColorU32(tint_col), img_size);

				ImGui::SetCursorPosX(0.f);
				ImGui::SetCursorPosY(img_size + 100.f);
				ImGui::Separator();

				ImGui::SetCursorPosX(5.f);
				ImGui::SetCursorPosY(w_height - 50.f);

				char buf[32];
				sprintf_s(buf, "%d/%d", (int)(index), m_state_service->GetTotalRessources());
				ImGui::ProgressBar(index / (float)m_state_service->GetTotalRessources(), ImVec2(-1.f, 20.f), buf);
				ImGui::End();
			}

			style.FrameRounding = frame_rounding_save;

			
		}
	}
}