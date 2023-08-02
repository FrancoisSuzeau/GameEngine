/******************************************************************************************************************************************/
// File : Main.cpp
// Purpose : Program start
/******************************************************************************************************************************************/
#include <iostream>

#include "Application.hpp"
#include "Views/GuiComponents/MetricsComponent.hpp"
#include "ViewModels/GUIViewModel.hpp"


int main(int argc, char** argv)
{
    std::shared_ptr<Starting::Application> app = std::make_shared<Starting::Application>();
    
    SQ_CLIENT_INFO("Squeamish v{}.{}", 0, 1);
    
    app->Initialize();
    app->SetGuiComponent<Views::MetricsComponent>();
    app->SetGuiComponent<ViewModels::GuiViewModel>();
  
    app->Run();
    
    SQ_CLIENT_INFO("Squeamish shutdown");

    app->Shutdown();
    app.reset();
    return EXIT_SUCCESS;
}
