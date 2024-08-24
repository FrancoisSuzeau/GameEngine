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
				auto type = std::type_index(typeid(T));
				auto instance = std::make_shared<Instances::Instance<T>>(static_cast<T*>(callback()));
				m_instances.insert_or_assign(type, instance);
			}

			template<typename T>
			std::shared_ptr<T> GetReference()
			{
				auto type = std::type_index(typeid(T));

				if(m_instances.contains(type))
				{
					auto instance = std::static_pointer_cast<Instances::Instance<T>>(m_instances.at(type));
					return instance->m_ptr;
				}

				return nullptr;
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
			std::map<std::type_index, std::shared_ptr<Instances::IInstance>> m_instances;
		};
	}
};
#endif