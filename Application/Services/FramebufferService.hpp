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
#include <map>
#include <memory>
#include "StateService.hpp"
#include "ShaderService.hpp"

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

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

		void Render();

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
		std::shared_ptr<Services::StateService> m_state_service;

		unsigned int quadVAO = 0;
		unsigned int quadVBO = 0;

		float quadVertices[24];
		
		void Load();
		std::shared_ptr<Services::ShaderService> shader;
	};
}

#endif