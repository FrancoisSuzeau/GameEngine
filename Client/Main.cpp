/******************************************************************************************************************************************/
// File : Main.cpp
// Purpose : Program start
/******************************************************************************************************************************************/
#include <iostream>

#include "GraphicInitializerService.hpp"
#include "AudioInitializerService.hpp"
#include "ImGUIServiceInitalizer.hpp"
#include "Application.hpp"
#include "Application.cpp"
#include "Engines/Engine.hpp"
#include "JsonLoaderService.hpp"

 
int main(int argc, char** argv)
{
    IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
    Starting::Application app;

    app.SetServiceBuilder<Services::GraphicInitializerService>();
    app.SetServiceBuilder<Services::AudioInitializerService>();
    app.SetServiceBuilder<Services::ImGUIServiceInitializer>();
    app.SetServiceBuilder<Services::JsonLoaderService>();

    app.SetEngineBuilder<Engines::Engine>();

    app.StartAllBuilders();

    Engines::Engine main_engine = *container->make<Engines::Engine>().get();

    main_engine.MainLoop();

    app.EndingBuilders();

    return EXIT_SUCCESS;
}
