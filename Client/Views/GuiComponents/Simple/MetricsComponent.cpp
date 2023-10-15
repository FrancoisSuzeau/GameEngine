/******************************************************************************************************************************************/
// File : MetricsComponent.cpp
// Purpose : Implementing the GUI view metrics
/******************************************************************************************************************************************/

#include "MetricsComponent.hpp"

namespace Views
{
	MetricsComponent::~MetricsComponent()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}
	}
	MetricsComponent::MetricsComponent()
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}
	void MetricsComponent::Render()
	{
		if (m_state_service)
		{
			bool test = m_state_service->getShowMetrics();
		
			if (test) { ImGui::ShowMetricsWindow(&test); }
		
			m_state_service->setShowMetrics(test);
		}
	}
}