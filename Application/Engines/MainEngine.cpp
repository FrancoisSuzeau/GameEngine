/******************************************************************************************************************************************/
// File : MainEngine.cpp
// Purpose : Implementing the main engine
/******************************************************************************************************************************************/
#include "MainEngine.hpp"

namespace Engines
{
	MainEngine::~MainEngine()
	{
	}

	void MainEngine::Construct()
	{
		IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
		if (container)
		{
			std::shared_ptr<Services::GraphicInitializerService> graph_service_init = container->GetReference<Services::GraphicInitializerService>();
			if (graph_service_init)
			{
				m_window = graph_service_init->GetSDLWindow();
			}
			else
			{
				SQ_APP_ERROR("Graphic service initializer is not referenced yet");
			}
			m_state_service = container->GetReference<Services::StateService>();
			if (!m_state_service)
			{
				SQ_APP_ERROR("State service is not referenced yet");
			}
			m_gui_engine = container->GetReference<GUIEngine>();
			if (!m_gui_engine)
			{
				SQ_APP_ERROR("GUI Engine is not referenced yet");
			}
			m_scene_engine = container->GetReference<SceneEngine>();
			if (!m_scene_engine)
			{
				SQ_APP_ERROR("Scene engine is not referenced yet");
			}
			m_framebuffer_service = container->GetReference<Services::FramebufferService>();
			if (m_framebuffer_service)
			{
				m_framebuffer_service->BuildFrameBuffer();
			}
			else
			{
				SQ_APP_ERROR("Framebuffer service is not referenced yet");
			}

			std::shared_ptr<Services::TextureLoaderService> tex = container->GetReference<Services::TextureLoaderService>();
			if (tex)
			{
				
				std::vector<std::string> paths;
				paths.push_back("resources/skybox/right.jpg");
				paths.push_back("resources/skybox/left.jpg");
				paths.push_back("resources/skybox/top.jpg");
				paths.push_back("resources/skybox/bottom.jpg");
				paths.push_back("resources/skybox/front.jpg");
				paths.push_back("resources/skybox/back.jpg");
				skybox_texture = tex->LoadTexture(paths);
			}
			else
			{
				SQ_APP_ERROR("Texture service loader is not referenced yet");
			}

			
		}


	}

	void MainEngine::MainLoop(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		SDL_Event event;

		if (m_state_service && m_gui_engine && m_scene_engine && m_framebuffer_service)
		{
			while (!m_state_service->getExit())
			{

				this->FpsCalculation(Enums::BEGIN);
				while (SDL_PollEvent(&event))
				{
					// Keep this to let IMGUI capture event
					m_scene_engine->MoveCamera(event);
				}
				

				//m_framebuffer_service->BindFramebuffer();
				this->InitFrame();

				m_scene_engine->RenderScene(view_model_builder);
				//m_scene_engine->RenderSkybox(view_model_builder, skybox_texture);

				/*m_framebuffer_service->UnbindFramebuffer();

				m_scene_engine->RenderFrameBuffer(view_model_builder, m_framebuffer_service->GetTextureId());*/

				m_gui_engine->RenderMainMenuBar(view_model_builder);
				m_gui_engine->RenderGuiComponents(view_model_builder);

				//ImGui::ShowDemoWindow();

				this->EndFrame();

				this->FpsCalculation(Enums::END);
			}
		}
	}

	void MainEngine::InitFrame()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		if (m_gui_engine)
		{
			m_gui_engine->InitFrame();
		}
	}

	void MainEngine::EndFrame()
	{
		if (m_gui_engine && m_window)
		{
			m_gui_engine->EndFrame();
			SDL_GL_SwapWindow(m_window);
		}
	}

	void MainEngine::FpsCalculation(Enums::EngineEnum ee)
	{
		switch (ee)
		{
		case Enums::BEGIN:
			start_loop = SDL_GetTicks();
			break;

		case Enums::END:
			end_loop = SDL_GetTicks();
			time_past = end_loop - start_loop;
			if (time_past < frame_rate)
			{
				SDL_Delay(frame_rate - time_past);
			}
			frame_rate = 1000 / 60;
			break;

		default:
			break;
		}
	}
}


