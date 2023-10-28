/******************************************************************************************************************************************/
// File : ICommand.hpp
// Purpose : An interface for the command pattern
/******************************************************************************************************************************************/
#ifndef ICOMMAND_H
#define ICOMMAND_H

#include "IRenderer.hpp"
#include <vector>

namespace Commands {

	class ICommand
	{
	public:
		virtual ~ICommand() {}
		virtual void Execute() = 0;
		virtual void SetRenderers(std::vector<std::shared_ptr<Renderers::IRenderer>> const renderers) {};
	};
}

#endif