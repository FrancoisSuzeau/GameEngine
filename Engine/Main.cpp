/******************************************************************************************************************************************/
// File : Main.cpp
// Purpose : Program start
/******************************************************************************************************************************************/
#include <iostream>
#include "Services/GraphicInitializerService.hpp"
#include "Services/AudioInitializerService.hpp"
#include "IocModule.hpp"
#include "Container/Container.hpp"

int main(int argc, char** argv)
{
    
    IoC::Container::Container* container = IoC::Container::Container::GetInstanceContainer();
    container->registerType<Services::GraphicInitializerService>([]() {
        return new Services::GraphicInitializerService();
        });

    auto graphic_services = container->make<Services::GraphicInitializerService>();
    graphic_services->Init();

    container->registerType<Services::AudioInitializerService>([]() {
        return new Services::AudioInitializerService();
        });
    
    auto audio_services = container->make<Services::AudioInitializerService>();
    audio_services->Init();

    std::cout << std::endl;

    audio_services->DeInit();
    graphic_services->DeInit();

    return EXIT_SUCCESS;
}