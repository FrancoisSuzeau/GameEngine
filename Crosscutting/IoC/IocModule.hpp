/******************************************************************************************************************************************/
// File : IoCModule.hpp
// Purpose : An ioc module to connect to all services and then inject necessary data
/******************************************************************************************************************************************/
#ifndef IOCMODULE
#define IOCMODULE
#include "Container/Container.hpp"
#include "Container/Container.cpp"
#include "IBuilder.hpp"

namespace IoC {

	class IocModule
	{
	public:
		IocModule();
		~IocModule();

		template<typename T>
		void Load(Builders::IBuilder *builder);
		void StartBuilder(Builders::IBuilder* builder);

	private:

	};
}

#endif