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
				SQ_APP_ERROR("Class {} in function {} : Graphic service initializer is not referenced yet", __FILE__ , __FUNCTION__);
			}
			m_state_service = container->GetReference<Services::StateService>();
			if (!m_state_service)
			{
				SQ_APP_ERROR("Class {} in function {} : State service is not referenced yet", __FILE__ , __FUNCTION__);
			}
			m_gui_engine = container->GetReference<GUIEngine>();
			if (!m_gui_engine)
			{
				SQ_APP_ERROR("Class {} in function {} : GUI Engine is not referenced yet", __FILE__, __FUNCTION__);
			}
			m_scene_engine = container->GetReference<SceneEngine>();
			if (!m_scene_engine)
			{
				SQ_APP_ERROR("Class {} in function {} : Scene engine is not referenced yet", __FILE__, __FUNCTION__);
			}
			m_framebuffer_service = container->GetReference<Services::FramebufferService>();
			if (m_framebuffer_service)
			{
				m_framebuffer_service->BuildFrameBufferTexture();
			}
			else
			{
				SQ_APP_ERROR("Class {} in function {} : Framebuffer service is not referenced yet", __FILE__, __FUNCTION__);
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
					m_scene_engine->MoveCamera(event);
					m_state_service->RefreshProjectionMatrix();
				}
				

				m_framebuffer_service->BindFramebuffer();
				this->InitFrame();

				m_scene_engine->RenderSkybox(view_model_builder);
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


