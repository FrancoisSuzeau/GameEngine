/******************************************************************************************************************************************/
// File : GUIEngine.cpp
// Purpose : Implementing the GUI engine
/******************************************************************************************************************************************/
#include "GUIEngine.hpp"

namespace Engines
{
	GUIEngine::~GUIEngine()
	{
	}

	void GUIEngine::Construct()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			std::shared_ptr<Services::ImGUIServiceInitializer> imgui_service_init = container->GetReference<Services::ImGUIServiceInitializer>();
			if (imgui_service_init)
			{
				m_io = imgui_service_init->GetIO();
				imgui_service_init.reset();
			}
			else
			{
				SQ_APP_ERROR("Class {} in function {} : ImGUI service initializer is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_state_service = container->GetReference<Services::StateService>();
			m_loader_service = container->GetReference<Services::LoaderService>();
			if(!m_state_service)
			{
				SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}
			if (!m_loader_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Loader service is not referenced yet", __FILE__, __FUNCTION__);
			}

		}
	}

	void GUIEngine::InitFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void GUIEngine::EndFrame()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void GUIEngine::RenderGuiComponents(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		if (view_model_builder)
		{
			std::shared_ptr<ViewModels::IViewModel> view_model = view_model_builder->GetViewModel(Constants::GUIVIEWMODEL);

			if (view_model)
			{
				view_model->RenderComponents(Enums::ComponentType::SIMPLE);
			}
		}

	}

	void GUIEngine::RenderMainMenuBar(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (view_model_builder)
			{
				std::shared_ptr<ViewModels::IViewModel> view_model = view_model_builder->GetViewModel(Constants::GUIVIEWMODEL);

				if (view_model)
				{
					view_model->RenderComponents(Enums::ComponentType::MENUS);
				}
			}

			ImGui::EndMainMenuBar();
		}
	}

	void GUIEngine::RenderLoader(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder, int const index)
	{
		if (view_model_builder)
		{
			std::shared_ptr<ViewModels::IViewModel> view_model = view_model_builder->GetViewModel(Constants::GUIVIEWMODEL);

			if (view_model)
			{
				view_model->RenderLoadComponent(index);
			}
		}
	}

	void GUIEngine::LoadAvailableSkyboxChoices(int const index) const
	{
		if (m_state_service && m_loader_service)
		{
			m_loader_service->LoadAvailableSkyboxChoices(index);
		}
	}

	void GUIEngine::LoadSkyboxCube(int const index) const
	{
		if (m_state_service && m_loader_service)
		{
			m_loader_service->LoadAvailableSkyboxCubeTexture(index);
		}
	}

	void GUIEngine::LoadAvailableTextures(int const index) const
	{
		if (m_state_service && m_loader_service)
		{
			m_loader_service->LoadAvailableTextures(index);
		}
	}
	void GUIEngine::LoadConfigs()
	{
		if (m_state_service && m_loader_service)
		{
			m_state_service->setConfigs(m_loader_service->LoadConfigs());
			m_loader_service->LoadSqueamishTexture();
		}
	}
}



