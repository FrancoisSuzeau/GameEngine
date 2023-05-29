/******************************************************************************************************************************************/
// File : Director.cpp
// Purpose : Implementing the director
/******************************************************************************************************************************************/
#include "Director.hpp"

using namespace Starting;

Director::Director()
{
    if (m_service_builder == nullptr)
    {
        m_service_builder = new Builders::ServiceBuilder();
        assert(m_service_builder);
    }

    if (m_engine_builder == nullptr)
    {
        m_engine_builder = new Builders::EngineBuilder();
        assert(m_engine_builder);
    }
}
template<typename T>
void Director::SetServiceBuilder()
{
    std::unique_ptr<IoC::IocModule> ioc_module = std::make_unique<IoC::IocModule>();
    ioc_module->LoadService<T>(m_service_builder);
    ioc_module.reset();
}

template<typename T>
void Director::SetEngineBuilder()
{
    std::unique_ptr<IoC::IocModule> ioc_module = std::make_unique<IoC::IocModule>();
    ioc_module->LoadEngine<T>(m_engine_builder);
    ioc_module.reset();
}

void Director::EndingBuilders()
{
    if (m_service_builder != nullptr)
    {
        m_service_builder->OnBuilderEnd();
        delete m_service_builder;
        m_service_builder = nullptr;
    }

    if (m_engine_builder != nullptr)
    {
        m_engine_builder->OnBuilderEnd();
        delete m_engine_builder;
        m_engine_builder = nullptr;
    }
}

void Director::StartAllBuilders()
{
    std::unique_ptr<IoC::IocModule> ioc_module = std::make_unique<IoC::IocModule>();
    ioc_module->StartBuilder(m_service_builder);
    ioc_module->StartBuilder(m_engine_builder);
    ioc_module.reset();
}
