/******************************************************************************************************************************************/
// File : IocModule.cpp
// Purpose : Implementing the inversion of control module
/******************************************************************************************************************************************/
#include "IocModule.hpp"

using namespace IoC;

IocModule::IocModule()
{
}

IocModule::~IocModule()
{
}

void IocModule::StartBuilder(Builders::IBuilder* builder)
{
    builder->Produce();
}