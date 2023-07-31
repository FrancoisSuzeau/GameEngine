/******************************************************************************************************************************************/
// File : Main.cpp
// Purpose : Program start
/******************************************************************************************************************************************/
#include <iostream>

#include "Engines/Engine.hpp"
#include "Engines/GUIEngine.hpp"
#include "Application.hpp"


int main(int argc, char** argv)
{
    std::shared_ptr<Starting::Application> app = std::make_shared<Starting::Application>();
    IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
    
    SQ_CLIENT_INFO("Squeamish v{}.{}", 0, 1);
    
    app->SetAllServices();
    app->SetEngineBuilder<Engines::GUIEngine>();
    app->SetEngineBuilder<Engines::SceneEngine::SceneEngine>();
    app->SetEngineBuilder<Engines::Engine>();

    app->Run();

    std::shared_ptr<Engines::Engine> main_engine = container->make<Engines::Engine>();
    
    main_engine->MainLoop();

    main_engine.reset();
    SQ_CLIENT_INFO("Squeamish shutdown");

    app->Shutdown();
    app.reset();
    return EXIT_SUCCESS;
}
