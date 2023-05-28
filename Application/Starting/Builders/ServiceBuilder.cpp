/******************************************************************************************************************************************/
// File : ServiceBuilder.cpp
// Purpose : Implementing the service builder
/******************************************************************************************************************************************/
#include "ServiceBuilder.hpp"

using namespace Builders;

ServiceBuilder::~ServiceBuilder()
{
	
}

void ServiceBuilder::Produce()
{
	for (std::unordered_map<std::string, std::shared_ptr<Services::IService>>::iterator it = m_services_initializer.begin();
		it != m_services_initializer.end(); ++it)
	{
		it->second->Init();
	}
}

void ServiceBuilder::Build(std::string service_name, std::shared_ptr<Services::IService> service_initializer)
{
	m_services_initializer.insert_or_assign(service_name, service_initializer);
}

void ServiceBuilder::OnServicesEnd()
{
	for (std::unordered_map<std::string, std::shared_ptr<Services::IService>>::iterator it = m_services_initializer.begin();
		it != m_services_initializer.end(); ++it)
	{
		it->second->DeInit();
	}
}

std::shared_ptr<Services::IService> Builders::ServiceBuilder::GetServiceInitalizer(std::string service_name) const
{
	return m_services_initializer.at(service_name);
}
