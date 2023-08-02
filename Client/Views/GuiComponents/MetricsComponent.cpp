/******************************************************************************************************************************************/
// File : GUIViewModel.cpp
// Purpose : Implementing the GUI view model
/******************************************************************************************************************************************/

#include "MetricsComponent.hpp"

namespace Views
{

	void MetricsComponent::Render(bool show)
	{
		ImGui::ShowMetricsWindow(&show);
	}
}