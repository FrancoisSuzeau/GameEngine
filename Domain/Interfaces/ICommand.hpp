/******************************************************************************************************************************************/
// File : ICommand.hpp
// Purpose : An interface for the command pattern
/******************************************************************************************************************************************/
#ifndef ICOMMAND_H
#define ICOMMAND_H

namespace Commands {

	class ICommand
	{
	public:
		virtual ~ICommand() {}
		virtual void Execute() = 0;
	};
}

#endif