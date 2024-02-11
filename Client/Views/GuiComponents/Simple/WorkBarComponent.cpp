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
	WorkBarComponent::WorkBarComponent() : show_color_picker(false)
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}
	}
	void WorkBarComponent::Render()
	{

		if (m_state_service)
		{
			int w_width = 400;
			int w_height = 500;
			std::shared_ptr<Renderers::IRenderer> selected_renderer = m_state_service->getSelectedRenderer();
			if (selected_renderer)
			{
				ImGui::SetNextWindowPos(ImVec2((float)((m_state_service->getWidth() / 2) - (w_width / 2)), (float)((m_state_service->getHeight() / 2) - (w_height / 2))));
				ImGui::SetNextWindowSize(ImVec2((float)w_width, (float)w_height));


				if (ImGui::Begin(" "))
				{
					m_state_service->setPopupHovered(ImGui::IsWindowHovered());
					ImGuiStyle& style = ImGui::GetStyle();
					float frame_rounding_save = style.FrameRounding;
					style.FrameRounding = 20.f;

					this->RenderColorPicker(selected_renderer);
					this->RenderSizer(selected_renderer);

					style.FrameRounding = frame_rounding_save;

				}
				ImGui::End();
				selected_renderer.reset();
			}
		}

	}
	void WorkBarComponent::RenderColorPicker(std::shared_ptr<Renderers::IRenderer> selected_renderer)
	{
		if (m_state_service && selected_renderer)
		{

			glm::vec4 color = selected_renderer->GetBackgroundColor();
			glm::vec4 ref_color = m_state_service->getRefColor();
			ImGuiColorEditFlags flags = ImGuiColorEditFlags_AlphaPreviewHalf | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs;
			ImGui::BulletText("Background color : ");
			ImGui::SameLine();
			if (ImGui::ColorButton("MyColor##3c", *(ImVec4*)&ref_color))
			{
				show_color_picker = !show_color_picker;
			}
			if (show_color_picker)
			{
				ImGui::ColorPicker4("MyColor##4", (float*)&color, flags, (float*)&ref_color);
			}
			selected_renderer->SetBackgroundColor(color);
		}
	}
	void WorkBarComponent::RenderSizer(std::shared_ptr<Renderers::IRenderer> selected_renderer)
	{
		if (selected_renderer)
		{
			if (ImGui::TreeNode("Size :"))
			{
				glm::vec3 size = selected_renderer->GetSize();
				ImGui::SliderFloat("Width", &size.x, 0.0f, 5.0f, "x = %.3f");
				ImGui::SliderFloat("Height", &size.y, 0.0f, 5.0f, "y = %.3f");
				ImGui::SliderFloat("Depth", &size.z, 0.0f, 5.0f, "z = %.3f");
				selected_renderer->SetSize(size);
				ImGui::TreePop();
			}
		}
	}
}