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
	StartComponent::StartComponent() : m_selected(-1)
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
		w_width = 400;
		w_height = 200;
	}
	void StartComponent::Render()
	{
		if (m_state_service && m_parent_view_model && !m_state_service->getContinued())
		{
			
			ImGui::SetNextWindowPos(ImVec2((float)((m_state_service->getWidth() / 2) - (w_width / 2)), (float)((m_state_service->getHeight() / 2) - (w_height / 2))));
			ImGui::SetNextWindowSize(ImVec2((float)w_width, (float)w_height));
			ImGuiStyle& style = ImGui::GetStyle();
			frame_rounding_save = style.FrameRounding;
			std::vector<std::string> created_scene = m_state_service->getConfigs()->GetCreatedScenes();
			if (!created_scene.empty())
			{
				if (ImGui::Begin("Select recent work :"))
				{
					int n = 0;

					for (auto it : created_scene)
					{
						if (ImGui::Selectable(it.c_str(), n == m_selected))
						{
							m_selected = n;
						}
						n++;
					}

					if (m_selected != -1)
					{
						style.FrameRounding = 20.f;
						ImGui::SetCursorPosY(w_height - 45.f);
						if (ImGui::Button("Select", ImVec2((float)(w_width - 15.f), 30.f)))
						{
							m_parent_view_model->AddCommand(std::make_unique<Commands::LoadSceneCommand>(created_scene[m_selected]));
							m_parent_view_model->AddCommand(std::make_unique<Commands::ExitCommand>(std::bind(&Services::StateService::setContinued, m_state_service, true)));
							m_parent_view_model->OnCommand();

						}

						style.FrameRounding = frame_rounding_save;
					}

					ImGui::End();
				}
			}
			else
			{
				m_state_service->setContinued(true);
			}
		}
	}
}