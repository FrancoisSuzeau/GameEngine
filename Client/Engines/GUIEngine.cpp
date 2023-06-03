/******************************************************************************************************************************************/
// File : GUIEngine.cpp
// Purpose : Implementing the GUI engine
/******************************************************************************************************************************************/
#include "GUIEngine.hpp"

using namespace Engines;

GUIEngine::~GUIEngine()
{
}

void GUIEngine::Construct()
{
	IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
	std::shared_ptr<Services::ImGUIServiceInitializer> imgui_service_init = container->make<Services::ImGUIServiceInitializer>();

	m_io = imgui_service_init->GetIO();
}

void GUIEngine::InitFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void GUIEngine::EndFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIEngine::RenderExitButton(bool& exit, int width, int height)
{
    ImGuiWindowFlags window_flags = 0;
    ImGuiStyle& style = ImGui::GetStyle();
    style.FrameRounding = 15;

    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoBackground;
    window_flags |= ImGuiWindowFlags_NoScrollbar;

    ImGui::SetNextWindowPos(ImVec2(((float)width / 2.f) - 200.f, ((float)height / 2.f) - 200.f));
    ImGui::SetNextWindowSize(ImVec2(400, 400));

    ImGui::Begin("Exit", NULL, window_flags);

    exit = ImGui::Button("Stop Simulation", ImVec2(385.0f, 30.0f));

    ImGui::End();
}
