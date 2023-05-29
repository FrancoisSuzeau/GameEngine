/******************************************************************************************************************************************/
// File : Engine.cpp
// Purpose : Implementing the main engine
/******************************************************************************************************************************************/
#include "Engine.hpp"

using namespace Engines;

Engine::Engine()
{
    IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
    std::shared_ptr<Services::GraphicInitializerService> graph_service_init = container->make<Services::GraphicInitializerService>();

    m_window = graph_service_init->GetSDLWindow();
    m_width = graph_service_init->GetWidth();
    m_height = graph_service_init->GetHeight();
}

Engine::~Engine()
{
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

            ImGuiWindowFlags window_flags = 0;
            ImGuiStyle& style = ImGui::GetStyle();
            ImVec2 frame_padding_save = style.FramePadding;

            window_flags |= ImGuiWindowFlags_NoResize;
            window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
            window_flags |= ImGuiWindowFlags_NoScrollbar;
            ImGui::SetNextWindowPos(ImVec2(((float)m_width / 2.f) - 200.f, ((float)m_height / 2.f) - 200.f));
            ImGui::SetNextWindowSize(ImVec2(400, 400));

            ImGui::Begin("Settings", NULL, window_flags);

            exit = ImGui::Button("Stop Simulation", ImVec2(385.0f, 30.0f));

            ImGui::End();

            this->EndFrame();
        }

        this->FpsCalculation(Enums::END);
    }
}

void Engine::InitFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void Engine::EndFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
