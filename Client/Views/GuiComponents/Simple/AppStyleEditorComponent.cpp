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

		if (m_parent_view_model)
		{
			m_parent_view_model.reset();
		}
	}
	AppStyleEditorComponent::AppStyleEditorComponent(std::shared_ptr<ViewModels::IViewModel> parent)
	{
		m_parent_view_model = parent;
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}
	void AppStyleEditorComponent::Render()
	{
		if (m_state_service)
		{
			bool show_editor = m_state_service->getShowStyleEditor();
			if (show_editor)
			{
				ImGui::Begin("Dear ImGui Style Editor", &show_editor, ImGuiWindowFlags_NoCollapse);
				ImGui::ShowStyleEditor();
				ImGui::End();
			}
			
			m_state_service->setShowStyleEditor(show_editor);
		}
	}
}