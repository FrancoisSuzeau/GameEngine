/******************************************************************************************************************************************/
// File : IocModule.cpp
// Purpose : Implementing the inversion of control module
/******************************************************************************************************************************************/
#include "IocModule.hpp"

namespace IoC
{
	IocModule::IocModule()
	{
	}

	IocModule::~IocModule()
	{
	}

	void IocModule::StartBuilder(Builders::IBuilder* builder)
	{
		if (builder)
		{
			builder->Produce();
		}
	}
}

