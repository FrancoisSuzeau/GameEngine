/******************************************************************************************************************************************/
// File : CopyComponentCommand.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "CopyComponentCommand.hpp"

namespace Commands
{
	CopyComponentCommand::CopyComponentCommand(std::shared_ptr<Renderers::IRenderer> renderer_to_copy) : m_renderer_to_copy(renderer_to_copy)
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

	CopyComponentCommand::~CopyComponentCommand()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}

		if (m_renderer_to_copy)
		{
			m_renderer_to_copy.reset();
		}
	}

	void CopyComponentCommand::Execute()
	{
		if (m_state_service && m_renderer_to_copy)
		{
			SQ_APP_TRACE("Component copied !");
		}
	}
}