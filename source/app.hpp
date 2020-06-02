#include "Aether/Aether.hpp"

class Application {
   private:
    Application();
    Application(const Application&) = delete;
    ~Application();
    static inline auto& getInstance() {
        static Application s_instance;
        return s_instance;
    }

    // We need to create the display 'element'
    // It acts as our 'root element' for everything on screen
    Aether::Display m_display;

   public:
    static void run();
    static inline void setScreen(Aether::Screen& screen) {
        // Call Aether::Display::exit() to break out of the loop
        getInstance().m_display.setScreen(&screen);
    }
    static inline void exitApp() { getInstance().m_display.exit(); }
};
