#include "../routines.hpp"

bool windowHandler_trigger (const ::sf::Event& event)
{
    return (event.type == ::sf::Event::Closed);
}

void windowHandler_action ()
{
    easyGUI::Application* app = nullptr;
    
    app = app->getInstance();

    if(app != nullptr)
    {
        app->stop();
    }
}