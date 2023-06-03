/******************************************************************************************************************************************/
// File : Engine.cpp
// Purpose : Implementing the main engine
/******************************************************************************************************************************************/
#include "Engine.hpp"

using namespace Engines;

Engine::~Engine()
{
}

void Engine::Construct()
{
    IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
    std::shared_ptr<Services::GraphicInitializerService> graph_service_init = container->make<Services::GraphicInitializerService>();

    m_gui_engine = container->make<GUIEngine>();
    m_window = graph_service_init->GetSDLWindow();
    m_width = graph_service_init->GetWidth();
    m_height = graph_service_init->GetHeight();

    graph_service_init.reset();
}

void Engine::MainLoop()
{
    bool exit = false;
    SDL_Event event;

    while (!exit)
    {
        
        this->FpsCalculation(Enums::BEGIN);

        while (SDL_PollEvent(&event))
        {
            this->InitFrame();

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            m_gui_engine->RenderExitButton(exit, m_width, m_height);

            this->EndFrame();
        }

        this->FpsCalculation(Enums::END);
    }
}

void Engine::InitFrame()
{
    m_gui_engine->InitFrame();
}

void Engine::EndFrame()
{
    m_gui_engine->EndFrame();
    SDL_GL_SwapWindow(m_window);
}

void Engine::FpsCalculation(Enums::EngineEnum ee)
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
