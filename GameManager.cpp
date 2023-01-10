#include <Application.hpp>
#include <Routine.hpp>
#include <Exceptions/ApplicationException.hpp>
#include <Logger.hpp>
#include <string>

#include "routines.hpp"
#include "Arena.hpp"
#include "menus.hpp"

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
        init();

        // Creating menus
        createMainMenu(app);
        createSecondMenu(app);
        createWorldSelect(app);
        createWorldMgmt(app);
        createItemEditMenu(app);
        createItemsMenu(app);
        createItemViewMenu(app);

        // Starting the application
        app->start();
    }
    catch (const ApplicationException* err)
    {
        ERROR << err->what();

        return 1;
    }

    return 0;
}