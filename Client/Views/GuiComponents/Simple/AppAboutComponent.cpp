/******************************************************************************************************************************************/
// File : AppAboutComponent.cpp
// Purpose : Implementing the GUI view app info
/******************************************************************************************************************************************/

#include "AppAboutComponent.hpp"

namespace Views
{
	AppAboutComponent::~AppAboutComponent()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}
	}
	AppAboutComponent::AppAboutComponent()
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}
	void AppAboutComponent::Render()
	{
		if (m_state_service)
		{
			bool test = m_state_service->getShowInfos();
			if (test) 
			{ 
				ImGui::ShowAboutWindow(&test); 
				//m_state_service->setGuiOpen(true);
			}
			/*else
			{
				m_state_service->setGuiOpen(false);
			}*/
			m_state_service->setShowInfos(test);
		}
	}
}