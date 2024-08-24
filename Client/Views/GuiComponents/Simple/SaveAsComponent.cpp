/******************************************************************************************************************************************/
// File : SaveAsComponent.cpp
// Purpose : Implementing the GUI view tools
/******************************************************************************************************************************************/

#include "SaveAsComponent.hpp"

namespace Views
{
	SaveAsComponent::~SaveAsComponent()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}

		if (m_parent_view_model)
		{
			m_parent_view_model.reset();
		}
	}
	SaveAsComponent::SaveAsComponent(std::shared_ptr<ViewModels::IViewModel> parent) : filename("")
	{
		m_parent_view_model = parent;
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
		w_width = 400;
		w_height = 120;
	}
	void SaveAsComponent::Render()
	{
		if (m_state_service)
		{
			bool show_save_as = m_state_service->getShowSaveAs();
			bool show_confirm = m_state_service->getShowConfirm();
			
			if (show_save_as)
			{
				ImGui::SetNextWindowPos(ImVec2((float)((m_state_service->getWidth() / 2) - (w_width / 2)), (float)((m_state_service->getHeight() / 2) - (w_height / 2))));
				ImGui::SetNextWindowSize(ImVec2((float)w_width, (float)w_height));


				if (ImGui::Begin(" ", &show_save_as, ImGuiWindowFlags_NoCollapse))
				{
					ImGui::Text(m_state_service->getConfirmMessage().c_str());
					ImGui::InputText("Enter name here ...", filename, IM_ARRAYSIZE(filename));
					ImGuiStyle& style = ImGui::GetStyle();
					frame_rounding_save = style.FrameRounding;
					style.FrameRounding = 20.f;
					ImGui::SetCursorPosY(w_height - 45.f);
					if (filename[0] != '\0')
					{
						if (ImGui::Button("Save", ImVec2((float)(w_width - 15.f), 30.f)))
						{

							m_parent_view_model->AddCommand(std::make_unique<Commands::SaveSceneCommand>(filename));
							m_parent_view_model->AddCommand(std::make_unique<Commands::ModifyConfigsCommand>((std::string)filename, Enums::ConfigsModifier::ADDFILE));
							m_parent_view_model->AddCommand(std::make_unique<Commands::LoadSceneCommand>(filename));
							show_save_as = false;
							show_confirm = true;
							m_state_service->setConfirmMessage("Are you sure you want to save this scene as " + std::string(filename));
							filename[0] = '\0';
						}
					}
					style.FrameRounding = frame_rounding_save;

				}
				ImGui::End();
			}
			m_state_service->setShowSaveAs(show_save_as);
			m_state_service->setShowConfirm(show_confirm);
		}
	}
}