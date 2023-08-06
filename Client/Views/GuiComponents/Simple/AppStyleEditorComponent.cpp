/******************************************************************************************************************************************/
// File : AppStyleEditorComponent.cpp
// Purpose : Implementing the GUI view app style editor
/******************************************************************************************************************************************/

#include "AppStyleEditorComponent.hpp"

namespace Views
{
	AppStyleEditorComponent::AppStyleEditorComponent()
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->make<Services::StateService>();
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