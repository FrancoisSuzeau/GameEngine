/******************************************************************************************************************************************/
// File : SingleRendererContextMenu.cpp
// Purpose : Implementing the GUI view tools
/******************************************************************************************************************************************/

#include "SingleRendererContextMenu.hpp"

namespace Views
{
	SingleRendererContextMenu::~SingleRendererContextMenu()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}
	}
	SingleRendererContextMenu::SingleRendererContextMenu()
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}
	void SingleRendererContextMenu::Render()
	{

		if (m_state_service)
		{
			int w_width = 400;
			int w_height = 500;
			std::shared_ptr<Renderers::IRenderer> selected_renderer = m_state_service->getSelectedRenderer();
			if (selected_renderer)
			{
				ImGuiColorEditFlags flags = ImGuiColorEditFlags_AlphaPreviewHalf | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_PickerHueWheel;
				glm::vec4 color = selected_renderer->GetBackgroundColor();
				glm::vec4 ref_color = m_state_service->getRefColor();
				ImGui::SetNextWindowPos(ImVec2((float)((m_state_service->getWidth() / 2) - (w_width / 2)), (float)((m_state_service->getHeight() / 2) - (w_height / 2))));
				ImGui::SetNextWindowSize(ImVec2((float)w_width, (float)w_height));
				
				
				if (ImGui::Begin(" "))
				{
					m_state_service->setPopupHovered(ImGui::IsWindowHovered());
					ImGuiStyle& style = ImGui::GetStyle();
					float frame_rounding_save = style.FrameRounding;
					style.FrameRounding = 20.f;

					ImGui::ColorPicker4("MyColor##4", (float*)&color, flags, (float*) &ref_color);
					selected_renderer->SetBackgroundColor(color);
					
					style.FrameRounding = frame_rounding_save;

				}
				ImGui::End();
				selected_renderer.reset();
			}
		}
		
	}
}