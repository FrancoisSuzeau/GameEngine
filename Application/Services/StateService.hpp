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
		StateService();
		void Init() override;
		void DeInit() override;

		bool getExit() const;
		void setExit(bool const new_val);
		int getWidth() const;
		int getHeight() const;
		bool getShowMetrics() const;
		void setShowMetrics(bool const new_val);
		bool getShowTools() const;
		void setShowTools(bool const new_val);
		bool getShowInfos() const;
		void setShowInfos(bool const new_val);


	private:

		int m_width;
		int m_height;
		bool m_exit;
		bool m_show_metrics;
		bool m_show_tools;
		bool m_show_app_info;
	};
}

#endif