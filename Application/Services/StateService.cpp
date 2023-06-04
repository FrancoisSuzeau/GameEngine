/******************************************************************************************************************************************/
// File : StateService.cpp
// Purpose : Implementing service Opengl / SDL  initialisation
/******************************************************************************************************************************************/
#include "StateService.hpp"

using namespace Services;

void StateService::Init()
{
	IoC::Container::Container *container = IoC::Container::Container::GetInstanceContainer();
	std::shared_ptr<Services::GraphicInitializerService> graph_service_init = container->make<Services::GraphicInitializerService>();
	m_width = graph_service_init->GetWidth();
	m_height = graph_service_init->GetHeight();

	m_exit = false;
}

void StateService::DeInit()
{
	
}

bool StateService::getExit() const
{
	return m_exit;
}

void StateService::setExit(bool const new_val)
{
	m_exit = new_val;
}

int StateService::getWidth() const
{
	return m_width;
}

int StateService::getHeight() const
{
	return m_height;
}


