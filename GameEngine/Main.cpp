#include <iostream>
#include <cassert>
#include "Services/GraphicServices.hpp"


int main(int argc, char** argv)
{
    
    Services::GraphicServices graphic_services;

    bool ret = graphic_services.Init();
    assert(ret);
    std::cout << ">> Initialise SDL : SUCCESS" << std::endl;

    std::cout << std::endl;

    graphic_services.DeInit();
    return EXIT_SUCCESS;
}