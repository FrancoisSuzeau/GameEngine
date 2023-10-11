/******************************************************************************************************************************************/
// File : Container.hpp
// Purpose : A container holding service for IoC module
/******************************************************************************************************************************************/
#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <functional>
#include <map>

#include "../Instance/Instance.hpp"

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
			void registerType(std::function<T* ()> callback)
			{
				m_callbacks[std::type_index(typeid(T))] = callback;
			}

			template<typename T>
			std::shared_ptr<T> GetReference()
			{
				auto type = std::type_index(typeid(T));

				auto search = m_instances.find(type);
				if (search != m_instances.end()) {
					auto instance = std::static_pointer_cast<Instances::Instance<T>>(search->second);
					return instance->m_ptr;
				}

				void* ptr = m_callbacks[type]();
				auto instance = std::make_shared<Instances::Instance<T>>(static_cast<T*>(ptr));
				m_instances[type] = instance;
				return instance->m_ptr;
			}

			template<typename T>
			void DestroyReference()
			{
				auto type = std::type_index(typeid(T));
				if (m_instances.contains(type))
				{
					auto instance = m_instances.at(type);
					instance->Destroy();
					instance.reset();
				}
			}

		private:
			std::unordered_map<std::type_index, std::function<void* ()>> m_callbacks;
			std::map<std::type_index, std::shared_ptr<Instances::IInstance>> m_instances;
		};
	}
};
#endif