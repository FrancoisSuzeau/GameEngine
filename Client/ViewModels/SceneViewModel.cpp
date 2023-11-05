/******************************************************************************************************************************************/
// File : SceneViewModel.cpp
// Purpose : Implementing the GUI view model
/******************************************************************************************************************************************/

#include "SceneViewModel.hpp"

namespace ViewModels
{
	SceneViewModel::~SceneViewModel()
	{
		for (std::map<std::string, std::shared_ptr<Views::IView>>::iterator it = m_views_map.begin(); it != m_views_map.end(); it++)
		{
			if (it->second)
			{
				it->second->Clean();
				it->second.reset();
			}
		}
		m_views_map.clear();

		if (m_textured_component)
		{
			m_textured_component->Clean();
			m_textured_component.reset();
		}

		if (m_untextured_component)
		{
			m_untextured_component->Clean();
			m_untextured_component.reset();
		}

		if (m_framebuffer_renderer)
		{
			m_framebuffer_renderer->Clean();
			m_framebuffer_renderer.reset();
		}

		if (m_skybox_renderer)
		{
			m_skybox_renderer->Clean();
			m_skybox_renderer.reset();
		}

		if (m_grid_renderer)
		{
			m_grid_renderer->Clean();
			m_grid_renderer.reset();
		}
	}
	void SceneViewModel::Construct()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			m_state_service = container->GetReference<Services::StateService>();
			if (!m_state_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__, __FUNCTION__);
			}
			
			std::shared_ptr<Views::Canvas> canvas = container->GetReference<Views::Canvas>();
			if (canvas)
			{
				canvas->SetParent(this);
				m_views_map.insert_or_assign(Constants::CANVAS, canvas);
				canvas.reset();
			}
			else
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Canvas component is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_textured_component = std::make_unique<Component::TexturedComponent>();
			m_untextured_component = std::make_unique<Component::ComponentBase>();
			m_framebuffer_renderer = std::make_shared<Renderers::ScreenRenderer>();
			if (m_framebuffer_renderer)
			{
				m_framebuffer_renderer->Construct();
			}

			m_skybox_renderer = std::make_shared<Renderers::Skybox>();
			if (m_skybox_renderer)
			{
				m_skybox_renderer->Construct();
			}

			m_grid_renderer = std::make_shared<Renderers::Grid>(48);
			if (m_grid_renderer)
			{
				m_grid_renderer->Construct();
			}

		}
	}

	void SceneViewModel::RenderViews(std::string const type_view)
	{
		if (m_state_service)
		{
			std::vector<std::shared_ptr<Renderers::IRenderer>> renderers = m_state_service->getRenderers();
			if (m_views_map.at(type_view) && !renderers.empty())
			{
				m_views_map.at(type_view)->Render(renderers);
			}
		}
	}
	void SceneViewModel::RenderFrameBuffer(unsigned int fb_texture_id)
	{
		if (m_textured_component && m_framebuffer_renderer)
		{
			m_framebuffer_renderer->SetTextureID(fb_texture_id);
			m_textured_component->Render(m_framebuffer_renderer);
		}
	}
	void SceneViewModel::RenderSkybox(unsigned int skybox_texture_id)
	{
		if (m_textured_component && m_skybox_renderer)
		{
			m_skybox_renderer->SetTextureID(skybox_texture_id);
			m_textured_component->Render(m_skybox_renderer);
		}
	}

	void SceneViewModel::RenderGrid()
	{
		if (m_untextured_component && m_grid_renderer)
		{
			m_untextured_component->Render(m_grid_renderer);
		}
	}
	
}

