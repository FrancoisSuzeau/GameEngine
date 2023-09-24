/******************************************************************************************************************************************/
// File : SceneViewModel.hpp
// Purpose : The scene view model of the application
/******************************************************************************************************************************************/
#ifndef SCENEVIEWMODEL_H
#define SCENEVIEWMODEL_H

#include "IViewModel.hpp"
#include "../Views/Views.hpp"
#include "Container/Container.hpp"


#include <iostream>
#include <map>

namespace ViewModels
{
	class SceneViewModel : public IViewModel
	{

	public:
		void Construct() override;
		void DeConstruct() override;
		void RenderViews(std::string const type_view) override;
		void RenderFrameBuffer(unsigned int fb_texture_id) override;
		void OnCommand(Commands::ICommand* command) override;

	private:
		std::map<std::string, std::shared_ptr<Views::IView>> m_views_map;
		std::vector < std::shared_ptr<Renderers::IRenderer> > m_renderers;
		std::unique_ptr<Component::TexturedComponent> m_framebuffer_component;
		std::shared_ptr<Renderers::ScreenRenderer> m_framebuffer_renderer;
	};
}

#endif