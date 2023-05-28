/******************************************************************************************************************************************/
// File : Engine.cpp
// Purpose : Implementing the main engine
/******************************************************************************************************************************************/
#include "Engine.hpp"

using namespace Engines;

Engine::Engine(SDL_Window* window) : m_window(window)
{
}

Engine::~Engine()
{
}

void Engine::MainLoop()
{

    while (true)
    {
        this->FpsCalculation(Enums::BEGIN);

            this->InitFrame();

                glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            this->EndFrame();

        this->FpsCalculation(Enums::END);
    }
}

void Engine::InitFrame()
{
}

void Engine::EndFrame()
{
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
