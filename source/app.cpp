#include "app.hpp"

#include "main_screen.hpp"

Application::Application() : m_display() {
    m_display.setBackgroundColour(Aether::Theme::Dark.bg.r, Aether::Theme::Dark.bg.g, Aether::Theme::Dark.bg.b);
    // Set the highlight animation (see Theme.hpp)
    m_display.setHighlightAnimation(Aether::Theme::Dark.highlightFunc);
    // Set the colours to use for selections (see Display.hpp)
    m_display.setHighlightColours(Aether::Theme::Dark.highlightBG, Aether::Theme::Dark.selected);

    // Set the screen our app will be starting with
    m_display.setScreen(&MainScreen::getInstance());
}

Application::~Application() {
    // m_display member will be automatically destroyed, cleaning up display services
}

void Application::run() {
    // After everything is set up call loop like this:
    // This runs at 60 times per second if possible
    while (getInstance().m_display.loop()) {
        // You could do some other processing in here
    }
}
