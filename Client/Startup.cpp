/******************************************************************************************************************************************/
// File : Startup.cpp
// Purpose : Implementing startup
/******************************************************************************************************************************************/

#include "Startup.hpp"

namespace Starting
{
    void Startup::ConfigureClientViews(std::shared_ptr<Application> app)
    {
        app->AddView<Views::MetricsComponent>();
        app->AddView<Views::StackToolsComponent>();
        app->AddView<Views::AppAboutComponent>();
        app->AddView<Views::AppStyleEditorComponent>();
        app->AddView<Views::MenuToolsComponent>();
        app->AddView<Views::MenuEditComponent>();
        app->AddViewModel<ViewModels::GuiViewModel>();
    }
}


