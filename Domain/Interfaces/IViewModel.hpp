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

namespace ViewModels {

	class IViewModel
	{
	public:
		virtual ~IViewModel() {}

		virtual void Construct() = 0;

		virtual void DeConstruct() = 0;

		virtual void RenderViews(std::string const type_view) = 0;
		virtual void RenderFrameBuffer(unsigned int fb_texture_id) {};
		virtual void RenderSkybox(unsigned int skybox_texture_id) {};
		virtual void OnCommand(Commands::ICommand *command) = 0;

	protected:
		std::unique_ptr<Commands::ICommand> m_command;

	};

}
#endif