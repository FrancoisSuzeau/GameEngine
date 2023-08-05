/******************************************************************************************************************************************/
// File : MetricsComponent.cpp
// Purpose : Implementing the GUI view metrics
/******************************************************************************************************************************************/

#include "MetricsComponent.hpp"

namespace Views
{
	MetricsComponent::MetricsComponent()
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->make<Services::StateService>();
	}
	void MetricsComponent::Render()
	{
		bool test = m_state_service->getShowMetrics();
		if (test) { ImGui::ShowMetricsWindow(&test); }
		m_state_service->setShowMetrics(test);
	}
}