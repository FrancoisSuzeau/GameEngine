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
#include "JsonLoaderService.hpp"
#include "ShaderLoaderService.hpp"
#include "Engines/SceneEngine.hpp"
#include "Engines/GUIEngine.hpp"
#include "Engines/MainEngine.hpp"
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
		void SetGuiComponent()
		{
			std::unique_ptr<IoC::IocModule> ioc_module = std::make_unique<IoC::IocModule>();
			ioc_module->LoadComponent<T>();
			ioc_module.reset();
		}
		

	private:
		std::unique_ptr<Builders::ServiceBuilder> m_service_builder;
		std::unique_ptr<Builders::EngineBuilder> m_engine_builder;
		std::shared_ptr<Engines::MainEngine> main_engine;

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

		void EndAllBuilder();
		void StartAllBuilder();
		void SetAllService();
		void SetAllEngine();
	};

}

#endif