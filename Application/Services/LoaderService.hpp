/******************************************************************************************************************************************/
// File : LoaderService.hpp
// Purpose : A service for communicate between loader and shader
/******************************************************************************************************************************************/
#ifndef LOADERSERVICE_H
#define LOADERSERVICE_H

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

	class LoaderService : public IService
	{

	public:
		void Init() override;
		void DeInit() override;
		void SaveScene(std::vector<std::shared_ptr<Component::IComponent>> const renderers, std::string const filename);
		void SaveConfigs(std::shared_ptr<ConfigEntity> configs);
		unsigned int LoadSkybox(std::string const path);
		std::vector<std::shared_ptr<Component::IComponent>> LoadScene(std::string const filename);
		std::shared_ptr<ConfigEntity> LoadConfigs();

	private:
		std::shared_ptr<JsonLoaderService> m_json_loader_service;
		std::shared_ptr<TextureLoaderService> m_texture_loader_service;
	};
}

#endif