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
		void RefreshColor();
		void RefreshBuffers();
		void EnableBlendCapture();
		void SetMinusSrcAlpha();

	private:
		std::shared_ptr<Services::OpenGLService> m_opengl_service;
		bool m_is_rendering_line;
	};
}

#endif