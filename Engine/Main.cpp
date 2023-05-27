/******************************************************************************************************************************************/
// File : Main.cpp
// Purpose : Program start
/******************************************************************************************************************************************/
#include <iostream>
#include "Services/GraphicServices.hpp"
#include "Services/AudioService.hpp"
#include "IocModule.hpp"

int main(int argc, char** argv)
{
    
    /*IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
    container->registerType<Services::GraphicServices>([]() {
        return new Services::GraphicServices();
        });

    auto graphic_services = container->make<Services::GraphicServices>();
    graphic_services->Init();

    container->registerType<Services::AudioService>([]() {
        return new Services::AudioService();
        });
    
    auto audio_services = container->make<Services::AudioService>();
    audio_services->Init();

    std::cout << std::endl;

    audio_services->DeInit();
    graphic_services->DeInit();*/

    return EXIT_SUCCESS;
}