/******************************************************************************************************************************************/
// File : ActualizeCommand.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "ActualizeCommand.hpp"

namespace Commands
{
	ActualizeCommand::ActualizeCommand()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_state_service = container->GetReference<Services::StateService>();
			if (!m_state_service)
			{
				SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
	}

	ActualizeCommand::~ActualizeCommand()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}
	}

	void ActualizeCommand::Execute()
	{
		if (m_state_service && m_state_service->getGridRenderer() && m_state_service->getActualize())
		{
			m_state_service->getGridRenderer()->Actualize(m_state_service->getConfigs()->GetGridScalingRatio());
			m_state_service->setActualize(false);
			m_state_service->setScalingWay(Enums::ScallingWay::EMPTY);
		}
	}
}