/******************************************************************************************************************************************/
// File : MenuToolsComponent.cpp
// Purpose : Implementing the GUI view app style editor
/******************************************************************************************************************************************/

#include "MenuToolsComponent.hpp"

namespace Views
{
	MenuToolsComponent::~MenuToolsComponent()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}

		this->SetParent(nullptr);
	}
	MenuToolsComponent::MenuToolsComponent() : metrics(false), tools(false), infos(false), style(false)
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}
	void MenuToolsComponent::Render()
	{
		if (m_parent_view_model && m_state_service)
		{
			if (ImGui::BeginMenu("Tools", m_state_service->getContinued()))
			{
				metrics = m_state_service->getShowMetrics();
				tools = m_state_service->getShowTools();
				infos = m_state_service->getShowInfos();
				style = m_state_service->getShowStyleEditor();
				s_event = m_state_service->getShowEvent();
				ImGui::MenuItem("Metrics/Debugger", NULL, &metrics);
				ImGui::MenuItem("Event viewer", NULL, &s_event);
				ImGui::MenuItem("Stack Tool", NULL, &tools);
				ImGui::MenuItem("Style Editor", NULL, &style);
				ImGui::MenuItem("About Dear ImGui", NULL, &infos);
				m_state_service->setShowMetrics(metrics);
				m_state_service->setShowTools(tools);
				m_state_service->setShowInfos(infos);
				m_state_service->setShowStyleEditor(style);
				m_state_service->setShowEvent(s_event);
				ImGui::EndMenu();
			}
		}
		
	}
}