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
	for (std::map<std::string, std::shared_ptr<Services::IService>>::iterator it = m_services_initializer.begin();
		it != m_services_initializer.end(); ++it)
	{
		if (it->second)
		{
			it->second->Init();
		}
	}
}

void ServiceBuilder::Build(std::string service_name, std::shared_ptr<Services::IService> service_initializer)
{
	if (service_initializer)
	{
		m_services_initializer.insert_or_assign(service_name, service_initializer);
	}
}

void ServiceBuilder::Build(std::shared_ptr<Engines::IEngine> engine)
{
	
}

void ServiceBuilder::Build(std::shared_ptr<ViewModels::IViewModel> view_model)
{

}

void ServiceBuilder::OnBuilderEnd()
{
	for (std::map<std::string, std::shared_ptr<Services::IService>>::reverse_iterator it = m_services_initializer.rbegin();
		it != m_services_initializer.rend(); ++it)
	{
		if (it->second)
		{
			it->second->DeInit();
			it->second.reset();
		}
	}
}
