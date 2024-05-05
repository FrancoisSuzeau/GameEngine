/******************************************************************************************************************************************/
// File : LoaderService.cpp
// Purpose : Implementing service shader
/******************************************************************************************************************************************/
#include "LoaderService.hpp"

namespace Services
{
	void LoaderService::Init()
	{
		IoC::Container::Container *container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_json_loader_service = container->GetReference<Services::JsonLoaderService>();
			if (!m_json_loader_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Json loader service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_texture_loader_service = container->GetReference<Services::TextureLoaderService>();
			if (!m_texture_loader_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Texture loader service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_shader_loader = container->GetReference<Services::ShaderLoaderService>();
			if (!m_shader_loader)
			{
				SQ_APP_ERROR("Class {} in function {} : Shader service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_state_service = container->GetReference<StateService>();
			if (!m_state_service)
			{
				SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
	}

	void LoaderService::DeInit()
	{
		
	}

	void LoaderService::SaveScene(std::vector<std::shared_ptr<Component::IComponent>> const components, std::string const filename)
	{
		if (m_json_loader_service)
		{
			m_json_loader_service->SaveScene(filename, components);
		}
	}
	void LoaderService::SaveConfigs(std::shared_ptr<ConfigEntity> configs)
	{
		if (m_json_loader_service)
		{
			m_json_loader_service->SaveConfigs(configs);
		}
	}
	void LoaderService::LoadSkybox()
	{
		if (m_texture_loader_service && m_state_service && m_state_service->getConfigs())
		{
			unsigned int texture_id = m_texture_loader_service->BuildSkyboxTexture(m_state_service->getConfigs()->GetSelectedSkybox());
			m_state_service->setSelectedSkyboxTextureId(texture_id);
		}
	}
	void LoaderService::LoadSkyboxS()
	{
		if (m_texture_loader_service && m_state_service && m_state_service->getConfigs())
		{
			std::vector < std::string > available_skybox_name = m_state_service->getConfigs()->GetAvailableSkybox();
			for (std::vector<std::string>::iterator it = available_skybox_name.begin(); it != available_skybox_name.end(); it++)
			{
				unsigned int texture_id = m_texture_loader_service->BuildTexture("resources/skybox/" + it[0] + "/back");
				m_state_service->addAvailableSkybox(it[0], texture_id);
			}
		}
	}
	void LoaderService::LoadSceneComponentTextures()
	{
		if (m_texture_loader_service && m_state_service)
		{
			std::vector < std::shared_ptr<Component::IComponent> > components = m_state_service->getComponents();

			for (std::vector < std::shared_ptr<Component::IComponent> >::iterator it = components.begin(); it != components.end(); it++)
			{
				if (it[0])
				{
					unsigned int texture_id = m_texture_loader_service->BuildTexture("resources/" + it[0]->GetTextureName());
					it[0]->SetTextureId(texture_id);
				}
			}
		}
	}
	std::vector<std::shared_ptr<Component::IComponent>> LoaderService::LoadScene(std::string const filename)
	{
		if (m_json_loader_service)
		{
			return m_json_loader_service->GetScene(filename);
		}

		return std::vector<std::shared_ptr<Component::IComponent>>();
	}
	std::shared_ptr<ConfigEntity> LoaderService::LoadConfigs()
	{
		if(m_json_loader_service)
		{
			return m_json_loader_service->GetConfigs();
		}
		return nullptr;
	}

	GLuint LoaderService::LoadShader(std::string shader_name, Enums::ShaderType shader_type)
	{
		if (m_shader_loader)
		{
			return m_shader_loader->loadShader(shader_name, shader_type);
		}

		return 0;
	}
}

