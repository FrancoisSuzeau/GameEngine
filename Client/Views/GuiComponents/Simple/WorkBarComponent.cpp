/******************************************************************************************************************************************/
// File : WorkBarComponent.cpp
// Purpose : Implementing the GUI view tools
/******************************************************************************************************************************************/

#include "WorkBarComponent.hpp"

namespace Views
{
	WorkBarComponent::~WorkBarComponent()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}
	}
	WorkBarComponent::WorkBarComponent() : show_color_picker(false), item_current(-1)
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
		else
		{
			w_width = 400;
		}
	}
	void WorkBarComponent::Render()
	{
		if (m_state_service && m_state_service->getContinued())
		{
			w_height = m_state_service->getHeight();
			ImGui::SetNextWindowPos(ImVec2((float)((m_state_service->getWidth()) - w_width), 0));
			ImGui::SetNextWindowSize(ImVec2((float)w_width, (float)w_height));
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar
				| ImGuiWindowFlags_NoScrollbar
				| ImGuiWindowFlags_NoResize
				| ImGuiWindowFlags_NoFocusOnAppearing
				| ImGuiWindowFlags_NoBringToFrontOnFocus;
			ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
			ImGuiWindowFlags window_flags2 = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollbar;

			if (ImGui::Begin("WorkBar", nullptr, window_flags))
			{
				this->RenderGeneralFunctionnalities(window_flags2);
				this->RenderCustomizeSelectedCpSection(tab_bar_flags, window_flags2);

				ImGui::End();
			}	
		}
	}
	void WorkBarComponent::RenderGeneralFunctionnalities(ImGuiWindowFlags window_flags2)
	{
		bool show_confirm = m_state_service->getShowConfirm();

		if (ImGui::BeginChild("ChildGeneralFun", ImVec2(0, 450), true, window_flags2))
		{
			const char* items[] = { "Triangle", "Square" };
			ImGui::Text("Add new :");
			if (ImGui::Combo(" ", &item_current, items, IM_ARRAYSIZE(items)))
			{

				if (m_parent_view_model)
				{
					m_parent_view_model->AddCommand(new Commands::AddNewComponentCommmand());
					m_state_service->setConfirmMessage("You are about to add a new component. Are you sure ?");
					show_confirm = true;
				}
				item_current = -1;
			}
			ImGui::EndChild();
		}

		m_state_service->setShowConfirm(show_confirm);
	}

	void WorkBarComponent::RenderCustomizeSelectedCpSection(ImGuiTabBarFlags tab_bar_flags, ImGuiWindowFlags window_flags2)
	{
		if (m_state_service && m_state_service->getContinued())
		{

			ImGuiStyle& style = ImGui::GetStyle();
			frame_rounding_save = style.FrameRounding;
			ImVec2 window_padding_save = style.WindowPadding;

			style.FrameRounding = 20.f;
			style.WindowPadding.y = 30.f;
			std::shared_ptr<Renderers::IRenderer> selected_renderer = m_state_service->getSelectedRenderer();
			if (selected_renderer)
			{
				style.WindowPadding = window_padding_save;
				if (ImGui::BeginChild("ChildSelectedCpt", ImVec2(0, 450), true, window_flags2))
				{
					if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
					{
						if (ImGui::BeginTabItem("Properties"))
						{
							m_state_service->setPopupHovered(ImGui::IsWindowHovered());
							this->RenderPropertiesTab(selected_renderer);
							ImGui::EndTabItem();
						}
						if (ImGui::BeginTabItem("Appearance"))
						{
							m_state_service->setPopupHovered(ImGui::IsWindowHovered());
							this->RenderAppearanceTab(selected_renderer);
							ImGui::EndTabItem();
						}
						if (ImGui::BeginTabItem("Infos"))
						{
							m_state_service->setPopupHovered(ImGui::IsWindowHovered());
							this->RenderInfosTab(selected_renderer);
							ImGui::EndTabItem();
						}
						ImGui::EndTabBar();
					}

					ImGui::EndChild();
				}

				selected_renderer.reset();
			}

			style.FrameRounding = frame_rounding_save;
			style.WindowPadding = window_padding_save;

		}
	}

	void WorkBarComponent::RenderPropertiesTab(std::shared_ptr<Renderers::IRenderer> selected_renderer)
	{
		if (m_state_service && selected_renderer)
		{
			glm::vec4 color = selected_renderer->GetBackgroundColor();
			glm::vec4 ref_color = m_state_service->getRefColor();
			glm::vec3 size = selected_renderer->GetSize();
			glm::vec3 position = selected_renderer->GetPosition();

			ImGuiColorEditFlags flags = ImGuiColorEditFlags_AlphaPreviewHalf
				| ImGuiColorEditFlags_AlphaBar
				| ImGuiColorEditFlags_PickerHueWheel
				| ImGuiColorEditFlags_NoInputs;
			ImGui::BulletText("Background color : ");
			ImGui::ColorPicker4("New Color##4", (float*)&color, flags, (float*)&ref_color);

			ImGui::BulletText("Position : ");
			ImGui::SliderFloat("X - Axis", &position.x, -5.0f, 5.0f, "%.3f");
			ImGui::SliderFloat("Y - Axis", &position.y, -5.0f, 5.0f, "%.3f");
			ImGui::SliderFloat("Z - Axis", &position.z, -5.0f, 5.0f, "%.3f");

			ImGui::BulletText("Size : ");
			ImGui::SliderFloat("Width", &size.x, 0.0f, 5.0f, "%.3f");
			ImGui::SliderFloat("Height", &size.y, 0.0f, 5.0f, "%.3f");
			ImGui::SliderFloat("Depth", &size.z, 0.0f, 5.0f, "%.3f");

			selected_renderer->SetSize(size);
			selected_renderer->SetBackgroundColor(color);
			selected_renderer->SetPosition(position);
		}
	}

	void WorkBarComponent::RenderAppearanceTab(std::shared_ptr<Renderers::IRenderer> selected_renderer)
	{
	}

	void WorkBarComponent::RenderInfosTab(std::shared_ptr<Renderers::IRenderer> selected_renderer)
	{
	}
	
}