/******************************************************************************************************************************************/
// File : RunTimeService.hpp
// Purpose : A service for communicate between loader and shader
/******************************************************************************************************************************************/
#ifndef RUNTIMESERVICE_H
#define RUNTIMESERVICE_H

#include "IService.hpp"
#include "Logger.hpp"
#include "Container/Container.hpp"
#include "OpenGLService.hpp"
#include "Enums/EngineEnum.hpp"


#include <iostream>
#include <map>
#include <memory>


namespace Services {

	class RunTimeService : public IService
	{

	public:
		RunTimeService();
		void Init() override;
		void DeInit() override;

		void RenderingInLine(float const line_width);
		void RenderingInFill();
		void LequalDepth();
		void LessDepth();
		bool IsRenderingLine() const;
		void RefreshScreen();
		void RefreshColor(glm::vec4 const colors);
		void RefreshBuffers(GLbitfield const masks);
		void EnableBlendCapture();
		void EnableDepthTest();
		void DisableDepthTest();
		void SetMinusSrcAlpha();
		void DeleteTexture(unsigned int &texture_id);
		void DeleteBuffer(unsigned int &buffer_id);
		void DeleteRenderBuffer(unsigned int &render_buffer_id);
		void DisableWriteStencilBuffer();
		void StencilFuncToWrite();
		void StencilFuncToRead();
		void StencilFuncDisable();
		void SetPass(Enums::FramebufferType fb_type);
		void SetStencilPass(Enums::StencilType stencyl_type);
		Enums::FramebufferType GetPass() const;
		Enums::StencilType GetStencilPass() const;

	private:
		std::shared_ptr<Services::OpenGLService> m_opengl_service;
		bool m_is_rendering_line;
		Enums::FramebufferType m_fb_type;
		Enums::StencilType m_stencil_type;
	};
}

#endif