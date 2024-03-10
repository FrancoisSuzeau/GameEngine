/******************************************************************************************************************************************/
// File : MenuFileComponent.cpp
// Purpose : Implementing the GUI view app style editor
/******************************************************************************************************************************************/

#include "MenuFileComponent.hpp"

namespace Views
{
	MenuFileComponent::MenuFileComponent()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_state_service = container->GetReference<Services::StateService>();
			if (!m_state_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
	}
	MenuFileComponent::~MenuFileComponent()
	{
		this->SetParent(nullptr);
		if (m_state_service)
		{
			m_state_service.reset();
		}
	}

	void MenuFileComponent::Render()
	{
		if (m_parent_view_model && m_state_service)
		{
			bool show_save_as = m_state_service->getShowSaveAs();
			bool show_confirm = m_state_service->getShowConfirm();
			if (ImGui::BeginMenu("File", !m_state_service->getGuiOpen()))
			{
				if (ImGui::MenuItem("New", "Ctrl+Shift+N", &show_confirm, m_state_service->getContinued() && m_state_service->getFileName() != ""))
				{
					m_parent_view_model->AddCommand(std::make_unique<Commands::LoadSceneCommand>(""));
					m_state_service->setConfirmMessage("You are about to create a new scene. Are you sure ?");
				}

				std::vector<std::string> created_scene = m_state_service->getConfigs()->GetCreatedScenes();
				if (ImGui::BeginMenu("Open", m_state_service->getContinued() && !created_scene.empty()))
				{
					for (auto& it : created_scene)
					{
						if (ImGui::MenuItem(it.c_str(), NULL, &show_confirm))
						{
							m_parent_view_model->AddCommand(std::make_unique<Commands::LoadSceneCommand>(it));
							m_state_service->setConfirmMessage("Are you sure you want to open " + it + " ?");
						}
					}
					ImGui::EndMenu();
				}

				if (ImGui::MenuItem("Save scene", "Ctrl+S", &show_confirm, m_state_service->getContinued() && m_state_service->getFileName() != ""))
				{
					m_parent_view_model->AddCommand(std::make_unique<Commands::SaveSceneCommand>());
					m_state_service->setConfirmMessage("Are you sure you want to save this scene ?");
				}


				if (ImGui::MenuItem("Save scene As..", "Ctrl+Shift+S", &show_save_as, m_state_service->getContinued()))
				{
					m_state_service->setConfirmMessage("Save this scene as ...");
				}

				ImGui::Separator();

				if (ImGui::MenuItem("Quit", "Alt+F4", &show_confirm))
				{
					if (m_state_service->getContinued())
					{
						m_parent_view_model->AddCommand(std::make_unique<Commands::SaveConfigCommand>());
					}
					m_state_service->setConfirmMessage("Are you sure you want to leave ?");
					m_parent_view_model->AddCommand(std::make_unique<Commands::ExitCommand>(std::bind(&Services::StateService::setExit, m_state_service, true)));
				}
				ImGui::EndMenu();
			}
			m_state_service->setShowSaveAs(show_save_as);
			m_state_service->setShowConfirm(show_confirm);
		}

	}
	
	
}