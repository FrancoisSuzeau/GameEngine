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

		for (std::vector<std::shared_ptr<Renderers::IRenderer>>::iterator it = m_renderers.begin(); it != m_renderers.end(); it++)
		{
			if (it[0])
			{
				it[0]->Clean();
				it[0].reset();
			}
		}

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

		for (std::vector<std::shared_ptr<Renderers::IRenderer>>::iterator it = m_renderers.begin(); it != m_renderers.end(); it++)
		{
			if (it->get())
			{
				it->reset();
			}
		}
		m_renderers.clear();

		if (m_json_service)
		{
			m_json_service.reset();
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
			m_json_service = container->GetReference<Services::JsonService>();
			if(!m_json_service)
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Json service is not referenced yet", __FILE__, __FUNCTION__);
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
		if (m_views_map.at(type_view) && !m_renderers.empty())
		{
			m_views_map.at(type_view)->Render(m_renderers);
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

	void SceneViewModel::LoadScene()
	{
		if (m_json_service)
		{
			m_renderers = m_json_service->LoadScene();
			for (std::vector<std::shared_ptr<Renderers::IRenderer>>::iterator it = m_renderers.begin(); it != m_renderers.end(); it++)
			{
				it[0]->Construct();
			}
		}
	}

	void SceneViewModel::RenderGrid()
	{
		if (m_untextured_component && m_grid_renderer)
		{
			m_untextured_component->Render(m_grid_renderer);
		}
	}

	void SceneViewModel::OnCommand(Commands::ICommand* command)
	{
		{
			if (command)
			{
				m_command = std::unique_ptr<Commands::ICommand>(command);
				if (m_command)
				{
					m_command->SetRenderers(m_renderers);
					m_command->Execute();
					m_command.reset();
				}
			}
		};
	}
	
}

