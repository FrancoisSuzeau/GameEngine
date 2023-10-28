/******************************************************************************************************************************************/
// File : SendToJsonServiceCommand.hpp
// Purpose : A save scene command
/******************************************************************************************************************************************/
#ifndef SENDTOJSONSERVICECOMMAND_H
#define SENDTOJSONSERVICECOMMAND_H

#include "ICommand.hpp"
#include "IRenderer.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "../Services/Services.hpp"

#include <memory>
#include <vector>

namespace Commands {

	class SendToJsonServiceCommand : public ICommand
	{
	public:
		SendToJsonServiceCommand();
		void SetRenderers(std::vector<std::shared_ptr<Renderers::IRenderer>> const renderers) override;
		void Execute() override;
	private:
		std::shared_ptr<Services::JsonService> m_json_service;
		std::vector<std::shared_ptr<Renderers::IRenderer>> m_renderers;
	};
}

#endif