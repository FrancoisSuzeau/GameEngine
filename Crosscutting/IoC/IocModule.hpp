/******************************************************************************************************************************************/
// File : IoCModule.hpp
// Purpose : An ioc module to connect to all services and then inject necessary data
/******************************************************************************************************************************************/
#ifndef IOCMODULE
#define IOCMODULE
#include "Container/Container.hpp"
#include "Container/Container.cpp"

namespace IoC {

	class IocModule
	{
	public:
		IocModule();
		~IocModule();

		void Load();

	private:

	};
}

#endif