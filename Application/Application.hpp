/******************************************************************************************************************************************/
// File : Application.hpp
// Purpose : Application creating, setting the builders and produce them via Ioc
/******************************************************************************************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Builders/ServiceBuilder.hpp"
#include "Builders/EngineBuilder.hpp"
#include "IocModule.hpp"
#include "IService.hpp"
#include "Services/GraphicInitializerService.hpp"
#include "Services/AudioInitializerService.hpp"
#include "Services/ImGUIServiceInitalizer.hpp"
#include "Services/StateService.hpp"

#include <cassert>
#include <memory>

namespace Starting {

	class Application
	{
	public:
		Application();
		void SetAllServices();
		template<typename T>
		void SetServiceBuilder()
		{
			std::unique_ptr<IoC::IocModule> ioc_module = std::make_unique<IoC::IocModule>();
			ioc_module->LoadService<T>(m_service_builder.get());
			ioc_module.reset();
		}
		template<typename T>
		void SetEngineBuilder()
		{
			std::unique_ptr<IoC::IocModule> ioc_module = std::make_unique<IoC::IocModule>();
			ioc_module->LoadEngine<T>(m_engine_builder.get());
			ioc_module.reset();
		}
		void EndingBuilders();
		void StartAllBuilders();

	private:
		std::unique_ptr<Builders::ServiceBuilder> m_service_builder;
		std::unique_ptr<Builders::EngineBuilder> m_engine_builder;
	};

}

#endif