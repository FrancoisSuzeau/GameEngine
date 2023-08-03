/******************************************************************************************************************************************/
// File : MenuEditComponent.cpp
// Purpose : Implementing the GUI view app style editor
/******************************************************************************************************************************************/

#include "MenuEditComponent.hpp"

namespace Views
{
	MenuEditComponent::MenuEditComponent()
	{
		
	}
	void MenuEditComponent::Render()
	{
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
	}
}