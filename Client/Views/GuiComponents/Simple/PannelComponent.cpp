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
	PannelComponent::PannelComponent(std::shared_ptr<ViewModels::IViewModel> parent) : item_current(-1), render_grid(true), trigger(5.f), previous_item_current(0), activate_bloom(false), bloom_strength(0),
		activate_debug(false), active_skybox(false), selected_skybox(""), show(false)
	{
		m_parent_view_model = parent;
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
		if (m_state_service && m_state_service->getConfigs())
		{
			render_grid = m_state_service->getConfigs()->GetRenderGrid();
			activate_bloom = m_state_service->getConfigs()->GetBloom();
			bloom_strength = m_state_service->getConfigs()->GetBloomStrength();
			activate_debug = m_state_service->getConfigs()->GetRenderDebug();
			active_skybox = m_state_service->getConfigs()->GetRenderSkybox();
			selected_skybox = m_state_service->getConfigs()->GetSelectedSkybox();
			activate_shadow = m_state_service->getConfigs()->GetDepth();
			std::vector<int> values = { 4, 8, 12 };
			auto it = std::find(values.begin(), values.end(), m_state_service->getConfigs()->GetGridSpacingRatio());
			if (it != values.end())
			{
				item_current = (int)std::distance(values.begin(), it);
			}
			trigger = m_state_service->getConfigs()->GetGridScalingTrigger();
		}
		w_width = 800;
		w_height = 800;
		previous_item_current = item_current;
	}
	void PannelComponent::Render()
	{
		if (m_state_service && m_parent_view_model)
		{
			std::string config_pannel = m_state_service->getConfigPannel();
			show = config_pannel != Constants::NONE;
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
						this->RenderGridPannelModifier();
						ImGui::Separator();
						this->RenderBloomPannelModifier();
						ImGui::Separator();
						this->RenderSkyboxPannelModifier();
						ImGui::Separator();
						this->RenderShadowPannelModifier();
					}

					if (config_pannel == Constants::DEBUG_CONFIG_PANNEL)
					{
						this->RenderDebugModifier();
					}

					this->RenderButtons();
					ImGui::End();
				}
			}
			else
			{
				this->OnClose();

			}

			m_state_service->setConfigPannel(show ? config_pannel : Constants::NONE);
			
		}
	}
	void PannelComponent::RenderGridPannelModifier()
	{
		if (m_state_service && m_state_service->getConfigs())
		{
			ImGui::Text("Grid rendering : ");
			if (ImGui::SliderFloat("Distance before rescaling grid", &trigger, 5, 25, "%.3f"))
			{
				m_parent_view_model->AddCommand(std::make_unique<Commands::ModifyConfigsCommand>(trigger, Enums::ConfigsModifier::CHANGETRIGGER));
				m_state_service->setActualize(true);
			}

			std::vector<int> values = { 4, 8, 12 };
			const char* items[] = { Constants::GRID_SPACING_SMALL.c_str(), Constants::GRID_SPACING_MEDIUM.c_str(), Constants::GRID_SPACING_LARGE.c_str()};
			if (ImGui::Combo("Grid scaling ratio", &item_current, items, IM_ARRAYSIZE(items)))
			{
				if (item_current >= 0 && item_current < values.size())
				{
					m_parent_view_model->AddCommand(std::make_unique<Commands::ModifyConfigsCommand>(values.at(item_current), Enums::ConfigsModifier::CHANGERATIO));
					m_state_service->setActualize(true);
				}
			}

			if (ImGui::Checkbox("Render Grid", &render_grid))
			{
				m_state_service->setActualize(true);
				m_parent_view_model->AddCommand(std::make_unique<Commands::ModifyConfigsCommand>(render_grid, Enums::ConfigsModifier::RENDERGRID));

			}
		}
		
	}
	void PannelComponent::RenderBloomPannelModifier()
	{
		if (m_state_service && m_state_service->getConfigs())
		{
			ImGui::Text("Effects rendering : ");
			if (ImGui::Checkbox("Activate bloom effect", &activate_bloom))
			{
				m_state_service->setActualize(true);
				m_parent_view_model->AddCommand(std::make_unique<Commands::ModifyConfigsCommand>(activate_bloom, Enums::ConfigsModifier::BLOOM));

			}

			if (ImGui::SliderInt("Bloom strength", &bloom_strength, 0, 10, "%.3f"))
			{
				m_parent_view_model->AddCommand(std::make_unique<Commands::ModifyConfigsCommand>(bloom_strength, Enums::ConfigsModifier::BLOOMSTRENGTH));
				if (bloom_strength == 0)
				{
					m_parent_view_model->AddCommand(std::make_unique<Commands::ModifyConfigsCommand>(false, Enums::ConfigsModifier::BLOOM));
					activate_bloom = false;
				}
				m_state_service->setActualize(true);
			}
		}
	}
	void PannelComponent::RenderShadowPannelModifier()
	{
		if (m_state_service && m_state_service->getConfigs())
		{
			ImGui::Text("Render Shadow : ");
			if (ImGui::Checkbox("Activate shadow effect", &activate_shadow))
			{
				m_state_service->setActualize(true);
				m_parent_view_model->AddCommand(std::make_unique<Commands::ModifyConfigsCommand>(activate_shadow, Enums::ConfigsModifier::SHADOW));

			}
		}
	}
	void PannelComponent::RenderSkyboxPannelModifier()
	{
		if (m_state_service && m_state_service->getConfigs())
		{
			ImGui::Text("Skybox rendering : ");
			if (ImGui::Checkbox("Activate skybox", &active_skybox))
			{
				m_state_service->setActualize(true);
				m_parent_view_model->AddCommand(std::make_unique<Commands::ModifyConfigsCommand>(active_skybox, Enums::ConfigsModifier::RENDERSKYBOX));
			}

			std::map<std::string, unsigned int> available_skybox = m_state_service->getAvailableSkybox();
			
			for (std::map<std::string, unsigned int>::iterator it = available_skybox.begin(); it != available_skybox.end(); it++)
			{
				if (it->first == selected_skybox)
				{
					ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
					ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
					ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
					ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 1.f); // 50% opaque white
					ImGui::Image((ImTextureID)(intptr_t)it->second, ImVec2(100, 100), uv_max, uv_min, tint_col, border_col);
				}
				else
				{
					ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
					ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
					ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);     // Black background
					ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
					if (ImGui::ImageButton((ImTextureID)(intptr_t)it->second, ImVec2(100, 100), uv_max, uv_min, 2, bg_col, tint_col))
					{
						selected_skybox = it->first;
						m_state_service->setActualize(true);
						m_parent_view_model->AddCommand(std::make_unique<Commands::ModifyConfigsCommand>(selected_skybox, Enums::ConfigsModifier::CHANGESKYBOX));
					}
				}
				ImGui::SameLine(120);
				
			}
			ImGui::Text(" ");
			for (std::map<std::string, unsigned int>::iterator it = available_skybox.begin(); it != available_skybox.end(); it++)
			{
				ImGui::Text(it->first.c_str());
				ImGui::SameLine(120);
			}
			ImGui::Text(" ");
		}
	}
	void PannelComponent::RenderDebugModifier()
	{
		if (m_state_service && m_state_service->getConfigs())
		{
			ImGui::Text("Back buffer debug : ");
			if (ImGui::Checkbox("Activate debug", &activate_debug))
			{
				m_state_service->setActualize(true);
				m_parent_view_model->AddCommand(std::make_unique<Commands::ModifyConfigsCommand>(activate_debug, Enums::ConfigsModifier::RENDERDEBUG));

			}
		}
	}
	void PannelComponent::RenderButtons()
	{
		ImGui::Separator();

		ImGuiStyle& style = ImGui::GetStyle();
		frame_rounding_save = style.FrameRounding;
		style.FrameRounding = 20.f;
		ImGui::SetCursorPosY(w_height - 45.f);
		if (m_state_service->getActualize())
		{

			if (ImGui::Button("Actualize", ImVec2((float)(w_width / 2.f) - 15.f, 30.f)))
			{
				if (item_current > previous_item_current)
				{
					m_state_service->setScalingWay(Enums::ScallingWay::Up);
					previous_item_current = item_current;
				}
				if (item_current < previous_item_current)
				{
					m_state_service->setScalingWay(Enums::ScallingWay::Bottom);
					previous_item_current = item_current;
				}
				m_parent_view_model->AddCommand(std::make_unique<Commands::ActualizeCommand>());
				m_parent_view_model->AddCommand(std::make_unique<Commands::SaveConfigCommand>());
				m_parent_view_model->OnCommand();
				m_state_service->setActualize(false);
			}
			ImGui::SameLine();
		}
		ImGui::SetCursorPosY(w_height - 45.f);

		if (ImGui::Button("Reset to default", ImVec2((float)(w_width / 2.f) - 15.f, 30.f)))
		{

		}
		style.FrameRounding = frame_rounding_save;
	}
	void PannelComponent::OnClose()
	{
		if (!show && m_state_service && m_state_service->getActualize() && m_parent_view_model)
		{
			m_parent_view_model->DeleteCommmands();
			m_state_service->setActualize(false);
			render_grid = m_state_service->getConfigs()->GetRenderGrid();
			activate_bloom = m_state_service->getConfigs()->GetBloom();
			bloom_strength = m_state_service->getConfigs()->GetBloomStrength();
			activate_debug = m_state_service->getConfigs()->GetRenderDebug();
			active_skybox = m_state_service->getConfigs()->GetRenderSkybox();
			selected_skybox = m_state_service->getConfigs()->GetSelectedSkybox();
			activate_shadow = m_state_service->getConfigs()->GetDepth();
			std::vector<int> values = { 4, 8, 12 };
			auto it = std::find(values.begin(), values.end(), m_state_service->getConfigs()->GetGridSpacingRatio());
			if (it != values.end())
			{
				item_current = (int)std::distance(values.begin(), it);
			}
			trigger = m_state_service->getConfigs()->GetGridScalingTrigger();
			previous_item_current = item_current;
		}
	}
}