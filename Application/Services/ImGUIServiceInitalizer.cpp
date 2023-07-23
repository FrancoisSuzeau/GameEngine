/******************************************************************************************************************************************/
// File : ImGUIServiceInitializer.cpp
// Purpose : Implementing service ImGUI initialisation
/******************************************************************************************************************************************/
#include "ImGUIServiceInitalizer.hpp"

using namespace Services;

void ImGUIServiceInitializer::Init()
{
	IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
	std::shared_ptr<Services::GraphicInitializerService> graph_service_init = container->make<Services::GraphicInitializerService>();

	SDL_GLContext gl_context = graph_service_init->GetGLContext();
	SDL_Window* sdl_window = graph_service_init->GetSDLWindow();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    m_io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(sdl_window, gl_context);
    ImGui_ImplOpenGL3_Init(Constants::IMGUIVERSION.c_str());

    SQ_APP_DEBUG("ImGui service SUCCESSFULLY initialized");
}

void ImGUIServiceInitializer::DeInit()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SQ_APP_DEBUG("ImGui service shutdown");
}

ImGuiIO ImGUIServiceInitializer::GetIO()
{
    return m_io;
}
