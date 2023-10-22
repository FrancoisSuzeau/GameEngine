/******************************************************************************************************************************************/
// File : SaveSceneCommand.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "SaveSceneCommand.hpp"

using namespace Commands;

SaveSceneCommand::SaveSceneCommand(std::string const filename)
{
	m_json_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::JsonService>();
	if (!m_json_service)
	{
		SQ_APP_ERROR("Class {} in function {} : Json service is not referenced yet", __FILE__, __FUNCTION__);
	}
	else
	{
		m_json_service->SetFileName(filename);
	}
}

void SaveSceneCommand::Execute()
{
	if (m_json_service)
	{
		SQ_APP_INFO("Save scene command is called");
		m_json_service->SaveScene();
		m_json_service.reset();
	}
}
