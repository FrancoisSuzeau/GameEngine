/******************************************************************************************************************************************/
// File : JsonService.cpp
// Purpose : Implementing service shader
/******************************************************************************************************************************************/
#include "JsonService.hpp"

namespace Services
{
	void JsonService::Init()
	{
		m_json_loader_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::JsonLoaderService>();
		if (!m_json_loader_service)
		{
			SQ_APP_ERROR("Class {} in function {} : Json loader service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}

	void JsonService::DeInit()
	{
		m_json_loader_service.reset();
	}

	void JsonService::SaveScene()
	{
		if (m_json_loader_service)
		{
			m_json_loader_service->SaveFile(filename);
		}
	}
	void JsonService::SetFileName(std::string const new_filename)
	{
		filename = new_filename;
	}
}

