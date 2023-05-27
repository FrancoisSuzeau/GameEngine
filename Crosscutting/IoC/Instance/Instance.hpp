/******************************************************************************************************************************************/
// File : Instance.hpp
// Purpose : the instance for container
/******************************************************************************************************************************************/
#ifndef INSTANCE_H
#define INSTANCE_H

#include "AbstractInstance.hpp"

namespace IoC {

	

	namespace Instances
	{
		template<typename T>
		class Instance : public AbstractInstance
		{
		public:
			Instance(T* ptr);
			std::shared_ptr<T> m_ptr;
		};
	}
}
#endif