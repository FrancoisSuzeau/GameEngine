/******************************************************************************************************************************************/
// File : Main.cpp
// Purpose : Program start
/******************************************************************************************************************************************/
#include <iostream>
#include "Services/GraphicServices.hpp"
#include "Services/AudioService.hpp"


int main(int argc, char** argv)
{
    Services::GraphicServices graphic_services;
    Services::AudioService audio_services;

    graphic_services.Init();
    audio_services.Init();

    std::cout << std::endl;

    audio_services.DeInit();
    graphic_services.DeInit();
    return EXIT_SUCCESS;
}