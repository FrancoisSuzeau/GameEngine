/******************************************************************************************************************************************/
// File : Main.cpp
// Purpose : Program start
/******************************************************************************************************************************************/
#include <iostream>

#include "Application.hpp"
#include "Views/Views.hpp"
#include "ViewModels/GUIViewModel.hpp"


int main(int argc, char** argv)
{
    std::shared_ptr<Starting::Application> app = std::make_shared<Starting::Application>();
    
    app->Initialize();

    app->AddView<Views::MetricsComponent>();
    app->AddView<Views::StackToolsComponent>();
    app->AddView<Views::AppAboutComponent>();
    app->AddView<Views::AppStyleEditorComponent>();
    app->AddViewModel<ViewModels::GuiViewModel>();
  
    app->Run();

    app->Shutdown();
    app.reset();

    return EXIT_SUCCESS;
}
