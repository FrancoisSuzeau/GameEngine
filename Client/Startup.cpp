/******************************************************************************************************************************************/
// File : Startup.cpp
// Purpose : Implementing startup
/******************************************************************************************************************************************/

#include "Startup.hpp"

namespace Starting
{
    void Startup::ConfigureClientViews(std::shared_ptr<Application> app)
    {
        if (app)
        {
            app->AddViewModel<ViewModels::SceneViewModel>(Constants::SCENEVIEWMODEL);
            app->AddViewModel<ViewModels::GuiViewModel>(Constants::GUIVIEWMODEL);
        }
    }

    void Startup::DeleteClientViews(std::shared_ptr<Application> app)
    {
        if (app)
        {
            app->DeleteReference<ViewModels::GuiViewModel>();
            app->DeleteReference<ViewModels::SceneViewModel>();
        }
    }
}


