/******************************************************************************************************************************************/
// File : GUIViewModel.hpp
// Purpose : The GUI view model of the application
/******************************************************************************************************************************************/
#ifndef GUIVIEWMODEL_H
#define GUIVIEWMODEL_H

#include "IGuiComponent.hpp"

#include <iostream>
#include <list>

namespace ViewModels
{
	class GuiViewModel : public Views::IGuiComponent
	{
	private:
		std::list<std::shared_ptr<Views::IGuiComponent>> m_gui_components;

	public:
		void Add(std::shared_ptr<IGuiComponent> component) override;
		void Remove(std::shared_ptr<IGuiComponent> component) override;
		bool IsComposite() const override;
		void Render(bool show = true) override;
	};
}

#endif