/******************************************************************************************************************************************/
// File : Application.hpp
// Purpose : Application creating, setting the builders and produce them via Ioc
/******************************************************************************************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Builders/ServiceBuilder.hpp"
#include "Builders/EngineBuilder.hpp"
#include "IocModule.hpp"
#include "IocModule.cpp"
#include "IService.hpp"
#include <cassert>
#include <memory>

namespace Starting {

	class Application
	{
	public:
		Application();
		template<typename T>
		void SetServiceBuilder();
		template<typename T>
		void SetEngineBuilder();
		void EndingBuilders();
		void StartAllBuilders();

	private:
		std::unique_ptr<Builders::ServiceBuilder> m_service_builder;
		std::unique_ptr<Builders::EngineBuilder> m_engine_builder;
	};

}

#endif