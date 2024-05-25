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
		m_bright_fb = 0;
		m_render_fb = 0;		
		m_depth_map_fb = 0;
		m_depth_map_texture_id = 0;
		m_color_multisample_fb = 0;
		m_color_texture_id = 0;
		m_bright_texture_id = 0;

		m_attachments[0] = GL_COLOR_ATTACHMENT0;
		m_attachments[1] = GL_COLOR_ATTACHMENT1;
		
	}
	void FramebufferService::DeInit()
	{	
		this->ClearFramebuffer();
		SQ_APP_DEBUG("Framebuffer service terminated");

	}
	unsigned int FramebufferService::GetTextureId(int id) const
	{
		switch (id)
		{
		case 0:
			return m_color_texture_id;
			break;
		case 1:
			return m_bright_texture_id;
			break;
		default:
			return 0;
			break;
		}
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
				m_runtime_service->DeleteTexture(m_color_multisample_texture_ids[i]);
			}
			m_runtime_service->DeleteTexture(m_color_texture_id);
			m_runtime_service->DeleteTexture(m_bright_texture_id);
			m_runtime_service->DeleteTexture(m_depth_map_texture_id);

			m_runtime_service->DeleteRenderBuffer(m_render_fb);

			m_runtime_service->DeleteBuffer(m_color_fb);
			m_runtime_service->DeleteBuffer(m_depth_map_fb);
			m_runtime_service->DeleteBuffer(m_color_multisample_fb);
			m_runtime_service->DeleteBuffer(m_bright_fb);
		}
	}
	
	void FramebufferService::BuildDepthMapFramebuffer()
	{
		glGenFramebuffers(1, &m_depth_map_fb);
		if (m_depth_map_fb != 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_depth_map_fb);
			if (glIsFramebuffer(m_depth_map_fb) == GL_TRUE)
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

				this->CheckFramebufferStatus("Depth");

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
		}
	}
	void FramebufferService::BuildNormalFrameBuffer()
	{
		this->SetFrameBufferDim();

		this->BuildDepthMapFramebuffer();

		glGenFramebuffers(1, &m_color_fb);
		if (m_color_fb != 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_color_fb);
			if (glIsFramebuffer(m_color_fb) == GL_TRUE)
			{
				this->BuildScreenTexture();
				this->BuildNormalRenderFB();
				this->CheckFramebufferStatus("Screen");
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
		}

		this->BuildPingPongFramebuffers();
	}

	void FramebufferService::BuildMultiSampleFrameBuffer()
	{
		this->SetFrameBufferDim();

		this->BuildDepthMapFramebuffer();

		glGenFramebuffers(1, &m_color_multisample_fb);
		if (m_color_multisample_fb != 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_color_multisample_fb);
			if (glIsFramebuffer(m_color_multisample_fb) == GL_TRUE)
			{
				this->BuildMultisampleColorTextures();
				this->BuildMultiSampleRenderFB();
				this->CheckFramebufferStatus("Multi-sample");

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}

		}

		this->BuildScreenFramebuffer();

		this->BuildBrighFramebuffer();

		this->BuildPingPongFramebuffers();


	}

	void FramebufferService::BindFramebuffer(Enums::FramebufferType fb_type)
	{
		switch (fb_type)
		{
		case Enums::FramebufferType::BIGHTFRAMEBUFFER:
			glBindFramebuffer(GL_FRAMEBUFFER, m_bright_fb);
			break;
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
		glReadBuffer(m_attachments[0]);
		glDrawBuffers(2, m_attachments);
		glBlitFramebuffer(0, 0, m_fb_width, m_fb_height, 0, 0, m_fb_width, m_fb_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_color_multisample_fb);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_bright_fb);
		glReadBuffer(m_attachments[1]);
		glDrawBuffers(2, m_attachments);
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
	void FramebufferService::BuildScreenTexture()
	{
		glGenTextures(1, &m_color_texture_id);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_color_texture_id);
		if (glIsTexture(m_color_texture_id) == GL_TRUE)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_fb_width, m_fb_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_texture_id, 0);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glGenTextures(1, &m_bright_texture_id);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_bright_texture_id);
		if (glIsTexture(m_bright_texture_id) == GL_TRUE)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_fb_width, m_fb_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_bright_texture_id, 0);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
	void FramebufferService::BuildScreenFramebuffer()
	{
		glGenFramebuffers(1, &m_color_fb);
		if (m_color_fb != 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_color_fb);
			if (glIsFramebuffer(m_color_fb) == GL_TRUE)
			{
				glGenTextures(1, &m_color_texture_id);
				glBindTexture(GL_TEXTURE_2D, m_color_texture_id);
				if (glIsTexture(m_color_texture_id) == GL_TRUE)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_fb_width, m_fb_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_texture_id, 0);
				}

				this->CheckFramebufferStatus("Screen");

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
		}
		
	}
	void FramebufferService::BuildBrighFramebuffer()
	{
		glGenFramebuffers(1, &m_bright_fb);
		if (m_bright_fb != 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_bright_fb);
			if (glIsFramebuffer(m_bright_fb) == GL_TRUE)
			{
				glGenTextures(1, &m_bright_texture_id);
				glBindTexture(GL_TEXTURE_2D, m_bright_texture_id);
				if (glIsTexture(m_bright_texture_id) == GL_TRUE)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_fb_width, m_fb_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_bright_texture_id, 0);
				}

				this->CheckFramebufferStatus("Bright");

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
		}
	}
	void FramebufferService::BuildMultisampleColorTextures()
	{
		glGenTextures(2, m_color_multisample_texture_ids);
		for (int i = 0; i < 2; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_color_multisample_texture_ids[i]);
			if (glIsTexture(m_color_multisample_texture_ids[i]) == GL_TRUE)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, m_fb_width, m_fb_height, GL_TRUE);
				glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D_MULTISAMPLE, m_color_multisample_texture_ids[i], 0);

				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}
	}
	void FramebufferService::BuildPingPongFramebuffers()
	{
		glGenFramebuffers(2, m_ping_pong_fb);

		glGenTextures(2, m_ping_pong_textures_ids);

		for (unsigned int i = 0; i < 2; i++)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_ping_pong_fb[i]);
			if (glIsFramebuffer(m_ping_pong_fb[i]) == GL_TRUE)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_ping_pong_textures_ids[i]);

				if (glIsTexture(m_ping_pong_textures_ids[i]) == GL_TRUE)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_fb_width, m_fb_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ping_pong_textures_ids[i], 0);

					glActiveTexture(GL_TEXTURE0 + i);
					glBindTexture(GL_TEXTURE_2D, 0);
				}
				
				this->CheckFramebufferStatus("Ping-pong " + std::to_string(i));

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
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
				glDrawBuffers(2, m_attachments);

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
				glDrawBuffers(2, m_attachments);
			}
		}
	}
	void FramebufferService::CheckFramebufferStatus(std::string const framebuffer_name)
	{
		auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			switch (status)
			{
			case GL_FRAMEBUFFER_UNDEFINED:
				SQ_APP_CRITICAL("{} framebuffer is undefined", framebuffer_name);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				SQ_APP_CRITICAL("{} framebuffer have incomplete attachement", framebuffer_name);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
				SQ_APP_CRITICAL("{} framebuffer have incomplete missing attachement", framebuffer_name);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
				SQ_APP_CRITICAL("{} framebuffer have incomplete draw buffer", framebuffer_name);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
				SQ_APP_CRITICAL("{} framebuffer have incomplete read buffer", framebuffer_name);
				break;
			case GL_FRAMEBUFFER_UNSUPPORTED:
				SQ_APP_CRITICAL("{} framebuffer is unsupported", framebuffer_name);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
				SQ_APP_CRITICAL("{} framebuffer have incomplete multi-sample", framebuffer_name);
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
				SQ_APP_CRITICAL("{} framebuffer have incomplete layer targets", framebuffer_name);
				break;
			default:
				SQ_APP_CRITICAL("{} framebuffer error undetermined", framebuffer_name);
				break;
			}
			
		}
		else
		{
			SQ_APP_DEBUG("{} framebuffer ready", framebuffer_name);
		}
		
	}
}