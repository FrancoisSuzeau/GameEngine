/******************************************************************************************************************************************/
// File : StartComponent.cpp
// Purpose : Implementing the GUI view tools
/******************************************************************************************************************************************/

#include "StartComponent.hpp"

namespace Views
{
	StartComponent::~StartComponent() 
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}
	}
	StartComponent::StartComponent() : selected(-1)
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}
	void StartComponent::Render()
	{
		if (m_state_service && m_parent_view_model)
		{
			int w = 400;
			int h = 200;
			ImGui::SetNextWindowPos(ImVec2((float)((m_state_service->getWidth() / 2) - (w / 2)), (float)((m_state_service->getHeight() / 2) - (h / 2))));
			ImGui::SetNextWindowSize(ImVec2((float)w, (float)h));
			if (ImGui::Begin("Select recent work :"))
			{
				int n = 0;
				std::vector<std::string> created_scene = m_parent_view_model->GetConfig()->GetCreatedScenes();
				for (auto it : created_scene)
				{
					if (ImGui::Selectable(it.c_str(), n == selected))
					{
						selected = n;
					}
					n++;
				}

				if (selected != -1)
				{
					ImGuiStyle& style = ImGui::GetStyle();
					float frame_rounding_save = style.FrameRounding;
					style.FrameRounding = 20.f;
					if (ImGui::Button("Select", ImVec2((float)(w - 15), 30.f)))
					{
						m_state_service->setFileName(created_scene[selected]);
						m_state_service->setExit(true);
					}

					style.FrameRounding = frame_rounding_save;
				}
				
				ImGui::End();
			}
		}
	}
}