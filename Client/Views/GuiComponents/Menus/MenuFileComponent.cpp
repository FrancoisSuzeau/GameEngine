/******************************************************************************************************************************************/
// File : MenuFileComponent.cpp
// Purpose : Implementing the GUI view app style editor
/******************************************************************************************************************************************/

#include "MenuFileComponent.hpp"

namespace Views
{
	MenuFileComponent::MenuFileComponent() : show_save_as(false), filename("")
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
		if (ImGui::BeginMenu("File") && m_parent_view_model && m_state_service )
		{
			std::vector<std::string> created_scene = m_state_service->getConfigs()->GetCreatedScenes();
			if (ImGui::MenuItem("New", "Ctrl+Shift+N", false, m_state_service->getFileName() != ""))
			{
			}
			if (ImGui::BeginMenu("Open", m_state_service->getContinued() && !created_scene.empty()) )
			{
				for (auto& it : created_scene)
				{
					if (ImGui::MenuItem(it.c_str()))
					{
						m_parent_view_model->OnCommand(new Commands::LoadSceneCommand(it));
					}
				}
				ImGui::EndMenu();
			}

			if (ImGui::MenuItem("Save scene", "Ctrl+S", false, m_state_service->getContinued()))
			{
				m_parent_view_model->OnCommand(new Commands::SaveSceneCommand());
			}

			ImGui::MenuItem("Save scene As..", "Ctrl+Shift+S", &show_save_as, m_state_service->getContinued());
			

			ImGui::Separator();

			if (ImGui::MenuItem("Quit", "Alt+F4"))
			{
				if (m_state_service->getContinued())
				{
					m_parent_view_model->OnCommand(new Commands::SaveConfigCommand());
				}
				m_parent_view_model->OnCommand(new Commands::ExitCommand(std::bind(&Services::StateService::setExit, m_state_service, true)));
			}
			ImGui::EndMenu();
		}
		
		this->ShowSaveAsWindow(400, 200);
		
	}

	void MenuFileComponent::ShowSaveAsWindow(int w_width, int w_height)
	{
		m_state_service->setGuiOpen(show_save_as);
		if (show_save_as && m_parent_view_model)
		{
			ImGui::SetNextWindowPos(ImVec2((float)((m_state_service->getWidth() / 2) - (w_width / 2)), (float)((m_state_service->getHeight() / 2) - (w_height / 2))));
			ImGui::SetNextWindowSize(ImVec2((float)w_width, (float)w_height));
			
			if (ImGui::Begin("Scene name :", &show_save_as))
			{
				
				ImGui::InputText("Enter name here ...", filename, IM_ARRAYSIZE(filename));
				ImGuiStyle& style = ImGui::GetStyle();
				float frame_rounding_save = style.FrameRounding;
				style.FrameRounding = 20.f;
				ImGui::SetCursorPosY(w_height - 45.f);
				if (ImGui::Button("Save", ImVec2((float)(w_width - 15), 30.f)) && m_state_service)
				{
					
					m_parent_view_model->OnCommand(new Commands::SaveSceneCommand(filename));
					m_parent_view_model->OnCommand(new Commands::ModifyConfigsCommand(filename, Enums::ConfigsModifier::ADDFILE));
					show_save_as = false;
					filename[0] = '\0';
				}
				style.FrameRounding = frame_rounding_save;
				ImGui::End();
			}

		}
	}
}