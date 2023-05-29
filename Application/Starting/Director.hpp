/******************************************************************************************************************************************/
// File : Director.hpp
// Purpose : Director creating, setting the builders and produce them via Ioc
/******************************************************************************************************************************************/
#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "Builders/ServiceBuilder.hpp"
#include "Builders/EngineBuilder.hpp"
#include "IocModule.hpp"
#include "IocModule.cpp"
#include "IService.hpp"
#include <cassert>

namespace Starting {

	class Director
	{
	public:
		Director();
		template<typename T>
		void SetServiceBuilder();
		template<typename T>
		void SetEngineBuilder();
		void EndingBuilders();
		void StartAllBuilders();

	private:
		Builders::ServiceBuilder* m_service_builder = nullptr;
		Builders::EngineBuilder* m_engine_builder = nullptr;
	};

}

#endif