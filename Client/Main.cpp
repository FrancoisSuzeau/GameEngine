/******************************************************************************************************************************************/
// File : Main.cpp
// Purpose : Program start
/******************************************************************************************************************************************/
#include <iostream>

#include "Application.hpp"
#include "Views/GuiComponents/MetricsComponent.hpp"



int main(int argc, char** argv)
{
    std::shared_ptr<Starting::Application> app = std::make_shared<Starting::Application>();
    
    SQ_CLIENT_INFO("Squeamish v{}.{}", 0, 1);
    
    app->Initialize();
    app->AddView<Views::MetricsComponent>();
  
    app->Run();
    
    SQ_CLIENT_INFO("Squeamish shutdown");

    app->Shutdown();
    app.reset();
    return EXIT_SUCCESS;
}
