/******************************************************************************************************************************************/
// File : LoaderService.hpp
// Purpose : A service for communicate between loader and shader
/******************************************************************************************************************************************/
#ifndef LOADERSERVICE_H
#define LOADERSERVICE_H

#include "IService.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "ExternalServices.hpp"
#include "StateService.hpp"
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
		void SaveScene(std::vector<std::shared_ptr<Component::IComponent>> const components, std::string const filename);
		void SaveConfigs(std::shared_ptr<ConfigEntity> configs);
		void LoadSkybox();
		void LoadSkyboxS();
		std::vector<std::shared_ptr<Component::IComponent>> LoadScene(std::string const filename);
		std::shared_ptr<ConfigEntity> LoadConfigs();
		GLuint LoadShader(std::string shader_name, Enums::ShaderType shader_type);

	private:
		std::shared_ptr<JsonLoaderService> m_json_loader_service;
		std::shared_ptr<TextureLoaderService> m_texture_loader_service;
		std::shared_ptr<ShaderLoaderService> m_shader_loader;
		std::shared_ptr<StateService> m_state_service;
	};
}

#endif