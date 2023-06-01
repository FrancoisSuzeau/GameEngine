/******************************************************************************************************************************************/
// File : Application.cpp
// Purpose : Implementing the Application
/******************************************************************************************************************************************/
#include "Application.hpp"

using namespace Starting;

Application::Application()
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
void Application::SetServiceBuilder()
{
    std::unique_ptr<IoC::IocModule> ioc_module = std::make_unique<IoC::IocModule>();
    ioc_module->LoadService<T>(m_service_builder);
    ioc_module.reset();
}

template<typename T>
void Application::SetEngineBuilder()
{
    std::unique_ptr<IoC::IocModule> ioc_module = std::make_unique<IoC::IocModule>();
    ioc_module->LoadEngine<T>(m_engine_builder);
    ioc_module.reset();
}

void Application::EndingBuilders()
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

void Application::StartAllBuilders()
{
    std::unique_ptr<IoC::IocModule> ioc_module = std::make_unique<IoC::IocModule>();
    ioc_module->StartBuilder(m_service_builder);
    ioc_module->StartBuilder(m_engine_builder);
    ioc_module.reset();
}
