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
#include "StateService.hpp"
#include "RunTimeService.hpp"

namespace Services {

	class FramebufferService : public IService
	{

	public:
		void Init() override;
		void DeInit() override;

		unsigned int GetTextureId(int id) const;
		unsigned int GetTextureId(bool horizontal) const;

		void BuildFrameBufferDepth();
		void BuildFrameBufferTexture();

		void BindFramebuffer();
		void BindFramebuffer(bool horizontal);
		void UnbindFramebuffer();

	private:
		unsigned int m_texture_fb;
		unsigned int m_texture_ids[2] = {0, 0};
		unsigned int m_ping_pong_fb[2] = { 0, 0 };
		unsigned int m_ping_pong_textures[2] = { 0, 0 };
		unsigned int m_render_fb;
		unsigned int m_depth_fb;
		unsigned int m_depth_id = 0;
		int m_fb_width;
		int m_fb_height;
		void SetFrameBufferDim();
		void BuildTextureFB();
		void BuildPingPongFB();
		void BuildRenderFB();
		void CheckFramebufferStatus(std::string const framebuffer_name);

		std::shared_ptr<Services::StateService> m_state_service;
		std::shared_ptr<Services::RunTimeService> m_runtime_service;

	};
}

#endif