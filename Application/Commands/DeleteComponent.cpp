/******************************************************************************************************************************************/
// File : DeleteComponent.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "DeleteComponent.hpp"

namespace Commands
{
	DeleteComponent::DeleteComponent()
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

	DeleteComponent::~DeleteComponent()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}
	}

	void DeleteComponent::Execute()
	{
		if (m_state_service)
		{
			m_state_service->deleteComponent();
			SQ_APP_TRACE("Component deleted !");
		}
	}
}