/******************************************************************************************************************************************/
// File : Container.cpp
// Purpose : Implementing the container singleton pattern
/******************************************************************************************************************************************/
#include "Container.hpp"

namespace IoC
{
	namespace Container
	{
		Container* Container::m_container = nullptr;

		Container::Container()
		{

		}

		Container* Container::GetInstanceContainer()
		{
			if (m_container == nullptr)
			{
				m_container = new Container();
			}

			return m_container;
		}
	}
}
