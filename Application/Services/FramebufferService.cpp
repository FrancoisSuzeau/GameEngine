/******************************************************************************************************************************************/
// File : FramebufferService.cpp
// Purpose : Implementing service shader
/******************************************************************************************************************************************/
#include "FramebufferService.hpp"

namespace Services
{
	void FramebufferService::Init()
	{
		m_state_service = IoC::Container::Container::GetInstanceContainer()->GetReference<Services::StateService>();
		if (!m_state_service)
		{
			SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
		}

		m_texture_fb = 0;
		m_depth_fb = 0;
		m_depth_id = 0;
		m_texture_id = 0;
		m_render_fb = 0;		
		
	}
	void FramebufferService::DeInit()
	{
		if (m_texture_fb != 0)
		{
			glDeleteFramebuffers(1, &m_texture_fb);
			m_texture_fb = 0;
		}
		if (m_depth_fb != 0)
		{
			glDeleteFramebuffers(1, &m_depth_fb);
			m_depth_fb = 0;
		}
		if (m_texture_id != 0)
		{
			glDeleteTextures(1, &m_texture_id);
			m_texture_id = 0;
		}
		if (m_depth_id != 0)
		{
			glDeleteTextures(1, &m_depth_id);
			m_depth_id = 0;
		}
		if (m_render_fb != 0)
		{
			glDeleteRenderbuffers(1, &m_render_fb);
			m_render_fb = 0;
		}
		
		if (m_state_service)
		{
			m_state_service.reset();
		}

		SQ_APP_DEBUG("Framebuffer service terminated");

	}
	unsigned int FramebufferService::GetTextureId() const
	{
		return m_texture_id;
	}
	void FramebufferService::BuildFrameBufferDepth()
	{
		glGenTextures(1, &m_depth_id);

		if (m_depth_id != 0)
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_depth_id);

			if (glIsTexture(m_depth_id) == GL_TRUE)
			{
				for (unsigned int i = 0; i < 6; ++i)
				{
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, m_state_service->getWidth(), m_state_service->getWidth(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
				}
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

				glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depth_id, 0);

				glDrawBuffer(GL_NONE);
				glReadBuffer(GL_NONE);

				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			}
		}
	}
	void FramebufferService::BuildFrameBufferTexture()
	{
		this->SetFrameBufferDim();
		glGenFramebuffers(1, &m_depth_fb);
		if (m_depth_fb != 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_depth_fb);
			if (glIsFramebuffer(m_depth_fb) == GL_TRUE)
			{
				this->BuildFrameBufferDepth();
				this->CheckFramebufferStatus("Depth");
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
		}
		glGenFramebuffers(1, &m_texture_fb);
		if (m_texture_fb != 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_texture_fb);
			if (glIsFramebuffer(m_texture_fb) == GL_TRUE)
			{
				this->BuildTextureFB();
				this->BuildRenderFB();
				this->CheckFramebufferStatus("Texture");
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
		}
	}

	void FramebufferService::BindFramebuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_texture_fb);
	}

	void FramebufferService::UnbindFramebuffer()
	{
		glDisable(GL_DEPTH_TEST);
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
	void FramebufferService::BuildTextureFB()
	{
		glGenTextures(1, &m_texture_id);
		if (m_texture_id != 0)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_texture_id);
			if (glIsTexture(m_texture_id) == GL_TRUE)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_fb_width, m_fb_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture_id, 0);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			
		}
	}
	void FramebufferService::BuildRenderFB()
	{
		glGenRenderbuffers(1, &m_render_fb);
		if (m_render_fb != 0)
		{
			glBindRenderbuffer(GL_RENDERBUFFER, m_render_fb);
			if (glIsRenderbuffer(m_render_fb) == GL_TRUE)
			{
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_fb_width, m_fb_height);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_render_fb);
				glBindRenderbuffer(GL_RENDERBUFFER, 0);
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