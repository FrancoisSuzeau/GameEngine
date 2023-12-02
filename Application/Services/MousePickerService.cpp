/******************************************************************************************************************************************/
// File : MousePickerService.cpp
// Purpose : Implementing the mouse picker service
/******************************************************************************************************************************************/
#include "MousePickerService.hpp"

namespace Services
{
	void MousePickerService::Init()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_state_service = container->GetReference<StateService>();
			if (!m_state_service)
			{
				SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}
			else
			{
				m_proj_mat = m_state_service->GetProjectionMatrix();
				m_view_mat = m_state_service->GetViewMatrix();
			}
		}
	}

	void MousePickerService::DeInit()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}
	}
	void MousePickerService::Update()
	{
		if (m_state_service)
		{
			m_view_mat = m_state_service->GetViewMatrix();
			m_current_ray = this->CalculateMouseRay();
		}
	}
	glm::vec3 MousePickerService::GetCurrentRay()
	{
		return m_current_ray;
	}
	glm::vec3 MousePickerService::CalculateMouseRay()
	{
		return glm::vec3();
	}
}

