/******************************************************************************************************************************************/
// File : GUIViewModel.hpp
// Purpose : The GUI view model of the application
/******************************************************************************************************************************************/
#ifndef GUIVIEWMODEL_H
#define GUIVIEWMODEL_H

#include "IViewModel.hpp"
#include "../Views/Views.hpp"
#include "Container/Container.hpp"
#include "Commands/Commands.hpp"
#include "SceneViewModel.hpp"

#include <iostream>
#include "ConfigEntity.hpp"
#include <list>
#include <map>

namespace ViewModels
{
	class GuiViewModel : public IViewModel
	{

	public:
		~GuiViewModel() override;
		void Construct() override;
		
		void RenderViews(std::string const type_view) override;
		void OnCommand(Commands::ICommand* command) override;
		void RenderStartMenu() override;
		void ChangeConfig(Enums::ConfigModifier modifier, std::string element) override;
		std::shared_ptr<Services::ConfigEntity> GetConfig() override;
 
	private:
		std::map<std::string, std::list<std::shared_ptr<Views::IView>>> m_views_map;
		std::shared_ptr<Services::ConfigEntity> m_config;
		std::shared_ptr<Services::JsonService> m_json_service;
		void AddSceneFile(std::string element);
		std::shared_ptr<Views::StartComponent> m_start_component;
	};
}

#endif