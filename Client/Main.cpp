/******************************************************************************************************************************************/
// File : Main.cpp
// Purpose : Program start
/******************************************************************************************************************************************/
#include <iostream>

#include "Startup.hpp"

using namespace Starting;

int main(int argc, char** argv)
{
    std::shared_ptr<Application> app = std::make_shared<Application>();
    
    if (app)
    {
        app->Initialize();

        Startup::ConfigureClientViews(app);

        app->Run();

        Startup::DeleteClientViews(app);
        app->Shutdown();
        
        app.reset();
    }

    return EXIT_SUCCESS;
}
