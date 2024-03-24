/******************************************************************************************************************************************/
// File : JsonLoaderService.hpp
// Purpose : A service loading json files
/******************************************************************************************************************************************/
#ifndef JSONLOADERSERVICE_H
#define JSONLOADERSERVICE_H

#include <fstream>
#include <cassert>
#include "Constants/StringConstants.hpp"
#include "Logger.hpp"

#include <nlohmann/json.hpp>

#include "IService.hpp"
//#include "Renderers/Renderers.hpp"
#include "Components/Components.hpp"
#include <string>
#include <iostream>
#include "ConfigEntity.hpp"

namespace Enums {
	NLOHMANN_JSON_SERIALIZE_ENUM(RendererType, {
	{RendererType::NONE, nullptr},
	{RendererType::GRID, "grid"},
	{RendererType::SKYBOX, "skybox"},
	{RendererType::SQUARE, "square"},
	{RendererType::SQUARE_TEXTURED, "square_textured"},
	{RendererType::TRIANGLE, "triangle"}
		})
}

namespace Services {

	class JsonLoaderService : public IService
	{
	public:
		void Init() override;
		void DeInit() override;
		void SaveScene(std::string const filename, std::vector<std::shared_ptr<Component::IComponent>> renderers);
		void SaveConfigs(std::unique_ptr<ConfigEntity> config);
		std::vector<std::shared_ptr<Component::IComponent>> GetScene(std::string const filename);
		std::unique_ptr<ConfigEntity> GetConfigs();
	private:
		std::unique_ptr<nlohmann::json> m_configs;
		std::unique_ptr<nlohmann::json> m_scene;
		void SaveFile(std::string const filename, std::unique_ptr<nlohmann::json> const content);
		std::unique_ptr<nlohmann::json> ReadFile(std::string filename);
		std::unique_ptr<nlohmann::json> ConvertToJsonFormat(std::vector<std::shared_ptr<Component::IComponent>> renderers);
		std::unique_ptr<nlohmann::json> ConvertToJsonFormat(std::unique_ptr<ConfigEntity> map_config);
		std::vector<std::shared_ptr<Component::IComponent>> ConvertToRenderers();
		std::unique_ptr<ConfigEntity> ConvertToConfigEntity();
		std::string GetStringNode(std::unique_ptr<nlohmann::json> json_content, std::string node_name);
		glm::vec4 GetVec4Node(std::unique_ptr<nlohmann::json> json_content, std::string node_name);
		glm::vec3 GetVec3Node(std::unique_ptr<nlohmann::json> json_content, std::string node_name);
		std::vector<std::string> GetStringVectorNode(std::unique_ptr<nlohmann::json> json_content, std::string node_name);
		
	};
}

#endif