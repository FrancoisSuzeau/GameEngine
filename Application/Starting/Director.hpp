/******************************************************************************************************************************************/
// File : Director.hpp
// Purpose : Director creating, setting the builders and produce them via Ioc
/******************************************************************************************************************************************/
#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "../Builders/ServiceBuilder.hpp"
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
		void SetBuilder();
		void EndingBuilder();
		void StartAllBuilder();

	private:
		Builders::ServiceBuilder* m_service_builder = nullptr;
	};

}

#endif