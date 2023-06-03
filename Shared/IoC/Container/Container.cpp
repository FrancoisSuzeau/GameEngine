/******************************************************************************************************************************************/
// File : Container.cpp
// Purpose : Implementing the container singleton pattern
/******************************************************************************************************************************************/
#include "Container.hpp"

using namespace IoC::Container;

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

template<typename T>
void Container::registerType(std::function<T* ()> callback)
{
	m_callbacks[std::type_index(typeid(T))] = callback;
}

template<typename T>
std::shared_ptr<T> Container::make()
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
