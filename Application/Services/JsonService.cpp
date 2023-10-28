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
	std::vector<std::shared_ptr<Renderers::IRenderer>> JsonService::LoadScene()
	{
		
		if (m_json_loader_service)
		{
			return m_json_loader_service->GetScene(Constants::DEFAULT_FILENAME);
		}

		return std::vector<std::shared_ptr<Renderers::IRenderer>>();
	}
	void JsonService::SetFileName(std::string const new_filename)
	{
		filename = new_filename;
	}
	void JsonService::SetScene(std::vector<std::shared_ptr<Renderers::IRenderer>> const renderers)
	{
		m_renderers = renderers;
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

