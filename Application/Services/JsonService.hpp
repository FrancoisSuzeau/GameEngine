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
#include "ConfigEntity.hpp"

#include <iostream>
#include <map>
#include <memory>


namespace Services {

	class JsonService : public IService
	{

	public:
		void Init() override;
		void DeInit() override;
		void SaveScene(std::vector<std::shared_ptr<Renderers::IRenderer>> const renderers, std::string const filename);
		void SaveConfigs(std::shared_ptr<ConfigEntity> configs);
		std::vector<std::shared_ptr<Renderers::IRenderer>> LoadScene(std::string const filename);
		std::shared_ptr<ConfigEntity> LoadConfigs();

	private:
		std::shared_ptr<JsonLoaderService> m_json_loader_service;
	};
}

#endif