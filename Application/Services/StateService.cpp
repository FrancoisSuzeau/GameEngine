/******************************************************************************************************************************************/
// File : StateService.cpp
// Purpose : Implementing service Opengl / SDL  initialisation
/******************************************************************************************************************************************/
#include "StateService.hpp"

namespace Services
{
	StateService::StateService() : m_show_metrics(false), m_show_tools(false), m_exit(false), m_height(0), m_width(0), m_show_app_info(false),
		m_show_style_editor(false), m_show_event(false), m_current_filename(Constants::DEFAULT_FILENAME), m_gui_open(false)
	{
	}

	void StateService::Init()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			std::shared_ptr<Services::GraphicInitializerService> graph_service_init = container->GetReference<Services::GraphicInitializerService>();
			if (graph_service_init)
			{
				m_width = graph_service_init->GetWidth();
				m_height = graph_service_init->GetHeight();
				graph_service_init.reset();
			}
			else
			{
				SQ_APP_ERROR("Class {} in function {} : Graphic service initializer is not referenced yet", __FILE__, __FUNCTION__);
			}
			m_camera_services = container->GetReference<Services::CameraService>();
			if (!m_camera_services)
			{
				SQ_APP_ERROR("Class {} in function {} : Camera service is not referenced yet", __FILE__, __FUNCTION__);
				
			}
			else
			{
				m_projection_matrix = glm::perspective(glm::radians(45.0f), (float)m_width / (float)m_height, 0.1f, 20.0f);
			}
		}

		m_exit = false;
		m_show_metrics = false;

		m_view = glm::mat4(1.f);
		
	}

	void StateService::DeInit()
	{
		if (m_camera_services)
		{
			m_camera_services.reset();
		}
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

	bool StateService::getShowMetrics() const
	{
		return m_show_metrics;
	}

	void StateService::setShowMetrics(bool const new_val)
	{
		m_show_metrics = new_val;
	}
	bool StateService::getShowTools() const
	{
		return m_show_tools;
	}
	void StateService::setShowTools(bool const new_val)
	{
		m_show_tools = new_val;
	}

	bool StateService::getShowInfos() const
	{
		return m_show_app_info;
	}
	void StateService::setShowInfos(bool const new_val)
	{
		m_show_app_info = new_val;
	}
	bool StateService::getShowStyleEditor() const
	{
		return m_show_style_editor;
	}
	void StateService::setShowStyleEditor(bool const new_val)
	{
		m_show_style_editor = new_val;
	}
	void StateService::setShowEvent(bool const new_val)
	{
		m_show_event = new_val;
	}
	bool StateService::getShowEvent() const
	{
		return m_show_event;
	}

	void StateService::setFileName(std::string const new_val)
	{
		m_current_filename = new_val;
	}

	void StateService::setGuiOpen(bool const new_val)
	{
		m_gui_open = new_val;
	}

	bool StateService::getGuiOpen() const
	{
		return m_gui_open;
	}

	std::string StateService::getFileName() const
	{
		return m_current_filename;
	}
	
	glm::mat4 StateService::GetViewMatrix() const
	{
		if (m_camera_services)
		{
			return m_camera_services->GetCameraView();
		}

		return m_view;
	}
	glm::mat4 StateService::GetProjectionMatrix() const
	{
		return m_projection_matrix;
	}
	void StateService::RefreshProjectionMatrix()
	{
		if (m_camera_services)
		{
			m_projection_matrix = glm::perspective(glm::radians(45.f), (float)m_width / (float)m_height, 0.1f, 20.0f);
		}
	}
}




