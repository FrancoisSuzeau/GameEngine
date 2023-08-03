/******************************************************************************************************************************************/
// File : StackToolsComponent.cpp
// Purpose : Implementing the GUI view tools
/******************************************************************************************************************************************/

#include "StackToolsComponent.hpp"

namespace Views
{
	StackToolsComponent::StackToolsComponent()
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->make<Services::StateService>();
	}
	void StackToolsComponent::Render()
	{
		bool test = m_state_service->getShowTools();
		if (test) { ImGui::ShowStackToolWindow(&test); }
		m_state_service->setShowTools(test);
	}
}