/******************************************************************************************************************************************/
// File : JsonService.hpp
// Purpose : A service for communicate between loader and shader
/******************************************************************************************************************************************/
#ifndef JSONSERVICE_H
#define JSONSERVICE_H

#include "IService.hpp"
#include "Services.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "ExternalServices.hpp"

#include <iostream>
#include <map>
#include <memory>


namespace Services {

	class JsonService : public IService
	{

	public:
		void Init() override;
		void DeInit() override;
		void SaveScene();
		void SaveConfigs();
		std::vector<std::shared_ptr<Renderers::IRenderer>> LoadScene();
		std::map<std::string, std::string> LoadConfigs();
		void SetFileName(std::string const new_filename);
		void SetScene(std::vector<std::shared_ptr<Renderers::IRenderer>> const renderers);
		void SetConfig(std::map<std::string, std::string> const map_config);

	private:
		std::shared_ptr<Services::JsonLoaderService> m_json_loader_service;
		std::string filename;
		std::vector<std::shared_ptr<Renderers::IRenderer>> m_renderers;
		std::map<std::string, std::string> m_map_config;
		void CleanRenderers();
	};
}

#endif