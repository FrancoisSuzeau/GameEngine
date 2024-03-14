/******************************************************************************************************************************************/
// File : Canvas.hpp
// Purpose : The canvas view of the scene
/******************************************************************************************************************************************/
#ifndef CANVAS_H
#define CANVAS_H

#include "IView.hpp"
#include "Services/ShaderService.hpp"
#include "Renderers/Renderers.hpp"
#include "Draggable.hpp"
#include "../Transformer.hpp"
#include <map>
#include <iostream>

namespace Views
{
	class Canvas : public IView
	{
	public:
		Canvas();
		void Clean() override;
		void Render(std::vector<std::shared_ptr<Component::IComponent>> renderers, GLenum const mode, float const line_width) override;
		void TransformRenderers(std::vector<std::shared_ptr<Component::IComponent>> renderers) override;
		void DragRenderers(std::vector<std::shared_ptr<Component::IComponent>> renderers) override;
		void ConstructRenderer() override;
	private:
		std::shared_ptr<Services::ShaderService> m_shader_service;
		std::unique_ptr<Views::Draggable> m_draggable_component;
		std::map<Enums::RendererType, std::shared_ptr<Renderers::IRenderer>> m_renderers;
	};
}

#endif