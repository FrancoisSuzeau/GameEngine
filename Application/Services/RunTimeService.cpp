/******************************************************************************************************************************************/
// File : RunTimeService.cpp
// Purpose : Implementing service shader
/******************************************************************************************************************************************/
#include "RunTimeService.hpp"

namespace Services
{
	RunTimeService::RunTimeService() : m_is_rendering_line(false)
	{
	}
	void RunTimeService::Init()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_opengl_service = container->GetReference<Services::OpenGLService>();
			if (!m_opengl_service)
			{
				SQ_APP_ERROR("Class {} in function {} : OpenGL service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
	}

	void RunTimeService::DeInit()
	{
		if (m_opengl_service)
		{
			m_opengl_service.reset();
		}
	}
	void RunTimeService::RenderingInLine(float const line_width)
	{
		if (m_opengl_service)
		{
			m_is_rendering_line = true;
			m_opengl_service->setRenderingMode(GL_LINE, line_width);
		}
	}
	void RunTimeService::RenderingInFill()
	{
		if (m_opengl_service)
		{
			m_is_rendering_line = false;
			m_opengl_service->setRenderingMode(GL_FILL, 0.f);
		}
	}

	void RunTimeService::LequalDepth()
	{
		if (m_opengl_service)
		{
			m_opengl_service->setDepth(GL_LEQUAL);
		}
	}

	void RunTimeService::LessDepth()
	{
		if (m_opengl_service)
		{
			m_opengl_service->setDepth(GL_LESS);
		}
	}


	bool RunTimeService::IsRenderingLine() const
	{
		return m_is_rendering_line;
	}
}

