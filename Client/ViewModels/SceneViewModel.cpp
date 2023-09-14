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
			
			std::shared_ptr<Renderers::Triangle>triangle = std::make_shared<Renderers::Triangle>();
			if (triangle)
			{
				triangle->Construct();
				m_renderers.push_back(triangle);
			}

			std::shared_ptr<Renderers::Square> square = std::make_shared<Renderers::Square>();
			if (square)
			{
				square->Construct();
				m_renderers.push_back(square);
			}
		}	
	}

	void SceneViewModel::DeConstruct()
	{
		for (std::map<std::string, std::shared_ptr<Views::IView>>::iterator it = m_views_map.begin(); it != m_views_map.end(); it++)
		{
			if (it->second)
			{
				it->second->Clean();
				it->second.reset();
			}
		}
		m_views_map.clear();

		for (std::vector<std::shared_ptr<Renderers::IRenderer>>::iterator it = m_renderers.begin(); it != m_renderers.end(); it++)
		{
			if (it[0])
			{
				it[0]->Clean();
				it[0].reset();
			}
		}

		m_renderers.clear();
	}
	void SceneViewModel::RenderViews(std::string const type_view)
	{
		if (m_views_map.at(type_view))
		{
			m_views_map.at(type_view)->Render(m_renderers);
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

