/******************************************************************************************************************************************/
// File : MenuToolsComponent.cpp
// Purpose : Implementing the GUI view app style editor
/******************************************************************************************************************************************/

#include "MenuToolsComponent.hpp"

namespace Views
{
	MenuToolsComponent::MenuToolsComponent() : metrics(false), tools(false), infos(false), style(false)
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("State service is not referenced yet");
		}
	}
	void MenuToolsComponent::Render()
	{
		if (ImGui::BeginMenu("Tools"))
		{
			if (m_state_service)
			{
				metrics = m_state_service->getShowMetrics();
				tools = m_state_service->getShowTools();
				infos = m_state_service->getShowInfos();
				style = m_state_service->getShowStyleEditor();
				ImGui::MenuItem("Metrics/Debugger", NULL, &metrics);
				ImGui::MenuItem("Stack Tool", NULL, &tools);
				ImGui::MenuItem("Style Editor", NULL, &style);
				ImGui::MenuItem("About Dear ImGui", NULL, &infos);
				m_state_service->setShowMetrics(metrics);
				m_state_service->setShowTools(tools);
				m_state_service->setShowInfos(infos);
				m_state_service->setShowStyleEditor(style);
			}
			ImGui::EndMenu();
		}
		
	}
}