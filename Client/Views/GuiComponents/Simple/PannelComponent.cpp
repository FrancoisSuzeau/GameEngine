/******************************************************************************************************************************************/
// File : PannelComponent.cpp
// Purpose : Implementing the GUI view tools
/******************************************************************************************************************************************/

#include "PannelComponent.hpp"

namespace Views
{
	PannelComponent::~PannelComponent()
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
	PannelComponent::PannelComponent(std::shared_ptr<ViewModels::IViewModel> parent)
	{
		m_parent_view_model = parent;
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
		w_width = 800;
		w_height = 800;
		item_current = -1;
	}
	void PannelComponent::Render()
	{
		if (m_state_service && m_parent_view_model)
		{
			std::string config_pannel = m_state_service->getConfigPannel();
			bool show = config_pannel != Constants::NONE;
			ImGui::SetNextWindowPos(ImVec2((float)((m_state_service->getWidth() / 2.f) - (w_width / 2.f)), (float)((m_state_service->getHeight() / 2.f) - (w_height / 2.f))));
			ImGui::SetNextWindowSize(ImVec2((float)w_width, (float)w_height));

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar
				| ImGuiWindowFlags_NoResize
				| ImGuiWindowFlags_NoCollapse;

			if (show)
			{
				if (ImGui::Begin(" ", &show, window_flags))
				{
					if (config_pannel == Constants::SCENE_CONFIG_PANNEL)
					{
						this->RenderConfigPannel();
					}

					ImGui::End();
				}
			}

			m_state_service->setConfigPannel(show ? config_pannel : Constants::NONE);
			
		}
	}
	void PannelComponent::RenderConfigPannel()
	{
		if (m_state_service && m_state_service->getConfigs())
		{
			ImGui::Text("Grid rendering : ");
			float f1 = m_state_service->getConfigs()->GetGridScalingTrigger();
			if (ImGui::SliderFloat("Distance before rescaling grid", &f1, 5.f, 25.f, "%.3f"))
			{
				m_parent_view_model->AddCommand(std::make_unique<Commands::ModifyConfigsCommand>(f1, Enums::ConfigsModifier::CHANGETRIGGER));
				m_parent_view_model->OnCommand();
			}

			ImGui::Separator();

			std::vector<int> values = { 2, 6, 10 };
			auto it = std::find(values.begin(), values.end(), m_state_service->getConfigs()->GetGridScalingRatio());
			if (it != values.end())
			{
				item_current = std::distance(values.begin(), it);
			}
			else
			{
				item_current = -1;
			}
			const char* items[] = { Constants::GRID_SPACING_SMALL.c_str(), Constants::GRID_SPACING_MEDIUM.c_str(), Constants::GRID_SPACING_LARGE.c_str()};
			if (ImGui::Combo("Grid scaling ratio", &item_current, items, IM_ARRAYSIZE(items)))
			{
				if (item_current >= 0 && item_current < values.size())
				{
					m_parent_view_model->AddCommand(std::make_unique<Commands::ModifyConfigsCommand>(values.at(item_current), Enums::ConfigsModifier::CHANGERATIO));
					m_parent_view_model->OnCommand();
				}
			}
		}
		
	}
}