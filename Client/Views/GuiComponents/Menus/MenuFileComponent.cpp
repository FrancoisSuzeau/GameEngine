/******************************************************************************************************************************************/
// File : MenuFileComponent.cpp
// Purpose : Implementing the GUI view app style editor
/******************************************************************************************************************************************/

#include "MenuFileComponent.hpp"

namespace Views
{
	MenuFileComponent::MenuFileComponent()
	{
		
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
					m_parent_view_model->OnCommand(new Commands::LoadNewShaderCommand("triangle", Enums::NORMAL));
				}
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) {}
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