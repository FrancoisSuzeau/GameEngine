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
			//unsigned int texture_id = m_texture_loader_service->BuildSkyboxTexture(m_state_service->getConfigs()->GetSelectedSkybox());
			/*if (texture_id != 0)
			{
				m_state_service->setSelectedSkyboxTextureId(texture_id);
			}*/
		}
	}
	void LoaderService::LoadSkyboxS(int const index)
	{
		if (m_texture_loader_service && m_state_service && m_state_service->getConfigs())
		{
			std::vector < std::string > available_skybox_name = m_state_service->getConfigs()->GetAvailableSkybox();

			unsigned int texture_id = m_texture_loader_service->BuildTexture("resources/skybox/" + available_skybox_name.at(index) + "/back");
			if (texture_id != 0)
			{
				m_state_service->addAvailableSkybox(available_skybox_name.at(index), texture_id);
			}
		}
	}
	void LoaderService::LoadAvailableTextures(int const index)
	{
		if (m_state_service && m_texture_loader_service && m_state_service->getConfigs())
		{
			std::vector<std::string> available_textures = m_state_service->getConfigs()->GetAvailableTextures();
			unsigned int texture_id = m_texture_loader_service->BuildTexture("resources/CptTextures/" + available_textures.at(index));
			if (texture_id != 0)
			{
				m_state_service->addAvailableTextures(available_textures.at(index), texture_id);
			}
		}
	}
	void LoaderService::LoadSceneComponentsTextures()
	{
		if (m_texture_loader_service && m_state_service)
		{
			std::vector < std::shared_ptr<Component::IComponent> > components = m_state_service->getComponents();

			for (std::vector < std::shared_ptr<Component::IComponent> >::iterator it = components.begin(); it != components.end(); it++)
			{
				if (it[0])
				{
					switch (it[0]->GetType())
					{
					case Enums::RendererType::CUBE_TEXTURED:
					case Enums::RendererType::SQUARE_TEXTURED:
					case Enums::RendererType::TRIANGLE_TEXTURED:
					case Enums::RendererType::SPHERE_TEXTURED:
					{
						std::shared_ptr<Component::TexturedComponent> component = std::dynamic_pointer_cast<Component::TexturedComponent> (it[0]);
						this->LoadTexture(component, component->GetTextureName());
					}
						break;
					case Enums::RendererType::TRIANGLE:
					case Enums::RendererType::SQUARE:
					case Enums::RendererType::GRID:
					case Enums::RendererType::CUBE:
					case Enums::RendererType::SPHERE:
					case Enums::RendererType::SKYBOX:
					case Enums::RendererType::SUBBGRID:
					case Enums::RendererType::SUBGRID2:
					case Enums::RendererType::NONE:
					default:
						break;
					}
					
					
				}
			}
		}
	}
	void LoaderService::LoadTexture(std::shared_ptr<Component::TexturedComponent> component, std::string texture_name)
	{
		if (m_texture_loader_service && component && m_state_service)
		{
			unsigned int texture_id = 0;
			std::map<std::string, unsigned int> available_texures = m_state_service->GetAvailableTextures();
			if (!available_texures.contains(texture_name))
			{
				texture_id = m_texture_loader_service->BuildTexture("resources/CptTextures/" + texture_name);
				if (texture_id != 0)
				{
					m_state_service->addAvailableTextures(texture_name, texture_id);
				}
			}
			else
			{
				texture_id = available_texures.at(texture_name);
			}

			component->SetTextureId(texture_id);
		}
	}
	void LoaderService::LoadSqueamishTexture()
	{
		if (m_state_service && m_texture_loader_service)
		{
			unsigned int texture_id = m_texture_loader_service->BuildTexture("resources/unicorn");
			if (texture_id != 0)
			{
				m_state_service->SetSqueamishTextureId(texture_id);
				m_state_service->addAvailableTextures("unicorn", texture_id);
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

