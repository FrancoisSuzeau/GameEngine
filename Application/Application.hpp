/******************************************************************************************************************************************/
// File : Application.hpp
// Purpose : Application creating, setting the builders and produce them via Ioc
/******************************************************************************************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Builders/Builders.hpp"
#include "IocModule.hpp"
#include "Services/Services.hpp"
#include "ExternalServices.hpp"
#include "Engines/Engines.hpp"
#include "Logger.hpp"

#include <cassert>
#include <memory>

namespace Starting {

	class Application
	{
	public:
		Application() {};
		
		void Initialize();
		void Run();
		void Shutdown();

		template<typename T>
		void AddView()
		{
			std::unique_ptr<IoC::IocModule> ioc_module = std::make_unique<IoC::IocModule>();
			if (ioc_module)
			{
				ioc_module->AddView<T>();
				ioc_module.reset();
			}
		}

		template<typename T>
		void AddViewModel()
		{
			std::unique_ptr<IoC::IocModule> ioc_module = std::make_unique<IoC::IocModule>();
			if (ioc_module && m_view_model_builder)
			{
				ioc_module->AddViewModel<T>(m_view_model_builder.get());
				ioc_module.reset();
			}
		}
		

	private:
		std::unique_ptr<Builders::ServiceBuilder> m_service_builder;
		std::unique_ptr<Builders::EngineBuilder> m_engine_builder;
		std::unique_ptr<Builders::ViewModelBuilder> m_view_model_builder;
		std::shared_ptr<Engines::MainEngine> main_engine;

		template<typename T>
		void SetServiceBuilder()
		{
			std::unique_ptr<IoC::IocModule> ioc_module = std::make_unique<IoC::IocModule>();
			if (ioc_module && m_service_builder)
			{
				ioc_module->LoadService<T>(m_service_builder.get());
				ioc_module.reset();
			}
		}

		template<typename T>
		void SetEngineBuilder()
		{
			std::unique_ptr<IoC::IocModule> ioc_module = std::make_unique<IoC::IocModule>();
			if (ioc_module && m_engine_builder)
			{
				ioc_module->LoadEngine<T>(m_engine_builder.get());
				ioc_module.reset();
			}
		}

		void EndAllBuilder();
		void StartAllBuilder();
		void SetAllService();
		void SetAllEngine();
	};

}

#endif