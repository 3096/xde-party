#include "main_screen.hpp"

#include "app.hpp"

MainScreen::MainScreen() {
    // this is an example for what you could do with Aether, written by tallbl0nde

    // We can add button callbacks to a screen too
    // Call Application::exitApp() to stop the display main loop
    onButtonPress(Aether::Button::PLUS, Application::exitApp);

    // We'll add a basic text element to begin
    // See the docs for what each parameter is
    auto* txt = new Aether::Text(50, 50, "Hello World!", 18);
    txt->setColour(Aether::Colour{200, 250, 200, 255});

    // Every element must be explicitly added to the screen/their parent element
    // Otherwise they won't show up!
    addElement(txt);

    // We'll add a button below the text to change the colour of the text colour
    auto* btn = new Aether::FilledButton(100, 300, 200, 60, "Press me!", 18, [txt]() {
        txt->setColour(Aether::Colour{255, 0, 50, 255});
    });
    // See Theme.hpp for supplied colours
    btn->setFillColour(Aether::Theme::Dark.accent);
    btn->setTextColour(Aether::Theme::Light.text);

    // Note that as this was the first 'selectable' element added it will automatically be highlighted on launch
    addElement(btn);

    // Next we'll add a basic list
    auto* list = new Aether::List(500, 100, 400, 400);
    addElement(list);

    // Note that when adding an element to a list the width will be adjusted to match the width of the list!
    // With the provided Aether::List* elements this is handled automatically...
    auto* tmp = new Aether::ListButton("Button", [list]() {
        // When the button is pressed we'll add another button to the list
        // Giving it a callback of nullptr causes nothing to happen when pressed
        list->addElement(new Aether::ListButton("New button!", nullptr));
    });
    list->addElement(tmp);

    // Adding some controls sends a button event when that shortcut is pressed:
    // It will position everything along the bottom
    auto* ctrls = new Aether::Controls();
    addElement(ctrls);

    // Only ControlItems can be added to Controls (use addItem() instead of addElement())
    auto* itm = new Aether::ControlItem(Aether::Button::PLUS, "Exit");
    ctrls->addItem(itm);
    // Note this won't do anything as we didn't assign a minus callback to the screen earlier
    itm = new Aether::ControlItem(Aether::Button::MINUS, "Change Colour");
    ctrls->addItem(itm);
}

MainScreen::~MainScreen() {
    // the parent descructor will clean everything up for us as long is the element is added to the screen
}
