/******************************************************************************************************************************************/
// File : MainEngine.cpp
// Purpose : Implementing the main engine
/******************************************************************************************************************************************/
#include "MainEngine.hpp"

using namespace Engines;

MainEngine::~MainEngine()
{
}

void MainEngine::Construct()
{
    IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
    std::shared_ptr<Services::GraphicInitializerService> graph_service_init = container->make<Services::GraphicInitializerService>();
    m_state_service = container->make<Services::StateService>();
    m_gui_engine = container->make<GUIEngine>();
    m_shader_loader = container->make<Services::ShaderLoaderService>();
    m_window = graph_service_init->GetSDLWindow();
    GLuint program_id = m_shader_loader->loadShader("sphere", Enums::NORMAL);
    graph_service_init.reset();
}

void MainEngine::MainLoop()
{
    SDL_Event event;
   
    while (!m_state_service->getExit())
    {
        
        this->FpsCalculation(Enums::BEGIN);

        while (SDL_PollEvent(&event))
        {
            this->InitFrame();

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            m_gui_engine->Render();
            //ImGui::ShowDemoWindow();

            this->EndFrame();
        }

        this->FpsCalculation(Enums::END);
    }
}

void MainEngine::InitFrame()
{
    m_gui_engine->InitFrame();
}

void MainEngine::EndFrame()
{
    m_gui_engine->EndFrame();
    SDL_GL_SwapWindow(m_window);
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
