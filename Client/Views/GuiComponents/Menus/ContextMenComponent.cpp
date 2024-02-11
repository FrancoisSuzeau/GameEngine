/******************************************************************************************************************************************/
// File : ContextMenuComponent.cpp
// Purpose : Implementing the GUI view tools
/******************************************************************************************************************************************/

#include "ContextMenuComponent.hpp"

namespace Views
{
	ContextMenuComponent::~ContextMenuComponent()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}
	}
	ContextMenuComponent::ContextMenuComponent()
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}
	void ContextMenuComponent::Render()
	{

		if (m_state_service)
		{
			
		}
		
	}
}