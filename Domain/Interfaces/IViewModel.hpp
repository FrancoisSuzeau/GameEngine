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



namespace ViewModels {

	class IViewModel
	{
	public:
		virtual ~IViewModel() { }

		virtual void Construct() = 0;

		virtual void RenderViews(std::string const type_view) = 0;
		virtual void RenderStartMenu() {};
		virtual void RenderFrameBuffer(unsigned int fb_texture_id) {};
		virtual void RenderSkybox(unsigned int skybox_texture_id) {};
		virtual void RenderGrid() {};
		virtual void OnCommand(Commands::ICommand* command) 
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
		};

	protected:
		std::unique_ptr<Commands::ICommand> m_command;

	};

}
#endif