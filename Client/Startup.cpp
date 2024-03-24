/******************************************************************************************************************************************/
// File : Startup.cpp
// Purpose : Implementing startup
/******************************************************************************************************************************************/

#include "Startup.hpp"

namespace Starting
{
    void Startup::ConfigureClientViews(std::shared_ptr<Application> app)
    {
        ConfigureClientGUI(app);
        ConfigureClientScene(app);
    }

    void Startup::DeleteClientViews(std::shared_ptr<Application> app)
    {
        DeleteClientGUI(app);
        DeleteClientScene(app);
    }

    void Startup::ConfigureClientGUI(std::shared_ptr<Application> app)
    {
        if (app)
        {
            app->AddView<Views::MetricsComponent>();
            app->AddView<Views::StackToolsComponent>();
            app->AddView<Views::AppAboutComponent>();
            app->AddView<Views::AppStyleEditorComponent>();
            app->AddView<Views::MenuToolsComponent>();
            app->AddView<Views::MenuEditComponent>();
            app->AddView<Views::MenuFileComponent>();
            app->AddView<Views::EventViewerComponent>();
            app->AddView<Views::StartComponent>();
            app->AddView<Views::SaveAsComponent>();
            app->AddView<Views::ConfirmComponent>();
            app->AddView<Views::WorkBarComponent>();

            app->AddViewModel<ViewModels::GuiViewModel>(Constants::GUIVIEWMODEL);
        }
    }
    void Startup::ConfigureClientScene(std::shared_ptr<Application> app)
    {
        app->AddView<Views::Canvas>();

        app->AddViewModel<ViewModels::SceneViewModel>(Constants::SCENEVIEWMODEL);
    }
    void Startup::DeleteClientGUI(std::shared_ptr<Application> app)
    {
        app->DeleteReference<ViewModels::GuiViewModel>();
    }
    void Startup::DeleteClientScene(std::shared_ptr<Application> app)
    {
        app->DeleteReference<ViewModels::SceneViewModel>();
    }
}


