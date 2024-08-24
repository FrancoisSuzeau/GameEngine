/******************************************************************************************************************************************/
// File : Application.hpp
// Purpose : Application creating, setting the builders and produce them via Ioc
/******************************************************************************************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Builders/EngineBuilder.hpp"
#include "Builders/ServiceBuilder.hpp"
#include "Builders/ViewModelBuilder.hpp"
#include "IocModule.hpp"

#include "Services/GraphicInitializerService.hpp"
#include "Services/AudioInitializerService.hpp"
#include "Services/ImGUIServiceInitalizer.hpp"
#include "Services/StateService.hpp"
#include "Services/ShaderService.hpp"
#include "Services/FramebufferService.hpp"
#include "Services/CameraService.hpp"
#include "Services/LoaderService.hpp"
#include "Services/MouseInputService.hpp"
#include "Services/KeyboardInputService.hpp"
#include "Services/RunTimeService.hpp"
#include "Services/PhysicsService.hpp"

#include "JsonLoaderService/JsonLoaderService.hpp"
#include "ShaderLoaderService/ShaderLoaderService.hpp"
#include "TextureLoaderService/TextureLoaderService.hpp"
#include "ModelLoaderService/ModelLoaderService.hpp"

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
		void AddViewModel(std::string const view_model_type)
		{
			std::unique_ptr<IoC::IocModule> ioc_module = std::make_unique<IoC::IocModule>();
			if (ioc_module && m_view_model_builder)
			{
				ioc_module->AddViewModel<T>(m_view_model_builder.get(), view_model_type);
				ioc_module.reset();
			}
		}

		template<typename T>
		void DeleteReference()
		{
			std::unique_ptr<IoC::IocModule> ioc_module = std::make_unique<IoC::IocModule>();
			if (ioc_module)
			{
				ioc_module->DestroyReference<T>();
				ioc_module.reset();
			}
		}
		

	private:
		std::unique_ptr<Builders::ServiceBuilder> m_service_builder;
		std::unique_ptr<Builders::EngineBuilder> m_engine_builder;
		std::shared_ptr<Builders::ViewModelBuilder> m_view_model_builder;
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

		void ShutAllService();
		void ShutAllEngine();
	};

}

#endif