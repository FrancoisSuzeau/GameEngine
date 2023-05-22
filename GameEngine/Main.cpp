/******************************************************************************************************************************************/
// File : Main.cpp
// Purpose : Program start
/******************************************************************************************************************************************/
#include <iostream>
#include "Services/GraphicServices.hpp"


int main(int argc, char** argv)
{
    
    Services::GraphicServices graphic_services;

    graphic_services.Init();

    std::cout << std::endl;

    graphic_services.DeInit();
    return EXIT_SUCCESS;
}