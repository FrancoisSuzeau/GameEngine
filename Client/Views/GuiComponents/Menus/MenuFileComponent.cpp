/******************************************************************************************************************************************/
// File : MenuFileComponent.cpp
// Purpose : Implementing the GUI view app style editor
/******************************************************************************************************************************************/

#include "MenuFileComponent.hpp"

namespace Views
{
	MenuFileComponent::MenuFileComponent()
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}
	MenuFileComponent::~MenuFileComponent()
	{
		this->SetParent(nullptr);
		if (m_state_service)
		{
			m_state_service.reset();
		}
	}
	void MenuFileComponent::Render()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New")) {}
			if (ImGui::MenuItem("Open", "Ctrl+O")) {}
			if (ImGui::BeginMenu("Open Recent"))
			{
				if(ImGui::MenuItem("NewFile") && m_parent_view_model)
				{
					//m_parent_view_model->OnCommand(new Commands::LoadNewShaderCommand("triangle", Enums::NORMAL));
				}
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Save", "Ctrl+S") && m_parent_view_model) 
			{
				
				if (m_state_service)
				{
					m_parent_view_model->OnCommand(new Commands::SaveSceneCommand(m_state_service->getFileName()));
				}
			}
			if (ImGui::MenuItem("Save As..")) {}

			ImGui::Separator();

			if (ImGui::MenuItem("Quit", "Alt+F4") && m_parent_view_model)
			{
				m_parent_view_model->OnCommand(new Commands::ExitCommand());
			}
			ImGui::EndMenu();
		}
		
	}
}