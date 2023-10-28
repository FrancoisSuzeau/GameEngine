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
		m_configs = this->ReadFile();
		SQ_EXTSERVICE_DEBUG("JSON service SUCCESSFULLY initialized");

	}

	void JsonLoaderService::DeInit()
	{
		SQ_EXTSERVICE_DEBUG("JSON service shutdown");
		if (m_scene)
		{
			m_scene.reset();
		}

		if (m_configs)
		{
			m_configs.reset();
		}
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
				flux_out << content->dump(4);
				flux_out.close();
			}
		}
		else
		{
			SQ_EXTSERVICE_ERROR("Class {} in function {} : No filename was given", __FILE__, __FUNCTION__);
		}
	}

	std::vector<std::shared_ptr<Renderers::IRenderer>> JsonLoaderService::GetScene(std::string const filename)
	{
		m_scene = this->ReadFile(filename);

		return this->ConvertToRenderers();
	}

	std::shared_ptr<nlohmann::json> JsonLoaderService::ReadFile(std::string filename)
	{
		if (filename.empty())
		{
			filename = Constants::CONFIGFILE;
		}
		std::ifstream flux_in(filename + Constants::JSONEXT);
		if (flux_in.is_open())
		{
			SQ_EXTSERVICE_TRACE("JSON [{}] file SUCCESSFULLY readed", filename + Constants::JSONEXT);
			try
			{
				return std::make_shared<nlohmann::json>(json::parse(flux_in));
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

		return nullptr;
	}

	std::shared_ptr<json> JsonLoaderService::ConvertToJsonFormat(std::vector<std::shared_ptr<Renderers::IRenderer>> renderers)
	{
		std::vector<json> renderers_json_format;
		for (std::vector<std::shared_ptr<Renderers::IRenderer>>::iterator it = renderers.begin(); it != renderers.end(); it++)
		{
			json renderer_json_format = {
				{"type", it[0]->GetType()},
				{"color", {it[0]->GetBackgroundColor().x, it[0]->GetBackgroundColor().y, it[0]->GetBackgroundColor().z}},
				{"position", {it[0]->GetPosition().x, it[0]->GetPosition().y, it[0]->GetPosition().z}},
				{"size", {it[0]->GetSize().x, it[0]->GetSize().y, it[0]->GetSize().z}}
			};
			renderers_json_format.push_back(renderer_json_format);
		}
		json j(renderers_json_format);
		return std::make_shared<json>(j);
	}

	std::vector<std::shared_ptr<Renderers::IRenderer>> JsonLoaderService::ConvertToRenderers()
	{
		std::vector<std::shared_ptr<Renderers::IRenderer>> renderers;
		for (json::iterator it = m_scene->begin(); it != m_scene->end(); ++it)
		{
			json j = this->GetStringNode(std::make_shared<json>(*it), "type");
			switch (j.template get<Enums::RendererType>())
			{
			case Enums::RendererType::GRID:
				renderers.push_back(std::make_shared<Renderers::Grid>(48));
				break;
			case Enums::RendererType::TRIANGLE:
				renderers.push_back(std::make_shared<Renderers::Triangle>());
				break;
			case Enums::RendererType::SQUARE:
				renderers.push_back(std::make_shared<Renderers::Square>());
				break;
			case Enums::RendererType::SQUARE_TEXTURED:
				break;
			default:
				break;
			}

		}

		return renderers;
	}

	int JsonLoaderService::GetIntNode(std::shared_ptr<nlohmann::json> json_content, std::string node_name)
	{
		return 0;
	}

	std::string JsonLoaderService::GetStringNode(std::shared_ptr<nlohmann::json> json_content, std::string node_name)
	{
		if (json_content)
		{
			std::string node = json_content->value(node_name, Constants::NONE);
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

