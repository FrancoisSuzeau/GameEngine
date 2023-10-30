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

			m_state_service = container->GetReference<Services::StateService>();
			if (!m_state_service)
			{
				SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
	}

	void JsonService::DeInit()
	{
		if (m_json_loader_service)
		{
			m_json_loader_service.reset();
		}

		this->CleanRenderers();

	}

	void JsonService::SaveScene()
	{
		if (m_json_loader_service)
		{
			m_json_loader_service->SaveScene(filename, m_renderers);
			this->CleanRenderers();
		}
	}
	void JsonService::SaveConfigs()
	{
		if (m_json_loader_service)
		{
			m_json_loader_service->SaveConfigs(m_config);
		}
	}
	std::vector<std::shared_ptr<Renderers::IRenderer>> JsonService::LoadScene()
	{
		if (m_json_loader_service && m_state_service)
		{
			return m_json_loader_service->GetScene(m_state_service->getFileName());
		}

		return std::vector<std::shared_ptr<Renderers::IRenderer>>();
	}
	std::shared_ptr<ConfigEntity> JsonService::LoadConfigs()
	{
		if(m_json_loader_service)
		{
			m_config = m_json_loader_service->GetConfigs();
			return m_config;
		}
		return std::make_shared<ConfigEntity>();
	}
	void JsonService::SetFileName(std::string const new_filename)
	{
		filename = new_filename;
	}
	void JsonService::SetScene(std::vector<std::shared_ptr<Renderers::IRenderer>> const renderers)
	{
		m_renderers = renderers;
	}
	void JsonService::SetConfig(std::shared_ptr<ConfigEntity> const config)
	{
		m_config = config;
	}
	void JsonService::CleanRenderers()
	{
		for (std::vector<std::shared_ptr<Renderers::IRenderer>>::iterator it = m_renderers.begin(); it != m_renderers.end(); it++)
		{
			if (it[0])
			{
				it[0].reset();
			}
		}

		m_renderers.clear();
	}
}

