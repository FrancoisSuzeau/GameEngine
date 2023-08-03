/******************************************************************************************************************************************/
// File : Startup.hpp
// Purpose : The startup of application
/******************************************************************************************************************************************/
#ifndef STARTUP_H
#define STARTUP_H

#include "Application.hpp"
#include "Views/Views.hpp"
#include "ViewModels/GUIViewModel.hpp"

#include <iostream>
#include <list>
#include <map>

namespace Starting {
	
	static class Startup
	{
	public:
		static void ConfigureClientViews(std::shared_ptr<Application> app);
	};
}


#endif