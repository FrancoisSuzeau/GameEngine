/******************************************************************************************************************************************/
// File : Main.cpp
// Purpose : Program start
/******************************************************************************************************************************************/
#include <iostream>

#include "GraphicInitializerService.hpp"
#include "AudioInitializerService.hpp"
#include "ImGUIServiceInitalizer.hpp"
#include "JsonLoaderService.hpp"
#include "ShaderLoaderService.hpp"
#include "Engines/Engine.hpp"
#include "Engines/GUIEngine.hpp"
#include "Application.hpp"
#include <Windows.h>

int main(int argc, char** argv)
{
    IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();

    std::shared_ptr<Starting::Application> app = std::make_shared<Starting::Application>();
    
    app->SetServiceBuilder<Services::GraphicInitializerService>();
    app->SetServiceBuilder<Services::AudioInitializerService>();
    app->SetServiceBuilder<Services::ImGUIServiceInitializer>();
    app->SetServiceBuilder<Services::JsonLoaderService>();
    app->SetServiceBuilder<Services::StateService>();
    app->SetServiceBuilder<Services::ShaderLoaderService>();

    app->SetEngineBuilder<Engines::GUIEngine>();
    app->SetEngineBuilder<Engines::Engine>();

    app->StartAllBuilders();

    std::shared_ptr<Engines::Engine> main_engine = container->make<Engines::Engine>();
    
    main_engine->MainLoop();

    app->EndingBuilders();
    app.reset();
    main_engine.reset();

    return EXIT_SUCCESS;
}
