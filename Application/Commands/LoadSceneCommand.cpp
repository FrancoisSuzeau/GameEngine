/******************************************************************************************************************************************/
// File : LoadSceneCommand.cpp
// Purpose : Implementing the load new shader command
/******************************************************************************************************************************************/
#include "LoadSceneCommand.hpp"

namespace Commands
{
	LoadSceneCommand::LoadSceneCommand(std::string const filename)
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_state_service = container->GetReference<Services::StateService>();
			if (!m_state_service)
			{
				SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}
			else
			{
				m_state_service->setFileName(filename);
			}

			m_loader_service = container->GetReference<Services::LoaderService>();
			if (!m_loader_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Json service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_physics_service = container->GetReference<Services::PhysicsService>();
			if (!m_physics_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Physics service is not referenced yet", __FILE__, __FUNCTION__);

			}

			m_shader_service = container->GetReference<Services::ShaderService>();
			if (!m_shader_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Shader service is not referenced yet", __FILE__, __FUNCTION__);

			}
		}
	}

	LoadSceneCommand::~LoadSceneCommand()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}

		if (m_loader_service)
		{
			m_loader_service.reset();
		}
	}

	void LoadSceneCommand::Execute()
	{
		if (m_loader_service && m_state_service && m_physics_service && m_shader_service)
		{
			std::shared_ptr<Services::SceneEntity> scene = m_loader_service->LoadScene(m_state_service->getFileName());
			if (scene)
			{
				m_physics_service->SetTheta(scene->GetDirectionLight());
				m_physics_service->SetPhi(scene->GetDirectionLight());
				m_state_service->SetScene(scene);
				m_loader_service->LoadSceneComponentsTextures();
				m_state_service->SetSelectedSkyboxTextureId();
				m_physics_service->SetLightSourcesGeneralParameters();
				m_physics_service->SetLightsAttenuationsParameters();
				m_shader_service->PassLightsParametersToSSBO(m_physics_service->GetLigthSources());
			}
		}
	}
}


