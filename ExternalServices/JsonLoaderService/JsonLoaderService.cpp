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
		m_file_exist = false;
		SQ_EXTSERVICE_DEBUG("JSON Loader service SUCCESSFULLY initialized");
	}

	void JsonLoaderService::DeInit()
	{
		SQ_EXTSERVICE_DEBUG("JSON Loader service shutdown");
		for (std::map<Enums::JsonType, std::unique_ptr<nlohmann::json>>::iterator it = m_json_contents.begin(); it != m_json_contents.end(); ++it)
		{
			if (it->second)
			{
				it->second.reset();
			}
		}

		m_json_contents.clear();
	}

	void JsonLoaderService::SaveScene(std::string const filename, std::shared_ptr<Services::SceneEntity> scene)
	{
		if (m_json_contents.contains(Enums::JsonType::Scene) && m_json_contents.at(Enums::JsonType::Scene))
		{
			m_json_contents.at(Enums::JsonType::Scene).reset();
			m_json_contents.erase(Enums::JsonType::Scene);
		}
		
		m_json_contents.insert_or_assign(Enums::JsonType::Scene, this->ConvertToJsonFormat(scene));
		this->SaveFile(filename, Enums::JsonType::Scene);
	}

	void JsonLoaderService::SaveConfigs(std::shared_ptr<ConfigEntity> config)
	{
		if (m_json_contents.contains(Enums::JsonType::Config) && m_json_contents.at(Enums::JsonType::Config))
		{
			m_json_contents.at(Enums::JsonType::Config).reset();
			m_json_contents.erase(Enums::JsonType::Config);
		}

		m_json_contents.insert_or_assign(Enums::JsonType::Config, this->ConvertToJsonFormat(config));
		this->SaveFile(Constants::CONFIGFILE, Enums::JsonType::Config);
		
	}

	void JsonLoaderService::SaveFile(std::string const filename, Enums::JsonType json_type)
	{
		if (!filename.empty())
		{
			std::ofstream flux_out(filename + Constants::JSONEXT);
			if (flux_out.is_open() && m_json_contents.contains(json_type) && m_json_contents.at(json_type))
			{
				flux_out << m_json_contents.at(json_type)->dump(4);
				flux_out.close();
			}
		}
		
	}

	std::shared_ptr<Services::SceneEntity> JsonLoaderService::GetScene(std::string const filename)
	{
		if (m_json_contents.contains(Enums::JsonType::Scene) && m_json_contents.at(Enums::JsonType::Scene))
		{
			m_json_contents.at(Enums::JsonType::Scene).reset();
			m_json_contents.erase(Enums::JsonType::Scene);
		}

		m_file_exist = false;
		m_json_contents.insert_or_assign(Enums::JsonType::Scene, this->ReadFile(filename));

		return this->ConvertToScene();
	}

	std::shared_ptr<ConfigEntity> JsonLoaderService::GetConfigs()
	{
		if (m_json_contents.contains(Enums::JsonType::Config) && m_json_contents.at(Enums::JsonType::Config))
		{
			m_json_contents.at(Enums::JsonType::Config).reset();
			m_json_contents.erase(Enums::JsonType::Config);
		}

		m_file_exist = false;
		m_json_contents.insert_or_assign(Enums::JsonType::Config, this->ReadFile(Constants::CONFIGFILE));
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
				m_file_exist = true;
				return std::make_unique<nlohmann::json>(json::parse(flux_in));
			}
			catch (const std::exception& e)
			{
				SQ_EXTSERVICE_ERROR("Class {} in function {} : Exception found when parsing [{}] file", __FILE__, __FUNCTION__, filename + Constants::JSONEXT);
				SQ_EXTSERVICE_DEBUG("{}", e.what());
			}

			flux_in.close();
		}

		return nullptr;
	}

	std::unique_ptr<json> JsonLoaderService::ConvertToJsonFormat(std::shared_ptr<Services::SceneEntity> scene)
	{
		std::vector<json> renderers_json_format;
		std::string selected_skybox;
		glm::vec3 direction_light;
		bool is_there_direction_light;
		if (scene)
		{
			std::vector<std::shared_ptr<Component::IComponent>> components = scene->GetSceneComponents();
			for (std::vector<std::shared_ptr<Component::IComponent>>::iterator it = components.begin(); it != components.end(); it++)
			{
				json renderer_json_format = {
					{"type", it[0]->GetType()},
					{"color", {it[0]->GetBackgroundColor().x, it[0]->GetBackgroundColor().y, it[0]->GetBackgroundColor().z, it[0]->GetBackgroundColor().a}},
					{"position", {it[0]->GetPosition().x, it[0]->GetPosition().y, it[0]->GetPosition().z}},
					{"size", {it[0]->GetSize().x, it[0]->GetSize().y, it[0]->GetSize().z}},
					{"texture_name", it[0]->GetTextureName()},
					{"mixe_texture_color", it[0]->GetMixeTextureColor()},
					{"is_light_source", it[0]->GetIsALightSource()},
					{"ambiant_occlusion", it[0]->GetAmbiantOcclusion()},
					{"specular_shininess", it[0]->GetSpecularShininess()},
					{"specular_strength", it[0]->GetSpecularStrength()},
					{"light_type", it[0]->GetLightType()}
				};
				renderers_json_format.push_back(renderer_json_format);
			}
			selected_skybox = scene->GetSelectedSkybox();
			direction_light = scene->GetDirectionLight();
			is_there_direction_light = scene->GetIsThereDirectionLight();
		}
		json j = 
		{ 
			{"components", renderers_json_format},
			{"selected_skybox", selected_skybox},
			{"direction_light", {direction_light.x, direction_light.y, direction_light.z}},
			{"is_there_direction_light", is_there_direction_light}
			
		};
		return std::make_unique<json>(j);
	}

	std::unique_ptr<json> JsonLoaderService::ConvertToJsonFormat(std::shared_ptr<ConfigEntity> config)
	{
		json json_config = { 
			{"create_scenes", config->GetCreatedScenes()}, 
			{"grid_scaling_trigger", config->GetGridScalingTrigger()},
			{"grid_spacing_ratio", config->GetGridSpacingRatio()},
			{"render_grid", config->GetRenderGrid()},
			{"bloom_strength", config->GetBloomStrength()},
			{"activate_bloom", config->GetBloom()},
			{"render_debug", config->GetRenderDebug()},
			{"available_skybox", config->GetAvailableSkybox()},
			{"render_skybox", config->GetRenderSkybox()},
			{"activate_depth", config->GetDepth()},
			{"available_textures", config->GetAvailableTextures()},
			{"activate_multisample", config->GetMultiSample()}
		};
		return std::make_unique<json>(json_config);
	}

	std::shared_ptr<Services::SceneEntity> JsonLoaderService::ConvertToScene()
	{
		std::shared_ptr<Services::SceneEntity> scene = std::make_shared<Services::SceneEntity>();

		std::vector<std::shared_ptr<Component::IComponent>> components;
		
		if (m_json_contents.contains(Enums::JsonType::Scene) && m_json_contents.at(Enums::JsonType::Scene) && m_file_exist)
		{
			json json_components = m_json_contents.at(Enums::JsonType::Scene)->at("components");
			for (json::iterator it = json_components.begin(); it != json_components.end(); ++it)
			{
				json j = this->GetStringNode(std::make_unique<json>(*it), "type");
				json j2 = this->GetStringNode(std::make_unique<json>(*it), "light_type");
				glm::vec3 position = this->GetVec3Node(std::make_unique<json>(*it), "position");
				glm::vec4 color = this->GetVec4Node(std::make_unique<json>(*it), "color");
				glm::vec3 size = this->GetVec3Node(std::make_unique<json>(*it), "size");
				std::string texture_name = this->GetStringNode(std::make_unique<json>(*it), "texture_name");
				bool mixe = this->GetBoolNode(std::make_unique<json>(*it), "mixe_texture_color");
				bool is_light_source = this->GetBoolNode(std::make_unique<json>(*it), "is_light_source");
				float ambiant_occlusion = this->GetFloatNode(std::make_unique<json>(*it), "ambiant_occlusion");
				int specular_shininess = this->GetIntNode(std::make_unique<json>(*it), "specular_shininess");
				float specular_strength = this->GetFloatNode(std::make_unique<json>(*it), "specular_strength");

				switch (j.template get<Enums::RendererType>())
				{
				case Enums::RendererType::TRIANGLE:
				case Enums::RendererType::SQUARE:
				case Enums::RendererType::CUBE:
				case Enums::RendererType::SPHERE:
					components.push_back(std::make_shared<Component::ComponentBase>(position, size, j.template get<Enums::RendererType>(), color, is_light_source, ambiant_occlusion, 
						specular_shininess, specular_strength, j2.template get<Enums::LightType>()));
					break;
				case Enums::RendererType::CUBE_TEXTURED:
				case Enums::RendererType::SQUARE_TEXTURED:
				case Enums::RendererType::TRIANGLE_TEXTURED:
				case Enums::RendererType::SPHERE_TEXTURED:
					components.push_back(std::make_shared<Component::TexturedComponent>(position, size, j.template get<Enums::RendererType>(), texture_name, mixe, is_light_source, ambiant_occlusion, 
						specular_shininess, specular_strength, j2.template get<Enums::LightType>()));
					break;
				default:
					break;
				}
			}
		}

		scene->SetSceneComponents(components);
		scene->SetSelectedSkybox(this->GetStringNode(Enums::JsonType::Scene, "selected_skybox"));
		scene->SetDirectionLight(this->GetVec3Node(Enums::JsonType::Scene, "direction_light"));
		scene->SetIsThereDirectionLight(this->GetBoolNode(Enums::JsonType::Scene, "is_there_direction_light"));
		return scene;
	}

	std::shared_ptr<ConfigEntity> JsonLoaderService::ConvertToConfigEntity()
	{
		std::shared_ptr<ConfigEntity> config = std::make_shared<ConfigEntity>();
		if (m_file_exist)
		{
			config->SetCreatedScene(this->GetStringVectorNode(Enums::JsonType::Config, "create_scenes"));
			config->SetGridScalingTrigger(this->GetFloatNode(Enums::JsonType::Config, "grid_scaling_trigger"));
			config->SetGridSpacingRatio(this->GetIntNode(Enums::JsonType::Config, "grid_spacing_ratio"));
			config->SetRenderGrid(this->GetBoolNode(Enums::JsonType::Config, "render_grid"));
			config->SetBloomStrength(this->GetIntNode(Enums::JsonType::Config, "bloom_strength"));
			config->SetBloom(this->GetBoolNode(Enums::JsonType::Config, "activate_bloom"));
			config->SetRenderDebug(this->GetBoolNode(Enums::JsonType::Config, "render_debug"));
			config->SetAvailableSkybox(this->GetStringVectorNode(Enums::JsonType::Config, "available_skybox"));
			config->SetRenderSkybox(this->GetBoolNode(Enums::JsonType::Config, "render_skybox"));
			config->SetDepth(this->GetBoolNode(Enums::JsonType::Config, "activate_depth"));
			config->SetAvailableTextures(this->GetStringVectorNode(Enums::JsonType::Config, "available_textures"));
			config->SetMutliSample(this->GetBoolNode(Enums::JsonType::Config, "activate_multisample"));
		}
		
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

	std::string JsonLoaderService::GetStringNode(Enums::JsonType json_type, std::string node_name)
	{
		if (m_json_contents.contains(json_type) && m_json_contents.at(json_type))
		{
			std::string node = m_json_contents.at(json_type)->value(node_name, Constants::NONE);
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

	glm::vec3 JsonLoaderService::GetVec3Node(Enums::JsonType json_type, std::string node_name)
	{
		if (m_json_contents.contains(json_type) && m_json_contents.at(json_type))
		{
			json node = m_json_contents.at(json_type)->at(node_name);

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

	std::vector<std::string> JsonLoaderService::GetStringVectorNode(Enums::JsonType json_type, std::string node_name)
	{
		if (m_json_contents.contains(json_type) && m_json_contents.at(json_type))
		{
			json node = m_json_contents.at(json_type)->at(node_name);
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

	float JsonLoaderService::GetFloatNode(Enums::JsonType json_type, std::string node_name)
	{
		if (m_json_contents.contains(json_type) && m_json_contents.at(json_type))
		{
			float node = m_json_contents.at(json_type)->value(node_name, 0.f);
			if (node == 0.f)
			{
				SQ_EXTSERVICE_ERROR("Class {} in function {} : Cannot found [{}] node", __FILE__, __FUNCTION__, node_name);
				return 0.f;
			}

			SQ_EXTSERVICE_TRACE("Node [{}] successfully readed", node_name);
			return node;
		}


		return 0.f;
	}

	int JsonLoaderService::GetIntNode(Enums::JsonType json_type, std::string node_name)
	{
		if (m_json_contents.contains(json_type) && m_json_contents.at(json_type))
		{
			int node = m_json_contents.at(json_type)->value(node_name, 0);
			if (node == 0)
			{
				SQ_EXTSERVICE_ERROR("Class {} in function {} : Cannot found [{}] node", __FILE__, __FUNCTION__, node_name);
				return 2;
			}

			SQ_EXTSERVICE_TRACE("Node [{}] successfully readed", node_name);
			return node;
		}
		return 2;
	}

	int JsonLoaderService::GetIntNode(std::unique_ptr<nlohmann::json> json_content, std::string node_name)
	{
		if (json_content)
		{
			json node = json_content->at(node_name);
			json_content.reset();
			if (node == Constants::NONE)
			{
				SQ_EXTSERVICE_ERROR("Class {} in function {} : Cannot found [{}] node", __FILE__, __FUNCTION__, node_name);
				return 0;

			}

			SQ_EXTSERVICE_TRACE("Node [{}] successfully readed", node_name);
			return node;
		}
		return 0;
	}

	bool JsonLoaderService::GetBoolNode(Enums::JsonType json_type, std::string node_name)
	{
		if (m_json_contents.contains(json_type) && m_json_contents.at(json_type))
		{
			bool node = m_json_contents.at(json_type)->value(node_name, true);

			SQ_EXTSERVICE_TRACE("Node [{}] successfully readed", node_name);
			return node;
		}
		return false;
	}

	bool JsonLoaderService::GetBoolNode(std::unique_ptr<nlohmann::json> json_content, std::string node_name)
	{
		if (json_content)
		{
			json node = json_content->at(node_name);
			json_content.reset();
			if (node == Constants::NONE)
			{
				SQ_EXTSERVICE_ERROR("Class {} in function {} : Cannot found [{}] node", __FILE__, __FUNCTION__, node_name);
				return false;

			}

			SQ_EXTSERVICE_TRACE("Node [{}] successfully readed", node_name);
			return node;
		}

		return false;
	}

	float JsonLoaderService::GetFloatNode(std::unique_ptr<nlohmann::json> json_content, std::string node_name)
	{
		if (json_content)
		{
			json node = json_content->at(node_name);
			json_content.reset();
			if (node == Constants::NONE)
			{
				SQ_EXTSERVICE_ERROR("Class {} in function {} : Cannot found [{}] node", __FILE__, __FUNCTION__, node_name);
				return 0.0f;

			}

			SQ_EXTSERVICE_TRACE("Node [{}] successfully readed", node_name);
			return node;
		}

		return 0.0f;
	}

}

