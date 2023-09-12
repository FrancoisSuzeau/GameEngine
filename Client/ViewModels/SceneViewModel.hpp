/******************************************************************************************************************************************/
// File : SceneViewModel.hpp
// Purpose : The scene view model of the application
/******************************************************************************************************************************************/
#ifndef SCENEVIEWMODEL_H
#define SCENEVIEWMODEL_H

#include "IViewModel.hpp"
#include "../Views/Views.hpp"
#include "Container/Container.hpp"


#include <iostream>
#include <map>

namespace ViewModels
{
	class SceneViewModel : public IViewModel
	{

	public:
		void Construct() override;
		void DeConstruct() override;
		void RenderViews(std::string const type_view) override;
		void OnCommand(Commands::ICommand* command) override;

	private:
		std::map<std::string, std::shared_ptr<Views::IView>> m_views_map;
		std::vector < std::shared_ptr<Renderers::Triangle> > m_renderers;
	};
}

#endif