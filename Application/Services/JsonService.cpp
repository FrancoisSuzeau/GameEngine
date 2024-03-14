/******************************************************************************************************************************************/
// File : JsonService.cpp
// Purpose : Implementing service shader
/******************************************************************************************************************************************/
#include "JsonService.hpp"

namespace Services
{
	void JsonService::Init()
	{
		IoC::Container::Container *container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_json_loader_service = container->GetReference<Services::JsonLoaderService>();
			if (!m_json_loader_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Json loader service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
	}

	void JsonService::DeInit()
	{
		if (m_json_loader_service)
		{
			m_json_loader_service.reset();
		}
	}

	void JsonService::SaveScene(std::vector<std::shared_ptr<Component::IComponent>> const renderers, std::string const filename)
	{
		if (m_json_loader_service)
		{
			m_json_loader_service->SaveScene(filename, renderers);
		}
	}
	void JsonService::SaveConfigs(std::shared_ptr<ConfigEntity> configs)
	{
		if (m_json_loader_service)
		{
			m_json_loader_service->SaveConfigs(configs);
		}
	}
	std::vector<std::shared_ptr<Component::IComponent>> JsonService::LoadScene(std::string const filename)
	{
		if (m_json_loader_service)
		{
			return m_json_loader_service->GetScene(filename);
		}

		return std::vector<std::shared_ptr<Component::IComponent>>();
	}
	std::shared_ptr<ConfigEntity> JsonService::LoadConfigs()
	{
		if(m_json_loader_service)
		{
			return m_json_loader_service->GetConfigs();
		}
		return std::make_shared<ConfigEntity>();
	}
}

