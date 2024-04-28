/******************************************************************************************************************************************/
// File : MenuSettingsComponent.cpp
// Purpose : Implementing the GUI view app style editor
/******************************************************************************************************************************************/

#include "MenuSettingsComponent.hpp"

namespace Views
{
	MenuSettingsComponent::MenuSettingsComponent(std::shared_ptr<ViewModels::IViewModel> parent)
	{
		m_parent_view_model = parent;
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}
	MenuSettingsComponent::~MenuSettingsComponent()
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
	void MenuSettingsComponent::Render()
	{
		if(m_parent_view_model && m_state_service)
		{
			std::string config_pannel = m_state_service->getConfigPannel(); 

			
			if (ImGui::BeginMenu("Settings", !m_state_service->getGuiOpen()))
			{
				if (m_state_service->getContinued())
				{
					ImGui::PushID(0);
					ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.f, 0.f, 0.f));
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.f, 0.f, 0.f));
					if (ImGui::Button("Global rendering"))
					{
						config_pannel = Constants::SCENE_CONFIG_PANNEL;
					}
					ImGui::PopStyleColor(2);
					ImGui::PopID();
					ImGui::SameLine(); ImGui::TextDisabled("Open the config scene pannel");
				}

				ImGui::TextDisabled("Another settings ...");
				ImGui::EndMenu();
			}

			m_state_service->setConfigPannel(config_pannel);
		}
		
	}
}