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
			m_state_service = container->make<Services::StateService>();
		}
		this->SetFrameBufferDim();
		m_texture_fb = 0;
		m_texture_id = 0;
		m_render_fb = 0;

		float vertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
			// positions   // texCoords
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,

			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f, 1.0f
		};

		GLuint quadVBO = 0;
		GLuint quadVAO = 0;

		for (int i = 0; i < 24; i++)
		{
			quadVertices[i] = vertices[i];
		}

		
		
	}
	void FramebufferService::DeInit()
	{
		if (m_texture_fb != 0)
		{
			glDeleteFramebuffers(1, &m_texture_fb);
			m_texture_fb = 0;
		}
		if (m_texture_id != 0)
		{
			glDeleteTextures(1, &m_texture_id);
			m_texture_id = 0;
		}
		if (m_render_fb != 0)
		{
			glDeleteRenderbuffers(1, &m_render_fb);
			m_render_fb = 0;
		}
		glDeleteVertexArrays(1, &quadVAO);
		quadVAO = 0;
		glDeleteBuffers(1, &quadVBO);
		quadVBO = 0;
		
		SQ_APP_DEBUG("Framebuffer service terminated");

	}
	unsigned int FramebufferService::GetTextureId() const
	{
		return m_texture_id;
	}
	void FramebufferService::BuildFrameBuffer()
	{
		this->Load();
		glGenFramebuffers(1, &m_texture_fb);
		if (m_texture_fb != 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_texture_fb);
			if (glIsFramebuffer(m_texture_fb) == GL_TRUE)
			{
				this->BuildTextureFB();
				this->BuildRenderFB();
				this->CheckFramebufferStatus();
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
		}

		shader = IoC::Container::Container::GetInstanceContainer()->make<Services::ShaderService>();
	}

	void FramebufferService::BindFramebuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_texture_fb);
	}

	void FramebufferService::UnbindFramebuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FramebufferService::Render()
	{
		if (shader)
		{
			
			GLuint p = shader->GetProgramId(Constants::SCREEN_SHADER);
			glUseProgram(p);
			shader->setTexture(Constants::SCREEN_SHADER, "texture0", 0);
			glBindVertexArray(quadVAO);
			glBindTexture(GL_TEXTURE_2D, m_texture_id);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			
		}
		
	}
	
	void FramebufferService::SetFrameBufferDim()
	{
		m_fb_width = 2560;
		m_fb_height = 1440;
		/*if (m_state_service)
		{
			m_fb_width = m_state_service->getWidth() * 80 / 100;
			m_fb_height = m_state_service->getHeight() * 80 / 100;
		}*/
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
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

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
	void FramebufferService::CheckFramebufferStatus()
	{
		auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			SQ_APP_CRITICAL("Frame buffer is not complete || Status : {}", status);
		}
		else
		{
			SQ_APP_DEBUG("Framebuffer service initiated");
		}
		
	}
	void FramebufferService::Load()
	{
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	}
}