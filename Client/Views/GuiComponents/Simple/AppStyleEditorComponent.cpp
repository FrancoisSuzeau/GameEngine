/******************************************************************************************************************************************/
// File : AppStyleEditorComponent.cpp
// Purpose : Implementing the GUI view app style editor
/******************************************************************************************************************************************/

#include "AppStyleEditorComponent.hpp"

namespace Views
{
	AppStyleEditorComponent::~AppStyleEditorComponent()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}
	}
	AppStyleEditorComponent::AppStyleEditorComponent()
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("State service is not referenced yet");
		}
	}
	void AppStyleEditorComponent::Render()
	{
		if (m_state_service)
		{
			bool test = m_state_service->getShowStyleEditor();
			if (test)
			{
				ImGui::Begin("Dear ImGui Style Editor", &test);
				ImGui::ShowStyleEditor();
				ImGui::End();
			}
			m_state_service->setShowStyleEditor(test);
		}
	}
}