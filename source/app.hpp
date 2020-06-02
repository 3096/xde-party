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

    Aether::Display m_display;

   public:
    static void run();
    static inline void setScreen(Aether::Screen& screen) { getInstance().m_display.setScreen(&screen); }
    static inline void exitApp() { getInstance().m_display.exit(); }
};
