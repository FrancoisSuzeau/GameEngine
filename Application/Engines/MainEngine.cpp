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
			std::shared_ptr<Services::GraphicInitializerService> graph_service_init = container->make<Services::GraphicInitializerService>();
			if (graph_service_init)
			{
				m_window = graph_service_init->GetSDLWindow();
			}
			m_state_service = container->make<Services::StateService>();
			m_gui_engine = container->make<GUIEngine>();
			m_scene_engine = container->make<SceneEngine>();
			m_framebuffer_service = container->make<Services::FramebufferService>();
			if (m_framebuffer_service)
			{
				m_framebuffer_service->BuildFrameBuffer();
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
				}
				

				m_framebuffer_service->BindFramebuffer();
				this->InitFrame();

				m_scene_engine->RenderScene(view_model_builder);

				m_framebuffer_service->UnbindFramebuffer();

				m_scene_engine->RenderFrameBuffer(view_model_builder, m_framebuffer_service->GetTextureId());

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


