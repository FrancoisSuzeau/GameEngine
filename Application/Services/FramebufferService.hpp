/******************************************************************************************************************************************/
// File : FramebufferService.hpp
// Purpose : A service for communicate between loader and shader
/******************************************************************************************************************************************/
#ifndef FRAMEBUFFERSERVICE_H
#define FRAMEBUFFERSERVICE_H

#include "IService.hpp"
#include "Logger.hpp"
#include <GL/glew.h>
#include <iostream>

namespace Services {

	class FramebufferService : public IService
	{

	public:
		void Init() override;
		void DeInit() override;

		unsigned int GetTextureId() const;

		void BuildFrameBuffer();

		void BindFramebuffer();
		void UnbindFramebuffer();

	private:
		unsigned int m_texture_fb;
		unsigned int m_texture_id;
		unsigned int m_render_fb;
		int m_fb_width;
		int m_fb_height;
		void SetFrameBufferDim();
		void BuildTextureFB();
		void BuildRenderFB();
		void CheckFramebufferStatus();

	};
}

#endif