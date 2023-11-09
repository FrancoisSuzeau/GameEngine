/******************************************************************************************************************************************/
// File : IView.hpp
// Purpose : the view interface
/******************************************************************************************************************************************/
#ifndef IVIEW_H
#define IVIEW_H

#include <iostream>
#include <functional>
#include "IViewModel.hpp"
#include "ICommand.hpp"
#include <vector>
#include "../Entities/Renderers/Renderers.hpp"

namespace Views {

	class IView
	{
	public:
		virtual ~IView() { SetParent(nullptr); }
		virtual void Render() {};
		virtual void Render(std::vector<std::shared_ptr<Renderers::IRenderer>> renderers) {};
		virtual void Clean() {};
		virtual void SetParent(ViewModels::IViewModel* parent) 
		{
			m_parent_view_model = std::shared_ptr<ViewModels::IViewModel>(parent);
		};

		virtual void SetSceneViewModel(ViewModels::IViewModel* scene_viewmodel) {};

	protected:
		std::vector<Commands::ICommand*> m_commands;
		std::shared_ptr<ViewModels::IViewModel> m_parent_view_model;
		virtual void SendCommandToParents()
		{
			if (m_parent_view_model)
			{
				for (std::vector<Commands::ICommand*>::iterator it = m_commands.begin(); it != m_commands.end(); it++)
				{
					if (it[0])
					{
						m_parent_view_model->OnCommand(it[0]);
					}
				}
			}
		}

		virtual void ResetCommands()
		{
			for (std::vector<Commands::ICommand*>::iterator it = m_commands.begin(); it != m_commands.end(); it++)
			{
				it[0] = nullptr;
			}
			m_commands.clear();
		}
	};
	
}
#endif