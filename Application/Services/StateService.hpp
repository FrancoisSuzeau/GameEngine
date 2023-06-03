/******************************************************************************************************************************************/
// File : StateService.hpp
// Purpose : A service initialising Opengl / SDL
/******************************************************************************************************************************************/
#ifndef STATESERVICE_H
#define STATESERVICE_H

#include <iostream>
#include "Container/Container.hpp"
#include "GraphicInitializerService.hpp"

#include "IService.hpp"

namespace Services {

	class StateService : public IService
	{

	public:
		void Init() override;
		void DeInit() override;

		bool getExit() const;
		void setExit(bool const new_val);
		int getWidth() const;
		int getHeight() const;


	private:

		int m_width;
		int m_height;
		bool m_exit;
	};
}

#endif