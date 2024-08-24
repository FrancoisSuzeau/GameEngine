/******************************************************************************************************************************************/
// File : MainEngine.cpp
// Purpose : Implementing the main engine
/******************************************************************************************************************************************/
#include "MainEngine.hpp"

namespace Engines
{
	MainEngine::~MainEngine()
	{
		if (m_state_service)
		{
			m_state_service.reset();
		}
		if (m_gui_engine)
		{
			m_gui_engine.reset();
		}
		if (m_scene_engine)
		{
			m_scene_engine.reset();
		}
		if (m_framebuffer_service)
		{
			m_framebuffer_service.reset();
		}

		if (m_runtime_service)
		{
			m_runtime_service.reset();
		}

		if (m_window)
		{
			m_window.reset();
		}
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
				graph_service_init.reset();
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
			
			m_scene_engine = container->GetReference<SceneEngine>();
			if (!m_scene_engine)
			{
				SQ_APP_ERROR("Class {} in function {} : Scene engine is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_framebuffer_service = container->GetReference<Services::FramebufferService>();
			if (!m_framebuffer_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Framebuffer service is not referenced yet", __FILE__, __FUNCTION__);
			}

			m_runtime_service = container->GetReference<Services::RunTimeService>();
			if (!m_runtime_service)
			{
				SQ_APP_ERROR("Class {} in function {} : Runtime service is not referenced yet", __FILE__, __FUNCTION__);

			}

			m_gui_engine = container->GetReference<GUIEngine>();
			if (!m_gui_engine)
			{
				SQ_APP_ERROR("Class {} in function {} : GUI Engine is not referenced yet", __FILE__, __FUNCTION__);
			}
			else
			{
				m_gui_engine->LoadConfigs();
				if (m_state_service->getConfigs() && m_framebuffer_service)
				{
					m_state_service->getConfigs()->GetMultiSample() ? m_framebuffer_service->BuildMultiSampleFrameBuffer() : m_framebuffer_service->BuildNormalFrameBuffer();
				}
			}
			
		}

	}

	void MainEngine::StartScreen(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		SDL_Event event;
		if (m_state_service && m_gui_engine && view_model_builder)
		{
			
			while (!m_state_service->getContinued() && !m_state_service->getExit())
			{

				this->FpsCalculation(Enums::BEGIN);
				while (SDL_PollEvent(&event))
				{
					ImGui_ImplSDL2_ProcessEvent(&event);
				}

				this->InitFrame();

				m_gui_engine->RenderMainMenuBar(view_model_builder);
				m_gui_engine->RenderGuiComponents(view_model_builder);

				this->EndFrame();

				this->FpsCalculation(Enums::END);
			}
		}
	}

	void MainEngine::LoadScreen(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		SDL_Event event;
		if (m_state_service && m_gui_engine && view_model_builder)
		{
			const int total_count_skybox = (const int) m_state_service->getConfigs()->GetAvailableSkybox().size();
			const int total_count_textures = (const int) m_state_service->getConfigs()->GetAvailableTextures().size();
			const int total_count_models = (const int)m_state_service->getConfigs()->GetAvailableModels().size();
			int progress = 0;

			for(int i = 0; i <= total_count_skybox; i++)
			{

				this->FpsCalculation(Enums::BEGIN);
				while (SDL_PollEvent(&event))
				{
					ImGui_ImplSDL2_ProcessEvent(&event);
				}

				this->InitFrame();

				if (i < total_count_skybox)
				{
					m_gui_engine->LoadAvailableSkyboxChoices(i);
				}
				m_gui_engine->RenderLoader(view_model_builder, progress);

				this->EndFrame();

				this->FpsCalculation(Enums::END);

				progress++;
			}

			progress--;

			for (int i = 0; i <= total_count_textures; i++)
			{

				this->FpsCalculation(Enums::BEGIN);
				while (SDL_PollEvent(&event))
				{
					ImGui_ImplSDL2_ProcessEvent(&event);
				}

				this->InitFrame();

				if (i < total_count_textures)
				{
					m_gui_engine->LoadAvailableTextures(i);
				}
				m_gui_engine->RenderLoader(view_model_builder, progress);

				this->EndFrame();

				this->FpsCalculation(Enums::END);

				progress++;
			}

			progress--;

			for (int i = 0; i <= total_count_skybox; i++)
			{

				this->FpsCalculation(Enums::BEGIN);
				while (SDL_PollEvent(&event))
				{
					ImGui_ImplSDL2_ProcessEvent(&event);
				}

				this->InitFrame();

				if (i < total_count_skybox)
				{
					m_gui_engine->LoadSkyboxCube(i);
				}
				m_gui_engine->RenderLoader(view_model_builder, progress);

				this->EndFrame();

				this->FpsCalculation(Enums::END);

				progress++;
			}

			progress--;

			for (int i = 0; i <= total_count_models; i++)
			{

				this->FpsCalculation(Enums::BEGIN);
				while (SDL_PollEvent(&event))
				{
					ImGui_ImplSDL2_ProcessEvent(&event);
				}

				this->InitFrame();

				if (i < total_count_models)
				{
					m_scene_engine->LoadAvailableModel(view_model_builder, i);
				}
				m_gui_engine->RenderLoader(view_model_builder, progress);

				this->EndFrame();

				this->FpsCalculation(Enums::END);

				progress++;
			}
			
		}
	}

	void MainEngine::MainLoop(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		SDL_Event event;
		if (m_state_service && m_gui_engine && m_scene_engine && m_framebuffer_service && view_model_builder)
		{
			m_scene_engine->UpdateAll();
			while (!m_state_service->getExit() && m_state_service->getContinued())
			{

				this->FpsCalculation(Enums::BEGIN);
				while (SDL_PollEvent(&event))
				{
					ImGui_ImplSDL2_ProcessEvent(&event);
					if (!m_state_service->getGuiOpen())
					{
						m_scene_engine->UpdateAll(event);
					}
				}
				
				m_runtime_service->RefreshScreen();

				if (m_state_service && m_state_service->getConfigs() && m_state_service->getConfigs()->GetDepth())
				{
					m_runtime_service->EnableDepthTest();
					m_runtime_service->SetPass(Enums::FramebufferType::DEPTHBUFFER);
					m_runtime_service->SetStencilPass(Enums::StencilType::STENCILBUFFERDISABLE);

					this->PassToFrameBuffer(view_model_builder);
				}


				if (m_state_service && m_state_service->getConfigs() && m_state_service->getConfigs()->GetMultiSample())
				{
					m_runtime_service->SetPass(Enums::FramebufferType::MULTISAMPLECOLORBUFFER);

					this->PassToFrameBuffer(view_model_builder);
				}

				m_runtime_service->SetPass(Enums::FramebufferType::NORMALCOLORBUFFER);
				
				this->PassToFrameBuffer(view_model_builder);

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

		if (m_runtime_service)
		{
			m_runtime_service->RefreshScreen();
			m_runtime_service->EnableDepthTest();
			m_runtime_service->EnableBlendCapture();
			m_runtime_service->SetMinusSrcAlpha();
		}

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
			SDL_GL_SwapWindow(m_window.get());
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
	void MainEngine::RenderStencilBuffer(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		if (m_runtime_service && m_scene_engine)
		{
			this->InitFrame();
			//Draw grid and skybox
			m_runtime_service->SetStencilPass(Enums::StencilType::STENCILBUFFERDISABLE);
			m_runtime_service->DisableWriteStencilBuffer();
			m_scene_engine->RefreshScene(view_model_builder);
			m_scene_engine->RenderScene(view_model_builder);
			//Pass to stencil buffer for scene component
			m_runtime_service->SetStencilPass(Enums::StencilType::STENCILBUFFERWRITE);
			m_runtime_service->StencilFuncToWrite();
			m_scene_engine->RefreshScene(view_model_builder);
			m_scene_engine->RenderScene(view_model_builder);
			//Read stencil buffer
			m_runtime_service->SetStencilPass(Enums::StencilType::STENCILBUFFERREAD);
			m_runtime_service->StencilFuncToRead();
			m_runtime_service->DisableDepthTest();
			m_scene_engine->RefreshScene(view_model_builder);
			m_scene_engine->RenderScene(view_model_builder);
			m_runtime_service->StencilFuncDisable();
		}
	}
	void MainEngine::PassToFrameBuffer(std::shared_ptr<Builders::ViewModelBuilder> view_model_builder)
	{
		if (m_runtime_service && m_framebuffer_service && m_scene_engine && m_state_service && m_state_service->getConfigs())
		{
			Enums::FramebufferType fb_type = m_runtime_service->GetPass();

			if (fb_type == Enums::FramebufferType::DEPTHBUFFER)
			{
				m_framebuffer_service->BindFramebuffer(fb_type);

				m_runtime_service->RefreshBuffers(GL_DEPTH_BUFFER_BIT);
				m_scene_engine->RefreshScene(view_model_builder);
				m_scene_engine->RenderScene(view_model_builder);

				m_framebuffer_service->UnbindFramebuffer();
			}

			if (fb_type == Enums::FramebufferType::NORMALCOLORBUFFER && !m_state_service->getConfigs()->GetMultiSample())
			{
				m_framebuffer_service->BindFramebuffer(fb_type);

				this->RenderStencilBuffer(view_model_builder);

				m_framebuffer_service->UnbindFramebuffer();

				m_scene_engine->RenderScreen();

			}

			if (fb_type == Enums::FramebufferType::MULTISAMPLECOLORBUFFER && m_state_service->getConfigs()->GetMultiSample())
			{
				m_framebuffer_service->BindFramebuffer(fb_type);

				this->RenderStencilBuffer(view_model_builder);

				m_framebuffer_service->BlitFramebuffer();

				m_framebuffer_service->UnbindFramebuffer();

			}

			if (fb_type == Enums::FramebufferType::NORMALCOLORBUFFER && m_state_service->getConfigs()->GetMultiSample())
			{
				m_scene_engine->RenderScreen();
			}
		}
	}
}


