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

    dir.SetBuilder<Services::GraphicInitializerService>();
    dir.SetBuilder<Services::AudioInitializerService>();
    dir.SetBuilder<Services::ImGUIServiceInitializer>();

    dir.StartAllBuilder();

    Engines::Engine main_engine;
    main_engine.MainLoop();

    dir.EndingBuilder();

    return EXIT_SUCCESS;
}