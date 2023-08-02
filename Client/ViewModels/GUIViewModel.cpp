/******************************************************************************************************************************************/
// File : GUIViewModel.cpp
// Purpose : Implementing the GUI view model
/******************************************************************************************************************************************/

#include "GUIViewModel.hpp"

namespace ViewModels
{
	void GuiViewModel::Add(std::shared_ptr<IGuiComponent> component)
	{
		component->SetParent(this);
		this->m_gui_components.push_back(component);
	}
	void GuiViewModel::Remove(std::shared_ptr<IGuiComponent> component)
	{
		component->SetParent(nullptr);
		m_gui_components.remove(component);
	}
	bool GuiViewModel::IsComposite() const
	{
		return true;
	}
	void GuiViewModel::Render(bool show)
	{
		for (std::list<std::shared_ptr<Views::IGuiComponent>>::iterator it = m_gui_components.begin(); it != m_gui_components.end(); it++)
		{
			if (show)
			{
				it->get()->Render();
			}
		}
	}
}

