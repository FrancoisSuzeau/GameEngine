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

template<typename T>
void IocModule::LoadService(Builders::IBuilder* builder)
{
    auto type = std::type_index(typeid(T));

    IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
    container->registerType<T>([]() {
        return new T();
        });

    auto service = container->make<T>();

    builder->Build(type.name(), service);
}

template<typename T>
void IocModule::LoadEngine(Builders::IBuilder* builder)
{
    IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
    container->registerType<T>([]() {
        return new T();
        });
    auto engine = container->make<T>();

    builder->Build(engine);
}
