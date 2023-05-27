/******************************************************************************************************************************************/
// File : Container.hpp
// Purpose : A container holding service for IoC module
/******************************************************************************************************************************************/
#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <functional>
#include <memory>
#include <unordered_map>

namespace IoC {

	class Container
	{
	public:
		class AbstractInstance
		{
		public:
			virtual ~AbstractInstance() {}
		};

		template<typename T>
		class Instance : public AbstractInstance
		{
		public:
			Instance(T* ptr) : ptr(ptr) {}
			std::shared_ptr<T> ptr;
		};

		template<typename T>
		void registerType(std::function<T* ()> callback)
		{
			m_callbacks[std::type_index(typeid(T))] = callback;
		}

		template<typename T>
		std::shared_ptr<T> make()
		{
			auto type = std::type_index(typeid(T));

			auto search = m_instances.find(type);
			if (search != m_instances.end()) {
				auto instance = std::static_pointer_cast<Instance<T>>(search->second);
				return instance->ptr;
			}

			void* ptr = m_callbacks[type]();
			auto instance = std::make_shared<Instance<T>>(static_cast<T*>(ptr));
			m_instances[type] = instance;
			return instance->ptr;
		}

	private:
		std::unordered_map<std::type_index, std::function<void* ()>> m_callbacks;
		std::unordered_map<std::type_index, std::shared_ptr<AbstractInstance>> m_instances;
	};
};

#endif