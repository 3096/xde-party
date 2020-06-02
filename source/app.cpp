#include "app.hpp"

#include "main_screen.hpp"

Application::Application() : m_display() {
    m_display.setBackgroundColour(Aether::Theme::Dark.bg.r, Aether::Theme::Dark.bg.g, Aether::Theme::Dark.bg.b);
    m_display.setHighlightAnimation(Aether::Theme::Dark.highlightFunc);
    m_display.setHighlightColours(Aether::Theme::Dark.highlightBG, Aether::Theme::Dark.selected);

    m_display.setScreen(&MainScreen::getInstance());
}

Application::~Application() {}

void Application::run() {
    while (getInstance().m_display.loop())
        ;
}
