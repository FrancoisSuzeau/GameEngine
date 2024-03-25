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

	void JsonLoaderService::SaveScene(std::string const filename, std::vector<std::shared_ptr<Component::IComponent>> renderers)
	{
		if (m_scene)
		{
			m_scene.reset();
		}
		m_scene = this->ConvertToJsonFormat(renderers);
		this->SaveFile(filename, std::move(m_scene));
	}

	void JsonLoaderService::SaveConfigs(std::shared_ptr<ConfigEntity> config)
	{
		if (m_configs)
		{
			m_configs.reset();
		}

		m_configs = this->ConvertToJsonFormat(config);
		this->SaveFile(Constants::CONFIGFILE, std::move(m_configs));
	}

	void JsonLoaderService::SaveFile(std::string const filename, std::unique_ptr<nlohmann::json> content)
	{
		if (!filename.empty())
		{
			std::ofstream flux_out(filename + Constants::JSONEXT);
			if (flux_out.is_open() && content)
			{
				flux_out << content->dump(4);
				flux_out.close();
				content.reset();
			}
		}
		
	}

	std::vector<std::shared_ptr<Component::IComponent>> JsonLoaderService::GetScene(std::string const filename)
	{
		if (m_scene)
		{
			m_scene.reset();
		}
		m_scene = this->ReadFile(filename);

		return this->ConvertToRenderers();
	}

	std::shared_ptr<ConfigEntity> JsonLoaderService::GetConfigs()
	{
		if (m_configs)
		{
			m_configs.reset();
		}
		m_configs = this->ReadFile(Constants::CONFIGFILE);
		return this->ConvertToConfigEntity();
	}

	std::unique_ptr<nlohmann::json> JsonLoaderService::ReadFile(std::string const filename)
	{
		std::ifstream flux_in(filename + Constants::JSONEXT);
		if (flux_in.is_open())
		{
			SQ_EXTSERVICE_TRACE("JSON [{}] file SUCCESSFULLY readed", filename + Constants::JSONEXT);
			try
			{
				return std::make_unique<nlohmann::json>(json::parse(flux_in));
			}
			catch (const std::exception& e)
			{
				SQ_EXTSERVICE_ERROR("Class {} in function {} : Exception found when parsing [{}] file", __FILE__, __FUNCTION__, filename + Constants::JSONEXT);
				SQ_EXTSERVICE_DEBUG("{}", e.what());
			}
		}

		return nullptr;
	}

	std::unique_ptr<json> JsonLoaderService::ConvertToJsonFormat(std::vector<std::shared_ptr<Component::IComponent>> renderers)
	{
		std::vector<json> renderers_json_format;
		for (std::vector<std::shared_ptr<Component::IComponent>>::iterator it = renderers.begin(); it != renderers.end(); it++)
		{
			json renderer_json_format = {
				{"type", it[0]->GetType()},
				{"color", {it[0]->GetBackgroundColor().x, it[0]->GetBackgroundColor().y, it[0]->GetBackgroundColor().z, it[0]->GetBackgroundColor().a}},
				{"position", {it[0]->GetPosition().x, it[0]->GetPosition().y, it[0]->GetPosition().z}},
				{"size", {it[0]->GetSize().x, it[0]->GetSize().y, it[0]->GetSize().z}}
			};
			renderers_json_format.push_back(renderer_json_format);
		}
		json j(renderers_json_format);
		return std::make_unique<json>(j);
	}

	std::unique_ptr<json> JsonLoaderService::ConvertToJsonFormat(std::shared_ptr<ConfigEntity> config)
	{
		json json_config = { {"create_scenes", config->GetCreatedScenes()}};
		return std::make_unique<json>(json_config);
	}

	std::vector<std::shared_ptr<Component::IComponent>> JsonLoaderService::ConvertToRenderers()
	{
		std::vector<std::shared_ptr<Component::IComponent>> renderers;
		if (m_scene)
		{
			for (json::iterator it = m_scene->begin(); it != m_scene->end(); ++it)
			{
				json j = this->GetStringNode(std::make_unique<json>(*it), "type");
				glm::vec3 position = this->GetVec3Node(std::make_unique<json>(*it), "position");
				glm::vec4 color = this->GetVec4Node(std::make_unique<json>(*it), "color");
				glm::vec3 size = this->GetVec3Node(std::make_unique<json>(*it), "size");
				switch (j.template get<Enums::RendererType>())
				{
				case Enums::RendererType::TRIANGLE:
				case Enums::RendererType::SQUARE:
					renderers.push_back(std::make_shared<Component::ComponentBase>(position, size, j.template get<Enums::RendererType>(), color));
					break;
				case Enums::RendererType::SQUARE_TEXTURED:
					break;
				default:
					break;
				}
			}
			m_scene.reset();
		}


		return renderers;
	}

	std::shared_ptr<ConfigEntity> JsonLoaderService::ConvertToConfigEntity()
	{
		std::shared_ptr<ConfigEntity> config = std::make_shared<ConfigEntity>();
		config->SetCreatedScene(this->GetStringVectorNode(std::move(m_configs), "create_scenes"));
		return config;
	}

	std::string JsonLoaderService::GetStringNode(std::unique_ptr<nlohmann::json> json_content, std::string node_name)
	{
		if (json_content)
		{
			std::string node = json_content->value(node_name, Constants::NONE);
			json_content.reset();
			if (node == Constants::NONE)
			{
				SQ_EXTSERVICE_ERROR("Class {} in function {} : Cannot found [{}] node", __FILE__, __FUNCTION__, node_name);
				return Constants::NONE;
			}

			SQ_EXTSERVICE_TRACE("Node [{}] successfully readed", node_name);
			return node;
		}

		
		return Constants::NONE;

	}

	glm::vec4 JsonLoaderService::GetVec4Node(std::unique_ptr<nlohmann::json> json_content, std::string node_name)
	{
		if (json_content)
		{
			json node = json_content->at(node_name);
			json_content.reset();
			if (node == Constants::NONE)
			{
				SQ_EXTSERVICE_ERROR("Class {} in function {} : Cannot found [{}] node", __FILE__, __FUNCTION__, node_name);
				return glm::vec4(0.f);

			}

			SQ_EXTSERVICE_TRACE("Node [{}] successfully readed", node_name);
			return glm::vec4(node[0], node[1], node[2], node[3]);
		}

		
		return glm::vec4(0.f);
	}

	glm::vec3 JsonLoaderService::GetVec3Node(std::unique_ptr<nlohmann::json> json_content, std::string node_name)
	{
		if (json_content)
		{
			json node = json_content->at(node_name);
			json_content.reset();
			if (node == Constants::NONE)
			{
				SQ_EXTSERVICE_ERROR("Class {} in function {} : Cannot found [{}] node", __FILE__, __FUNCTION__, node_name);
				return glm::vec3(0.f);

			}

			SQ_EXTSERVICE_TRACE("Node [{}] successfully readed", node_name);
			return glm::vec3(node[0], node[1], node[2]);
		}

		return glm::vec3(0.f);
	}

	std::vector<std::string> JsonLoaderService::GetStringVectorNode(std::unique_ptr<nlohmann::json> json_content, std::string node_name)
	{
		if (json_content)
		{
			json node = json_content->at(node_name);
			json_content.reset();
			if (node == Constants::NONE)
			{
				SQ_EXTSERVICE_ERROR("Class {} in function {} : Cannot found [{}] node", __FILE__, __FUNCTION__, node_name);
				return std::vector<std::string>();
			}

			SQ_EXTSERVICE_TRACE("Node [{}] successfully readed", node_name);
			std::vector<std::string> vect;
			for (json::iterator it = node.begin(); it != node.end(); ++it)
			{
				vect.push_back(*it);
			}
			return vect;
		}
		return std::vector<std::string>();
	}

}

