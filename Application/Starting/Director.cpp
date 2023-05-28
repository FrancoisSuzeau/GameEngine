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
}
template<typename T>
void Director::SetBuilder()
{
    std::unique_ptr<IoC::IocModule> ioc_module;
    ioc_module->Load<T>(m_service_builder);
    ioc_module.reset();
}

template<typename T>
std::shared_ptr<Services::IService> Director::GetServiceInitializer()
{
    auto type = std::type_index(typeid(T));
    return m_service_builder->GetServiceInitalizer(type.name());
}



void Director::EndingBuilder()
{
    if (m_service_builder != nullptr)
    {
        m_service_builder->OnServicesEnd();
        delete m_service_builder;
        m_service_builder = nullptr;
    }

}

void Director::StartAllBuilder()
{
    std::unique_ptr<IoC::IocModule> ioc_module;
    ioc_module->StartBuilder(m_service_builder);
    ioc_module.reset();
}
