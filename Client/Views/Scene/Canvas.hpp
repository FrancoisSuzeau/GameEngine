/******************************************************************************************************************************************/
// File : Canvas.hpp
// Purpose : The canvas view of the scene
/******************************************************************************************************************************************/
#ifndef CANVAS_H
#define CANVAS_H

#include "IView.hpp"
#include "Services/ShaderService.hpp"
#include "Container/Container.hpp"
#include "Constants/NumberConstants.hpp"
#include "Renderers/Renderers.hpp"

namespace Views
{
	class Canvas : public IView
	{
	public:
		Canvas();
		void Clean() override;
		void Render() override;
	private:
		std::shared_ptr<Services::ShaderService> m_shader_service;
		std::unique_ptr<Renderers::Triangle> m_triangle;
	};
}

#endif