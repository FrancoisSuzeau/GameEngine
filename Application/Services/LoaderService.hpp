/******************************************************************************************************************************************/
// File : LoaderService.hpp
// Purpose : A service for communicate between loader and shader
/******************************************************************************************************************************************/
#ifndef LOADERSERVICE_H
#define LOADERSERVICE_H

#include "IService.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"

#include "TextureLoaderService/TextureLoaderService.hpp"
#include "JsonLoaderService/JsonLoaderService.hpp"
#include "ShaderLoaderService/ShaderLoaderService.hpp"
#include "ModelLoaderService/ModelLoaderService.hpp"

#include "StateService.hpp"
#include "ConfigEntity.hpp"
#include "SceneEntity.hpp"

#include <iostream>
#include <map>
#include <memory>


namespace Services {

	class LoaderService : public IService
	{

	public:
		void Init() override;
		void DeInit() override;
		void SaveScene(std::shared_ptr<Services::SceneEntity> scene, std::string const filename);
		void SaveConfigs(std::shared_ptr<ConfigEntity> configs);
		void LoadAvailableSkyboxChoices(int const index);
		void LoadAvailableSkyboxCubeTexture(int const index);
		void LoadAvailableTextures(int const index);
		void LoadSceneComponentsTextures();
		void LoadTexture(std::shared_ptr<Component::TexturedComponent> component, std::string texture_name);
		void LoadSqueamishTexture();
		std::shared_ptr<Services::SceneEntity> LoadScene(std::string const filename);
		std::shared_ptr<ConfigEntity> LoadConfigs();
		std::unique_ptr<Renderers::Model> LoadModel(std::string const name);
		GLuint LoadShader(std::string shader_name, Enums::ShaderType shader_type);

	private:
		std::shared_ptr<JsonLoaderService> m_json_loader_service;
		std::shared_ptr<TextureLoaderService> m_texture_loader_service;
		std::shared_ptr<ShaderLoaderService> m_shader_loader;
		std::shared_ptr<StateService> m_state_service;
		std::shared_ptr<ModelLoaderService> m_model_loader_service;
	};
}

#endif