/******************************************************************************************************************************************/
// File : StackToolsComponent.cpp
// Purpose : Implementing the GUI view tools
/******************************************************************************************************************************************/

#include "StackToolsComponent.hpp"

namespace Views
{
	StackToolsComponent::~StackToolsComponent()
	{
		m_state_service.reset();
	}
	StackToolsComponent::StackToolsComponent()
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
	}
	void StackToolsComponent::Render()
	{
		if (m_state_service)
		{
			bool test = m_state_service->getShowTools();
			if (test) { ImGui::ShowStackToolWindow(&test); }
			m_state_service->setShowTools(test);
		}
	}
}