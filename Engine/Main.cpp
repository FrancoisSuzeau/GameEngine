/******************************************************************************************************************************************/
// File : Main.cpp
// Purpose : Program start
/******************************************************************************************************************************************/
#include <iostream>
#include <memory>

#include "Services/GraphicInitializerService.hpp"
#include "Services/AudioInitializerService.hpp"
#include "Services/ImGUIServiceInitalizer.hpp"
#include "Director.hpp"
#include "Director.cpp"
#include "Engines/Engine.hpp"

 
int main(int argc, char** argv)
{
    Starting::Director dir;

    dir.SetBuilder<Services::GraphicInitializerService>();
    dir.SetBuilder<Services::AudioInitializerService>();
    dir.SetBuilder<Services::ImGUIServiceInitializer>();

    dir.StartAllBuilder();

    IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
    std::shared_ptr<Services::GraphicInitializerService> graph_service_init = container->make<Services::GraphicInitializerService>();

    SDL_Window* sdl_window = graph_service_init->GetSDLWindow();
    int w = graph_service_init->GetWidth();
    int h = graph_service_init->GetHeight();

    Engines::Engine main_engine(sdl_window, w, h);
    main_engine.MainLoop();

    dir.EndingBuilder();

    return EXIT_SUCCESS;
}