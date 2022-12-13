#include <routines.hpp>
#include <menus.hpp>

using namespace easyGUI;

int main()
{
    // Setting application parameters
    unsigned appWidth = 800;
    unsigned appHeight = 600;
    std::string appTitle = "Demo app";

    // Declaring application object
    Application* app = nullptr;

    // Creating application
    app = app->getInstance(appWidth, appHeight, appTitle.c_str());

    // Creating routines
    Routine windowHandler(windowHandler_trigger, windowHandler_action);
    
    // Adding routine to app
    app->addRoutine(&windowHandler);

    try
    {
        // Creating menus
        createMainMenu(app);
        createSecondMenu(app);

        // Starting the application
        app->start();
    }
    catch(const ApplicationException* err)
    {
        ERROR << err->what();

        return 1;
    }
    
    return 0;
}
