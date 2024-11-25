/******************************************************************************************************************************************/
// File : HWorkBarComponent.cpp
// Purpose : Implementing the GUI view tools
/******************************************************************************************************************************************/

#include "HWorkBarComponent.hpp"

namespace Views
{
	HWorkBarComponent::~HWorkBarComponent()
	{

	}
	HWorkBarComponent::HWorkBarComponent(std::shared_ptr<ViewModels::IViewModel> parent)
	{
		m_parent_view_model = parent;
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_state_service = container->GetReference<Services::StateService>();
			if (!m_state_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}
			else
			{
				w_height = 300;
			}
		}
	}
	void HWorkBarComponent::Render()
	{
		if (m_state_service && m_state_service->getContinued())
		{
			w_width = m_state_service->getWidth();
			ImGui::SetNextWindowPos(ImVec2(0, (float)((m_state_service->getHeight()) - w_height)));
			ImGui::SetNextWindowSize(ImVec2((float)w_width, (float)w_height));
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar
				| ImGuiWindowFlags_NoScrollbar
				| ImGuiWindowFlags_NoResize
				| ImGuiWindowFlags_NoFocusOnAppearing
				| ImGuiWindowFlags_NoBringToFrontOnFocus;

			if (ImGui::Begin("HorizontalWorkBar", nullptr, window_flags))
			{

				ImGui::End();
			}
		}
	}

}