/******************************************************************************************************************************************/
// File : Main.cpp
// Purpose : Program start
/******************************************************************************************************************************************/
#include <iostream>
#include "Services/GraphicInitializerService.hpp"
#include "Services/AudioInitializerService.hpp"
#include "Director.hpp"
#include "Director.cpp"

 
int main(int argc, char** argv)
{
    Starting::Director dir;

    dir.SetBuilder<Services::GraphicInitializerService>();
    dir.SetBuilder<Services::AudioInitializerService>();

    dir.StartAllBuilder();

    dir.EndingBuilder();

    return EXIT_SUCCESS;
}