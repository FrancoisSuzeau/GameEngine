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
	}
	void SceneViewModel::Construct()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			std::shared_ptr<Views::Canvas> component_1 = container->GetReference<Views::Canvas>();

			if (component_1)
			{
				component_1->SetParent(this);
				m_views_map.insert_or_assign(Constants::CANVAS, component_1);
				component_1.reset();
			}
			else
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Canvas component is not referenced yet", __FILE__, __FUNCTION__);
			}

			std::shared_ptr<Renderers::Grid> grid = std::make_shared<Renderers::Grid>(48);
			if (grid)
			{
				grid->Construct();
				m_renderers.push_back(grid);
				grid.reset();
			}

			

			std::shared_ptr<Renderers::Triangle>triangle = std::make_shared<Renderers::Triangle>();
			if (triangle)
			{
				triangle->Construct();
				m_renderers.push_back(triangle);
				triangle.reset();
			}

			std::shared_ptr<Renderers::Square> square = std::make_shared<Renderers::Square>();
			if (square)
			{
				square->Construct();
				m_renderers.push_back(square);
				square.reset();
			}

			m_json_service = container->GetReference<Services::JsonService>();
			if (m_json_service)
			{
				m_json_service->SetScene(m_renderers);
			}
			else
			{
				SQ_CLIENT_ERROR("Class {} in function {} : Json service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_textured_component = std::make_unique<Component::TexturedComponent>();
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

		}	
	}

	void SceneViewModel::RenderViews(std::string const type_view)
	{
		if (m_views_map.at(type_view))
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

	void SceneViewModel::OnCommand(Commands::ICommand* command)
	{
		if (command)
		{
			m_command = std::unique_ptr<Commands::ICommand>(command);
			if (m_command)
			{
				m_command->Execute();
				m_command.reset();
			}
		}
	}
}

