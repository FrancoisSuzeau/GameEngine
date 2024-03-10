/******************************************************************************************************************************************/
// File : AddNewComponentCommmand.hpp
// Purpose : A save scene command
/******************************************************************************************************************************************/
#ifndef ADDNEWCPTCOMMAND_H
#define ADDNEWCPTCOMMAND_H

#include "ICommand.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "../Services/Services.hpp"

#include <memory>

namespace Commands {

	class AddNewComponentCommmand : public ICommand
	{
	public:
		AddNewComponentCommmand(Enums::RendererType component_type);
		~AddNewComponentCommmand();
		void Execute() override;
	private:
		std::shared_ptr<Services::StateService> m_state_service;
		std::shared_ptr<Services::CameraService> m_camera_service;
		Enums::RendererType const m_component_type;
		void MakeNewComponent(std::shared_ptr<Renderers::IRenderer> new_component_to_make);
	};
}

#endif