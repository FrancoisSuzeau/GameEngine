/******************************************************************************************************************************************/
// File : JsonLoaderService.cpp
// Purpose : Implementing JSON loader service
/******************************************************************************************************************************************/
#include "JsonLoaderService.hpp"

namespace Services
{
	using json = nlohmann::json;
	void JsonLoaderService::Init()
	{
		this->ReadFile(m_configs);
		SQ_EXTSERVICE_DEBUG("JSON service SUCCESSFULLY initialized");
		
	}

	void JsonLoaderService::DeInit()
	{
		SQ_EXTSERVICE_DEBUG("JSON service shutdown");
	}

	void JsonLoaderService::SaveScene(std::string const filename, std::vector<std::shared_ptr<Renderers::IRenderer>> renderers)
	{
		if (m_scene)
		{
			m_scene.reset();
		}
		m_scene = this->ConvertToJsonFormat(renderers);
		this->SaveFile(filename, m_scene);
	}

	void JsonLoaderService::SaveFile(std::string const filename, std::shared_ptr<nlohmann::json> content)
	{
		if (!filename.empty())
		{
			std::ofstream flux_out(filename + Constants::JSONEXT);
			if (flux_out.is_open())
			{
				flux_out << *content.get();
				flux_out.close();
			}
		}
		else
		{
			SQ_EXTSERVICE_ERROR("Class {} in function {} : No filename was given", __FILE__, __FUNCTION__);
		}
	}

	std::shared_ptr<Renderers::IRenderer> JsonLoaderService::GetScene(std::string const filename)
	{
		this->ReadFile(m_scene, filename);
		return std::shared_ptr<Renderers::IRenderer>();
	}

	void JsonLoaderService::ReadFile(std::shared_ptr<nlohmann::json> json_content, std::string filename)
	{
		if (filename.empty())
		{
			filename = Constants::CONFIGFILE;
		}
		std::ifstream flux_in(filename + Constants::JSONEXT);
		if (flux_in.is_open())
		{
			SQ_EXTSERVICE_TRACE("JSON [{}] file SUCCESSFULLY readed", filename + Constants::JSONEXT);
			if (json_content)
			{
				json_content.reset();
			}
			try
			{
				json_content = std::make_shared<nlohmann::json>(json::parse(flux_in));
			}
			catch (const std::exception& e)
			{
				SQ_EXTSERVICE_ERROR("Class {} in function {} : Exception found when parsing [{}] file", __FILE__, __FUNCTION__, filename + Constants::JSONEXT);
				SQ_EXTSERVICE_DEBUG("{}", e.what());
			}
		}
		else
		{
			SQ_EXTSERVICE_ERROR("Class {} in function {} : Cannot read or found [{}] file", __FILE__, __FUNCTION__, filename + Constants::JSONEXT);
		}
	}

	std::shared_ptr<json> JsonLoaderService::ConvertToJsonFormat(std::vector<std::shared_ptr<Renderers::IRenderer>> renderers)
	{
		std::vector<json> renderers_json_format;
		for (std::vector<std::shared_ptr<Renderers::IRenderer>>::iterator it = renderers.begin(); it != renderers.end(); it++)
		{
			json renderer_json_format = { 
				{"type", it[0]->GetType()}
			};
			renderers_json_format.push_back(renderer_json_format);
		}
		json j(renderers_json_format);
		return std::make_shared<json>(j);
	}

	std::string JsonLoaderService::GetStringNode(std::string node_name)
	{
		if (m_configs)
		{
			std::string node = m_configs->value(node_name, Constants::NONE);
			if (node == Constants::NONE)
			{
				SQ_EXTSERVICE_ERROR("Class {} in function {} : Cannot found [{}] node", __FILE__, __FUNCTION__, Constants::USERPREFNODE);
				return Constants::NONE;
				
			}

			SQ_EXTSERVICE_TRACE("Node [{}] successfully readed", Constants::USERPREFNODE);
			return node;
		}

		SQ_EXTSERVICE_ERROR("Class {} in function {} : No json was serialized - Cannot read node", __FILE__, __FUNCTION__);
		return Constants::NONE;;
		
	}

}

