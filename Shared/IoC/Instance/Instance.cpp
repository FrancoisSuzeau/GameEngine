/******************************************************************************************************************************************/
// File : Instance.cpp
// Purpose : Implementing Instance for Container
/******************************************************************************************************************************************/
#include "Instance.hpp"

using namespace IoC::Instances;

template<typename T>
Instance<T>::Instance(T* ptr) : m_ptr(ptr) 
{

}
