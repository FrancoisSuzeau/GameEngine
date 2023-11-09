/******************************************************************************************************************************************/
// File : MenuFileComponent.cpp
// Purpose : Implementing the GUI view app style editor
/******************************************************************************************************************************************/

#include "MenuFileComponent.hpp"

namespace Views
{
	MenuFileComponent::MenuFileComponent() : filename(""), m_confirm_message(" "), show_confirm(false), show_save_as(false)
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

		this->ResetCommands();
	}

	void MenuFileComponent::Render()
	{
		if (m_parent_view_model && m_state_service)
		{
			show_save_as = m_state_service->getShowSaveAs();
			show_confirm = m_state_service->getShowConfirm();
			if (ImGui::BeginMenu("File", !m_state_service->getGuiOpen()))
			{
				if (ImGui::MenuItem("New", "Ctrl+Shift+N", &show_confirm, m_state_service->getContinued() && m_state_service->getFileName() != ""))
				{
					m_commands.push_back(new Commands::LoadSceneCommand(""));
					m_confirm_message = "You are about to create a new scene. Are you sure ?";
				}

				std::vector<std::string> created_scene = m_state_service->getConfigs()->GetCreatedScenes();
				if (ImGui::BeginMenu("Open", m_state_service->getContinued() && !created_scene.empty()))
				{
					for (auto& it : created_scene)
					{
						if (ImGui::MenuItem(it.c_str(), NULL, &show_confirm))
						{
							m_commands.push_back(new Commands::LoadSceneCommand(it));
							m_confirm_message = "Are you sure you want to open " + it + " ?";
						}
					}
					ImGui::EndMenu();
				}

				if (ImGui::MenuItem("Save scene", "Ctrl+S", &show_confirm, m_state_service->getContinued() && m_state_service->getFileName() != ""))
				{
					m_commands.push_back(new Commands::SaveSceneCommand());
					m_confirm_message = "Are you sure you want to save this scene ?";
				}


				if (ImGui::MenuItem("Save scene As..", "Ctrl+Shift+S", &show_save_as, m_state_service->getContinued()))
				{
					m_confirm_message = "Save this scene as ...";
				}

				ImGui::Separator();

				if (ImGui::MenuItem("Quit", "Alt+F4", &show_confirm))
				{
					if (m_state_service->getContinued())
					{
						m_commands.push_back(new Commands::SaveConfigCommand());
					}
					m_confirm_message = "Are you sure you want to leave ?";
					m_commands.push_back(new Commands::ExitCommand(std::bind(&Services::StateService::setExit, m_state_service, true)));
				}
				ImGui::EndMenu();
			}

			this->ShowSaveAsWindow(400, 120);
			this->ShowConfirm(400, 120);
		}

	}

	void MenuFileComponent::ShowSaveAsWindow(int w_width, int w_height)
	{
		if (show_save_as)
		{
			ImGui::SetNextWindowPos(ImVec2((float)((m_state_service->getWidth() / 2) - (w_width / 2)), (float)((m_state_service->getHeight() / 2) - (w_height / 2))));
			ImGui::SetNextWindowSize(ImVec2((float)w_width, (float)w_height));


			if (ImGui::Begin(" ", &show_save_as))
			{
				ImGui::Text(m_confirm_message.c_str());
				ImGui::InputText("Enter name here ...", filename, IM_ARRAYSIZE(filename));
				ImGuiStyle& style = ImGui::GetStyle();
				float frame_rounding_save = style.FrameRounding;
				style.FrameRounding = 20.f;
				ImGui::SetCursorPosY(w_height - 45.f);
				if (filename[0] != '\0')
				{
					if (ImGui::Button("Save", ImVec2((float)(w_width - 15.f), 30.f)))
					{

						m_commands.push_back(new Commands::SaveSceneCommand(filename));
						m_commands.push_back(new Commands::ModifyConfigsCommand(filename, Enums::ConfigsModifier::ADDFILE));
						show_save_as = false;
						show_confirm = true;
						m_confirm_message = "Are you sure you want to save this scene as " + std::string(filename);
						filename[0] = '\0';
					}
				}
				style.FrameRounding = frame_rounding_save;

			}
			ImGui::End();
		}
		m_state_service->setShowSaveAs(show_save_as);
	}

	void MenuFileComponent::ShowConfirm(int w_width, int w_height)
	{

		if (show_confirm)
		{
			ImGui::SetNextWindowPos(ImVec2((float)((m_state_service->getWidth() / 2.f) - (w_width / 2.f)), (float)((m_state_service->getHeight() / 2.f) - (w_height / 2.f))));
			ImGui::SetNextWindowSize(ImVec2((float)w_width, (float)w_height));

			if (ImGui::Begin(" ", &show_confirm))
			{
				ImGui::Text(m_confirm_message.c_str());
				ImGuiStyle& style = ImGui::GetStyle();
				float frame_rounding_save = style.FrameRounding;
				style.FrameRounding = 20.f;
				ImGui::SetCursorPosY((float)(w_height - 45.f));
				if (ImGui::Button("Accept", ImVec2((float)(w_width / 2.f - 15.f), 30.f)) && m_state_service)
				{
					this->SendCommandToParents();
					this->ResetCommands();
					show_confirm = false;
				}
				ImGui::SetCursorPos(ImVec2((float)(w_width / 2.f), (float)(w_height - 45.f)));
				if (ImGui::Button("Cancel", ImVec2((float)(w_width / 2.f - 15.f), 30.f)) && m_state_service)
				{
					show_confirm = false;
				}
				style.FrameRounding = frame_rounding_save;
			}
			ImGui::End();
		}
		m_state_service->setShowConfirm(show_confirm);
	}
	
	
}