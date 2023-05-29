/******************************************************************************************************************************************/
// File : Main.cpp
// Purpose : Program start
/******************************************************************************************************************************************/
#include <iostream>

#include "Services/GraphicInitializerService.hpp"
#include "Services/AudioInitializerService.hpp"
#include "Services/ImGUIServiceInitalizer.hpp"
#include "Director.hpp"
#include "Director.cpp"
#include "Engines/Engine.hpp"

 
int main(int argc, char** argv)
{
    Starting::Director dir;

    dir.SetServiceBuilder<Services::GraphicInitializerService>();
    dir.SetServiceBuilder<Services::AudioInitializerService>();
    dir.SetServiceBuilder<Services::ImGUIServiceInitializer>();

    dir.SetEngineBuilder<Engines::Engine>();

    dir.StartAllBuilders();

    IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
    Engines::Engine main_engine = *container->make<Engines::Engine>().get();

    main_engine.MainLoop();

    dir.EndingBuilders();

    return EXIT_SUCCESS;
}