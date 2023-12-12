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

	class IViewModel
	{
	public:
		virtual ~IViewModel() { }

		virtual void Construct() = 0;

		virtual void RenderComponents(Enums::ComponentType view_type) {};
		virtual void RenderComponents(GLenum const mode, float const line_width) {};
		virtual void ManageComponents() {};
		virtual void RenderFrameBuffer(unsigned int fb_texture_id) {};
		virtual void RenderSkybox(unsigned int skybox_texture_id) {};
		virtual void RenderGrid() {};
		virtual void AddCommand(Commands::ICommand* command)
		{
			if (command)
			{
				m_commands.push_back(std::unique_ptr<Commands::ICommand>(command));
			}
		}
		virtual void OnCommand() 
		{
			for (std::vector<std::unique_ptr<Commands::ICommand>>::iterator it = m_commands.begin(); it != m_commands.end(); it++)
			{
				if (it[0])
				{
					it[0]->Execute();
					it[0].reset();
					it[0] = nullptr;
				}
			}

			m_commands.clear();
		};

	protected:
		std::vector<std::unique_ptr<Commands::ICommand>> m_commands;

	};

}
#endif