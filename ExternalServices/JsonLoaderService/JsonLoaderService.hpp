/******************************************************************************************************************************************/
// File : JsonLoaderService.hpp
// Purpose : A service loading json files
/******************************************************************************************************************************************/
#ifndef JSONLOADERSERVICE_H
#define JSONLOADERSERVICE_H

#include <fstream>
#include <cassert>
#include <map>
#include "Constants/StringConstants.hpp"
#include "Logger.hpp"

#include <nlohmann/json.hpp>

#include "IService.hpp"

#include "Components/ComponentBase.hpp"
#include "Components/TexturedComponent.hpp"

#include <string>
#include <iostream>
#include "ConfigEntity.hpp"
#include "SceneEntity.hpp"
#include "Enums/EngineEnum.hpp"

namespace Enums {
	NLOHMANN_JSON_SERIALIZE_ENUM(RendererType, {
	{RendererType::NONE, nullptr},
	{RendererType::GRID, "grid"},
	{RendererType::SKYBOX, "skybox"},
	{RendererType::SQUARE, "square"},
	{RendererType::SQUARE_TEXTURED, "square_textured"},
	{RendererType::TRIANGLE, "triangle"},
	{RendererType::CUBE_TEXTURED, "cube_textured"},
	{RendererType::CUBE, "cube"},
	{RendererType::TRIANGLE_TEXTURED, "triangle_textured"},
	{RendererType::SPHERE, "sphere"},
	{RendererType::SPHERE_TEXTURED, "sphere_textured"}
		});

	NLOHMANN_JSON_SERIALIZE_ENUM(LightType, {
		{LightType::DIRECTIONALLIGHT, "directional_light"},
		{LightType::POINTLIGHT, "point_light"},
		{LightType::SPOTLIGHT, "spot_light"}
		});
}

namespace Services {

	class JsonLoaderService : public IService
	{
	public:
		void Init() override;
		void DeInit() override;
		void SaveScene(std::string const filename, std::shared_ptr<Services::SceneEntity> scene);
		void SaveConfigs(std::shared_ptr<ConfigEntity> config);
		std::shared_ptr<Services::SceneEntity> GetScene(std::string const filename);
		std::shared_ptr<ConfigEntity> GetConfigs();
	private:
		std::map<Enums::JsonType, std::unique_ptr<nlohmann::json>> m_json_contents;
		void SaveFile(std::string const filename, Enums::JsonType json_type);
		std::unique_ptr<nlohmann::json> ReadFile(std::string const filename);
		std::unique_ptr<nlohmann::json> ConvertToJsonFormat(std::shared_ptr<Services::SceneEntity> scene);
		std::unique_ptr<nlohmann::json> ConvertToJsonFormat(std::shared_ptr<ConfigEntity> map_config);
		std::shared_ptr<Services::SceneEntity> ConvertToScene();
		std::shared_ptr<ConfigEntity> ConvertToConfigEntity();


		std::string GetStringNode(std::unique_ptr<nlohmann::json> json_content, std::string node_name);
		std::string GetStringNode(Enums::JsonType json_type, std::string node_name);
		glm::vec4 GetVec4Node(std::unique_ptr<nlohmann::json> json_content, std::string node_name);
		glm::vec3 GetVec3Node(std::unique_ptr<nlohmann::json> json_content, std::string node_name);
		std::vector<std::string> GetStringVectorNode(Enums::JsonType json_type, std::string node_name);
		float GetFloatNode(Enums::JsonType json_type, std::string node_name);
		int GetIntNode(Enums::JsonType json_type, std::string node_name);
		int GetIntNode(std::unique_ptr<nlohmann::json> json_content, std::string node_name);
		bool GetBoolNode(Enums::JsonType json_type, std::string node_name);
		bool GetBoolNode(std::unique_ptr<nlohmann::json> json_content, std::string node_name);
		float GetFloatNode(std::unique_ptr<nlohmann::json> json_content, std::string node_name);

		bool m_file_exist;
		
	};
}

#endif