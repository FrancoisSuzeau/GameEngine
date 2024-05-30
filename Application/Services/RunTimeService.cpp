/******************************************************************************************************************************************/
// File : RunTimeService.cpp
// Purpose : Implementing service shader
/******************************************************************************************************************************************/
#include "RunTimeService.hpp"

namespace Services
{
	RunTimeService::RunTimeService() : m_is_rendering_line(false), m_fb_type(Enums::FramebufferType::NORMALCOLORBUFFER), m_stencil_type(Enums::StencilType::STENCILBUFFERWRITE)
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

		this->SetAttenuationConstants();
	}

	void RunTimeService::DeInit()
	{
		m_attenuation_constants.clear();
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
	void RunTimeService::RefreshScreen()
	{
		this->RefreshColor(glm::vec4(0.07f, 0.13f, 0.17f, 1.f));
		this->RefreshBuffers(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	void RunTimeService::RefreshColor(glm::vec4 const colors)
	{
		if (m_opengl_service)
		{
			m_opengl_service->clearColor(colors);
		}
	}
	void RunTimeService::RefreshBuffers(GLbitfield const masks)
	{
		if (m_opengl_service)
		{
			m_opengl_service->clearBuffer(masks);
		}
	}
	void RunTimeService::EnableBlendCapture()
	{
		if (m_opengl_service)
		{
			m_opengl_service->enable(GL_BLEND);
		}
	}

	void RunTimeService::EnableDepthTest()
	{
		if (m_opengl_service)
		{
			m_opengl_service->enable(GL_DEPTH_TEST);
		}
	}
	void RunTimeService::DisableDepthTest()
	{
		if (m_opengl_service)
		{
			m_opengl_service->disable(GL_DEPTH_TEST);
		}
	}
	void RunTimeService::SetMinusSrcAlpha()
	{
		if (m_opengl_service)
		{
			m_opengl_service->blend(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
	}
	void RunTimeService::DeleteTexture(unsigned int &texture_id)
	{
		if (m_opengl_service)
		{
			m_opengl_service->deleteTexture(texture_id);
		}
	}
	void RunTimeService::DeleteBuffer(unsigned int &buffer_id)
	{
		if (m_opengl_service)
		{
			m_opengl_service->deleteBuffer(buffer_id);
		}
	}
	void RunTimeService::DeleteRenderBuffer(unsigned int &render_buffer_id)
	{
		if (m_opengl_service)
		{
			m_opengl_service->deleteRenderBuffer(render_buffer_id);
		}
	}
	void RunTimeService::DisableWriteStencilBuffer()
	{
		if (m_opengl_service)
		{
			m_opengl_service->writeStencilMask(0x00);
		}
	}
	
	void RunTimeService::StencilFuncToWrite()
	{
		if (m_opengl_service)
		{
			m_opengl_service->stencilFunc(GL_ALWAYS, 1, 0xFF);
			m_opengl_service->writeStencilMask(0xFF);
		}
	}
	void RunTimeService::StencilFuncToRead()
	{
		if (m_opengl_service)
		{
			m_opengl_service->stencilFunc(GL_NOTEQUAL, 1, 0xFF);
			this->DisableWriteStencilBuffer();
		}
	}
	void RunTimeService::StencilFuncDisable()
	{
		if (m_opengl_service)
		{
			m_opengl_service->writeStencilMask(0xFF);
			m_opengl_service->stencilFunc(GL_ALWAYS, 0, 0xFF);
		}
	}
	void RunTimeService::SetPass(Enums::FramebufferType fb_type)
	{
		m_fb_type = fb_type;
	}
	void RunTimeService::SetStencilPass(Enums::StencilType stencil_type)
	{
		m_stencil_type = stencil_type;
	}
	Enums::FramebufferType RunTimeService::GetPass() const
	{
		return m_fb_type;
	}
	Enums::StencilType RunTimeService::GetStencilPass() const
	{
		return m_stencil_type;
	}
	Attenuation_constants RunTimeService::GetAttenuationConstant(int const distance)
	{
		if (distance >= 0 && distance <= 7)
		{
			return m_attenuation_constants.front();
		}

		if (distance > 600 && distance <= 3250)
		{
			return m_attenuation_constants.back();
		}
		if (!m_attenuation_constants.empty() && !m_attenuation_distance.empty() && m_attenuation_constants.size() == m_attenuation_distance.size())
		{
			for (int i = 1; i < m_attenuation_distance.size() - 1; i++)
			{
				if (distance > m_attenuation_distance[i - 1] && distance <= m_attenuation_distance[i])
				{
					return m_attenuation_constants[i];
				}
			}
		}

		return {1.f, 0.7f, 1.8f};
	}
	void RunTimeService::SetAttenuationConstants()
	{
		m_attenuation_constants = {

			{1.f, 0.7f, 1.8f},
			{1.f, 0.35f, 0.44f},
			{1.f, 0.22f, 0.2f},
			{1.f, 0.14f, 0.07f},
			{1.f, 0.09f, 0.032f},
			{1.f, 0.07f, 0.017f},
			{1.f, 0.045f, 0.0075f},
			{1.f, 0.027f, 0.0028f},
			{1.f, 0.022f, 0.0019f},
			{1.f, 0.014f, 0.0007f},
			{1.f, 0.007f, 0.0002f},
			{1.f, 0.0014f, 0.000007f}
		};

		m_attenuation_distance = { 7, 13, 20, 32, 50, 65, 100, 160, 200, 325, 600, 3250 };
	}
}

