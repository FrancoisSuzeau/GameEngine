/******************************************************************************************************************************************/
// File : IInstance.hpp
// Purpose : the interface instance for container
/******************************************************************************************************************************************/
#ifndef IINSTANCE_H
#define IINSTANCE_H

#include <typeinfo>
#include <typeindex>

#include <memory>
#include <unordered_map>

namespace IoC {


	namespace Instances
	{
		class IInstance
		{
		public:
			virtual ~IInstance() {}
		};
	}
}
#endif