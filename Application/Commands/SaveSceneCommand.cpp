/******************************************************************************************************************************************/
// File : SaveSceneCommand.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "SaveSceneCommand.hpp"

namespace Commands
{
	SaveSceneCommand::SaveSceneCommand(std::string const filename)
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_state_service = container->GetReference<Services::StateService>();
			if (!m_state_service)
			{
				SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}
			else
			{
				m_state_service->setFileName(filename);
			}

			m_loader_service = container->GetReference<Services::LoaderService>();
			if (!m_loader_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Json service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
	}

	SaveSceneCommand::SaveSceneCommand()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_state_service = container->GetReference<Services::StateService>();
			if (!m_state_service)
			{
				SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_loader_service = container->GetReference<Services::LoaderService>();
			if (!m_loader_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Json service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
	}

	SaveSceneCommand::~SaveSceneCommand()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}

		if (m_loader_service)
		{
			m_loader_service.reset();
		}
	}

	void SaveSceneCommand::Execute()
	{
		if (m_loader_service && m_state_service)
		{
			m_loader_service->SaveScene(m_state_service->GetScene(), m_state_service->getFileName());
			m_state_service.reset();
			m_loader_service.reset();
		}
	}
}