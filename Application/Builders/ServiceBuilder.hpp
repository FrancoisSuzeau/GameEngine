/******************************************************************************************************************************************/
// File : ServiceBuilder.hpp
// Purpose : A builder for SDL, Opengl services
/******************************************************************************************************************************************/
#ifndef SERVICEBUILDER_H
#define SERVICEBUILDER_H

#include <map>
#include <iostream>
#include <memory>
#include <string>

#include "IService.hpp"
#include "IBuilder.hpp"
#include "Container/Container.hpp"

namespace Builders {

	class ServiceBuilder : public IBuilder
	{
	public:
		~ServiceBuilder() override;
		void Produce() override;
		void Build(std::string service_name, std::shared_ptr<Services::IService> service_initializer) override;
		void Build(std::shared_ptr<Engines::IEngine> engine) override;

		void OnBuilderEnd() override;

 	private:

		std::map<std::string, std::shared_ptr<Services::IService>> m_services_initializer;
	};
}

#endif