/******************************************************************************************************************************************/
// File : AppAboutComponent.cpp
// Purpose : Implementing the GUI view app info
/******************************************************************************************************************************************/

#include "AppAboutComponent.hpp"

namespace Views
{
	AppAboutComponent::AppAboutComponent()
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->make<Services::StateService>();
	}
	void AppAboutComponent::Render()
	{
		if (m_state_service)
		{
			bool test = m_state_service->getShowInfos();
			if (test) { ImGui::ShowAboutWindow(&test); }
			m_state_service->setShowInfos(test);
		}
	}
}