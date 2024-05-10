/******************************************************************************************************************************************/
// File : DeleteComponent.hpp
// Purpose : A save scene command
/******************************************************************************************************************************************/
#ifndef DELETECOMPONENT_H
#define DELETECOMPONENT_H

#include "ICommand.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "../Services/StateService.hpp"

#include <memory>

namespace Commands {

	class DeleteComponent : public ICommand
	{
	public:
		DeleteComponent();
		~DeleteComponent();
		void Execute() override;
	private:
		std::shared_ptr<Services::StateService> m_state_service;
	};
}

#endif