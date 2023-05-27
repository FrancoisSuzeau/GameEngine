/******************************************************************************************************************************************/
// File : Container.hpp
// Purpose : A container holding service for IoC module
/******************************************************************************************************************************************/
#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <functional>

#include "../Instance/Instance.hpp"
//to remove linking issue
#include "../Instance/Instance.cpp"

namespace IoC {

	namespace Container
	{
		class Container
		{
		protected:
			
			static Container* m_container;
		public:
			Container();
			Container(Container& other) = delete;
			void operator=(const Container&) = delete;
			static Container* GetInstanceContainer();

			template<typename T>
			void registerType(std::function<T* ()> callback);

			template<typename T>
			std::shared_ptr<T> make();

		private:
			std::unordered_map<std::type_index, std::function<void* ()>> m_callbacks;
			std::unordered_map<std::type_index, std::shared_ptr<Instances::IInstance>> m_instances;
		};
	}
};
#endif