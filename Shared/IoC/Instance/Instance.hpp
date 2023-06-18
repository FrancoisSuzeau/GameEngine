/******************************************************************************************************************************************/
// File : Instance.hpp
// Purpose : the instance for container
/******************************************************************************************************************************************/
#ifndef INSTANCE_H
#define INSTANCE_H

#include "IInstance.hpp"

namespace IoC {

	

	namespace Instances
	{
		template<typename T>
		class Instance : public IInstance
		{
		public:
			Instance(T* ptr) : m_ptr(ptr) {}
			std::shared_ptr<T> m_ptr;
		};
	}
}
#endif