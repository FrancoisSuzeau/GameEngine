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
#include "Renderers/Renderers.hpp"
#include <string>
#include <iostream>

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
		void SaveScene(std::string const filename, std::vector<std::shared_ptr<Renderers::IRenderer>> renderers);
		void SaveConfigs(std::map<std::string, std::string> config_map);
		std::vector<std::shared_ptr<Renderers::IRenderer>> GetScene(std::string const filename);
		std::map<std::string, std::string> GetConfigs();
	private:
		std::shared_ptr<nlohmann::json> m_configs;
		std::shared_ptr<nlohmann::json> m_scene;
		void SaveFile(std::string const filename, std::shared_ptr<nlohmann::json> const content);
		std::shared_ptr<nlohmann::json> ReadFile(std::string filename);
		std::shared_ptr<nlohmann::json> ConvertToJsonFormat(std::vector<std::shared_ptr<Renderers::IRenderer>> renderers);
		std::shared_ptr<nlohmann::json> ConvertToJsonFormat(std::map<std::string, std::string> map_config);
		std::vector<std::shared_ptr<Renderers::IRenderer>> ConvertToRenderers();
		std::map<std::string, std::string> ConvertToConfigMap();
		std::string GetStringNode(std::shared_ptr<nlohmann::json> json_content, std::string node_name);
		glm::vec3 GetVec3Node(std::shared_ptr<nlohmann::json> json_content, std::string node_name);
		
	};
}

#endif