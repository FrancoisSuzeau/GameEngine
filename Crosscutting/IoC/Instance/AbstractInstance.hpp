/******************************************************************************************************************************************/
// File : AbstractInstance.hpp
// Purpose : the abstract instance for container
/******************************************************************************************************************************************/
#ifndef ABINSTANCE_H
#define ABINSTANCE_H

#include <typeinfo>
#include <typeindex>

#include <memory>
#include <unordered_map>

namespace IoC {


	namespace Instances
	{
		class AbstractInstance
		{
		public:
			virtual ~AbstractInstance() {}
		};
	}
}
#endif