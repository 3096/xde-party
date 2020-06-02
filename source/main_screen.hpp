#include "Aether/Aether.hpp"

class MainScreen : public Aether::Screen {
   private:
    MainScreen();
    MainScreen(const MainScreen&) = delete;
    ~MainScreen();

   public:
    static inline auto& getInstance() {
        static MainScreen s_instance;
        return s_instance;
    }
};
