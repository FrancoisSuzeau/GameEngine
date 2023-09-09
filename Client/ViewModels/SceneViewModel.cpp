/******************************************************************************************************************************************/
// File : SceneViewModel.cpp
// Purpose : Implementing the GUI view model
/******************************************************************************************************************************************/

#include "SceneViewModel.hpp"

namespace ViewModels
{
	void SceneViewModel::Construct()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			std::shared_ptr<Views::Canvas> component_1 = container->make<Views::Canvas>();

			if (component_1)
			{
				component_1->SetParent(this);
				m_views_map.insert_or_assign(Constants::CANVAS, component_1);
			}
			
		}
		
	}

	void SceneViewModel::DeConstruct()
	{
		m_views_map.clear();
	}
	void SceneViewModel::RenderViews(std::string const type_view)
	{
		if (m_views_map.at(type_view))
		{
			m_views_map.at(type_view)->Render();
		}
	}
	void SceneViewModel::OnCommand(Commands::ICommand* command)
	{
		if (command)
		{
			m_command = std::unique_ptr<Commands::ICommand>(command);
			if (m_command)
			{
				m_command->Execute();
				m_command.reset();
			}
		}
	}
}

