/******************************************************************************************************************************************/
// File : FramebufferService.cpp
// Purpose : Implementing service shader
/******************************************************************************************************************************************/
#include "FramebufferService.hpp"

namespace Services
{
	void FramebufferService::Init()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_state_service = container->GetReference<Services::StateService>();
			if (!m_state_service)
			{
				SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_runtime_service = container->GetReference<RunTimeService>();
			if (!m_runtime_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Run time service is not referenced yet", __FILE__, __FUNCTION__);
			}
		}
		

		m_color_fb = 0;
		m_render_fb = 0;		
		m_depth_map_fb = 0;
		m_depth_map_texture_id = 0;
		m_color_multisample_fb = 0;
		m_color_multisample_texture = 0;
		
	}
	void FramebufferService::DeInit()
	{	
		this->ClearFramebuffer();
		SQ_APP_DEBUG("Framebuffer service terminated");

	}
	unsigned int FramebufferService::GetTextureId(int id) const
	{
		return m_color_texture_ids[id];
		
	}
	unsigned int FramebufferService::GetTextureId() const
	{
		return m_color_texture_id;
	}
	unsigned int FramebufferService::GetTextureId(bool horizontal) const
	{
		return m_ping_pong_textures_ids[horizontal];
		
	}
	unsigned int FramebufferService::GetDephtTextureId() const
	{
		return m_depth_map_texture_id;
	}

	void FramebufferService::ClearFramebuffer()
	{
		if (m_runtime_service)
		{
			for (int i = 0; i < 2; i++)
			{
				m_runtime_service->DeleteTexture(m_ping_pong_textures_ids[i]);
				m_runtime_service->DeleteTexture(m_color_texture_ids[i]);
			}

			m_runtime_service->DeleteTexture(m_color_multisample_texture);
			m_runtime_service->DeleteTexture(m_color_texture_id);

			m_runtime_service->DeleteRenderBuffer(m_render_fb);
			m_runtime_service->DeleteBuffer(m_color_fb);
			m_runtime_service->DeleteBuffer(m_depth_map_fb);
			m_runtime_service->DeleteTexture(m_depth_map_texture_id);
		}
	}
	
	void FramebufferService::BuildDepthMapTexture()
	{
		glGenTextures(1, &m_depth_map_texture_id);

		if (m_depth_map_texture_id != 0)
		{
			glBindTexture(GL_TEXTURE_2D, m_depth_map_texture_id);

			if (glIsTexture(m_depth_map_texture_id) == GL_TRUE)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
					m_fb_width, m_fb_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_map_texture_id, 0);

				glDrawBuffer(GL_NONE);
				glReadBuffer(GL_NONE);

				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}
	}
	void FramebufferService::BuildNormalFrameBuffer()
	{
		this->SetFrameBufferDim();

		glGenFramebuffers(1, &m_depth_map_fb);
		if (m_depth_map_fb != 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_depth_map_fb);
			if (glIsFramebuffer(m_depth_map_fb) == GL_TRUE)
			{
				this->BuildDepthMapTexture();
				this->CheckFramebufferStatus("Depth framebuffer");

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
		}

		glGenFramebuffers(1, &m_color_fb);
		if (m_color_fb != 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_color_fb);
			if (glIsFramebuffer(m_color_fb) == GL_TRUE)
			{
				this->BuildScreenTexture(Enums::FramebufferType::NORMALCOLORBUFFER);
				this->BuildNormalRenderFB();
				this->CheckFramebufferStatus("Normal Color framebuffer");
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
		}

		this->BuildPingPongTexture();
	}

	void FramebufferService::BuildMultiSampleFrameBuffer()
	{
		this->SetFrameBufferDim();

		glGenFramebuffers(1, &m_depth_map_fb);
		if (m_depth_map_fb != 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_depth_map_fb);
			if (glIsFramebuffer(m_depth_map_fb) == GL_TRUE)
			{
				this->BuildDepthMapTexture();
				this->CheckFramebufferStatus("Depth framebuffer");

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
		}

		glGenFramebuffers(1, &m_color_multisample_fb);
		if (m_color_multisample_fb != 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_color_multisample_fb);
			if (glIsFramebuffer(m_color_multisample_fb) == GL_TRUE)
			{
				this->BuildMultisampleColorTexture();
				this->BuildMultiSampleRenderFB();
				this->CheckFramebufferStatus("Multisample frame buffer");

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}

		}

		glGenFramebuffers(1, &m_color_fb);
		if (m_color_fb != 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_color_fb);
			if (glIsFramebuffer(m_color_fb) == GL_TRUE)
			{
				this->BuildScreenTexture(Enums::FramebufferType::MULTISAMPLECOLORBUFFER);
				this->CheckFramebufferStatus("Normal Color framebuffer");

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
		}

	}

	void FramebufferService::BindFramebuffer(Enums::FramebufferType fb_type)
	{
		switch (fb_type)
		{
		case Enums::FramebufferType::NORMALCOLORBUFFER:
			glBindFramebuffer(GL_FRAMEBUFFER, m_color_fb);
			break;
		case Enums::FramebufferType::MULTISAMPLECOLORBUFFER:
			glBindFramebuffer(GL_FRAMEBUFFER, m_color_multisample_fb);
			break;
		case Enums::FramebufferType::DEPTHBUFFER:
			glBindFramebuffer(GL_FRAMEBUFFER, m_depth_map_fb);
			break;
		default:
			break;
		}
	}

	void FramebufferService::BlitFramebuffer()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_color_multisample_fb);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_color_fb);
		glBlitFramebuffer(0, 0, m_fb_width, m_fb_height, 0, 0, m_fb_width, m_fb_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	}

	void FramebufferService::BindFramebuffer(bool horizontal)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_ping_pong_fb[horizontal]);
	}

	void FramebufferService::UnbindFramebuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	void FramebufferService::SetFrameBufferDim()
	{
		if (m_state_service)
		{
			m_fb_width = m_state_service->getWidth();
			m_fb_height = m_state_service->getHeight();
		}
	}
	void FramebufferService::BuildScreenTexture(Enums::FramebufferType type)
	{
		switch (type)
		{
		case Enums::NORMALCOLORBUFFER:
			glGenTextures(2, m_color_texture_ids);
			for (int i = 0; i < 2; i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_color_texture_ids[i]);
				if (glIsTexture(m_color_texture_ids[i]) == GL_TRUE)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_fb_width, m_fb_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_color_texture_ids[i], 0);

					glActiveTexture(GL_TEXTURE0 + i);
					glBindTexture(GL_TEXTURE_2D, 0);
				}
			}
			break;
		case Enums::MULTISAMPLECOLORBUFFER:
			glGenTextures(1, &m_color_texture_id);
			glBindTexture(GL_TEXTURE_2D, m_color_texture_id);
			if (glIsTexture(m_color_texture_id) == GL_TRUE)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_fb_width, m_fb_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_texture_id, 0);
			}
			break;
		case Enums::DEPTHBUFFER:
		default:
			break;
		}
	}
	void FramebufferService::BuildMultisampleColorTexture()
	{
		glGenTextures(1, &m_color_multisample_texture);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_color_multisample_texture);
		if (glIsTexture(m_color_multisample_texture) == GL_TRUE)
		{
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, m_fb_width, m_fb_height, GL_TRUE);
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_color_multisample_texture, 0);
		}
	}
	void FramebufferService::BuildPingPongTexture()
	{
		glGenFramebuffers(2, m_ping_pong_fb);

		glGenTextures(2, m_ping_pong_textures_ids);

		for (unsigned int i = 0; i < 2; i++)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_ping_pong_fb[i]);

			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_ping_pong_textures_ids[i]);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_fb_width, m_fb_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ping_pong_textures_ids[i], 0);

			this->CheckFramebufferStatus("Normal Ping-pong framebuffer");

			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
	
	
	void FramebufferService::BuildNormalRenderFB()
	{
		glGenRenderbuffers(1, &m_render_fb);
		if (m_render_fb != 0)
		{
			glBindRenderbuffer(GL_RENDERBUFFER, m_render_fb);
			if (glIsRenderbuffer(m_render_fb) == GL_TRUE)
			{
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_fb_width, m_fb_height);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_render_fb);

				glBindRenderbuffer(GL_RENDERBUFFER, 0);

				// Tell OpenGL we need to draw to both attachments
				unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
				glDrawBuffers(2, attachments);
			}
		}
	}
	void FramebufferService::BuildMultiSampleRenderFB()
	{
		glGenRenderbuffers(1, &m_render_fb);
		if (m_render_fb != 0)
		{
			glBindRenderbuffer(GL_RENDERBUFFER, m_render_fb);
			if (glIsRenderbuffer(m_render_fb) == GL_TRUE)
			{
				glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, m_fb_width, m_fb_height);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_render_fb);

				glBindRenderbuffer(GL_RENDERBUFFER, 0);

				// Tell OpenGL we need to draw to both attachments
				unsigned int attachments[1] = { GL_COLOR_ATTACHMENT0};
				glDrawBuffers(1, attachments);
			}
		}
	}
	void FramebufferService::CheckFramebufferStatus(std::string const framebuffer_name)
	{
		auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			SQ_APP_CRITICAL("{} frame buffer is not complete || Status : {}", framebuffer_name, status);
		}
		else
		{
			SQ_APP_DEBUG("{} framebuffer ready", framebuffer_name);
		}
		
	}
}