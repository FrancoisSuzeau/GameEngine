/******************************************************************************************************************************************/
// File : IViewModel.hpp
// Purpose : the view model interface
/******************************************************************************************************************************************/
#ifndef IVIEWMODEL_H
#define IVIEWMODEL_H

#include <iostream>
#include <functional>
#include <list>
#include "ICommand.hpp"
#include "IRenderer.hpp"
#include "../Entities/ConfigEntity.hpp"

namespace Enums {
	enum ComponentType { SIMPLE, MENUS, CANVAS };
}

namespace ViewModels {

	class IViewModel : public std::enable_shared_from_this < IViewModel>
	{
	public:
		virtual ~IViewModel() { }

		virtual void Construct() = 0;

		virtual void RenderComponents(Enums::ComponentType view_type) {}
		virtual void RenderComponents() {}
		virtual void RenderLoadComponent(int index) {}
		virtual void ManageScene() {}
		virtual void LoadModel(const int index) {}
		virtual void RenderSceneElements(Enums::RendererType element) {}
		virtual void AddCommand(std::unique_ptr<Commands::ICommand> command)
		{
			if (command)
			{
				m_commands.push_back(std::move(command));
			}
		}
		virtual void OnCommand() 
		{
			for (std::vector<std::unique_ptr<Commands::ICommand>>::iterator it = m_commands.begin(); it != m_commands.end(); it++)
			{
				if (it[0])
				{
					it[0]->Execute();
				}
			}

			this->DeleteCommmands();
			
		};

		virtual void DeleteCommmands()
		{
			for (std::vector<std::unique_ptr<Commands::ICommand>>::iterator it = m_commands.begin(); it != m_commands.end(); it++)
			{
				if (it[0])
				{
					it[0].reset();
					it[0] = nullptr;
				}
			}

			if (!m_commands.empty())
			{
				m_commands.clear();
			}
		}

	protected:
		std::vector<std::unique_ptr<Commands::ICommand>> m_commands;

	};

}
#endif