/******************************************************************************************************************************************/
// File : StackToolsComponent.cpp
// Purpose : Implementing the GUI view tools
/******************************************************************************************************************************************/

#include "StackToolsComponent.hpp"

namespace Views
{
	StackToolsComponent::~StackToolsComponent()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}
	}
	StackToolsComponent::StackToolsComponent()
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}
	void StackToolsComponent::Render()
	{
		if (m_state_service)
		{
			bool show_tool = m_state_service->getShowTools();
			if (show_tool) 
			{
				ImGui::ShowStackToolWindow(&show_tool); 
			}
			m_state_service->setShowTools(show_tool);
		}
	}
}