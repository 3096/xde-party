#pragma once

#include <filesystem>

#include "Aether/Aether.hpp"

class MainScreen : public Aether::Screen {
   private:
    MainScreen();
    MainScreen(const MainScreen&) = delete;
    ~MainScreen();

    // const
    static constexpr auto AMS_GAME_SAVE_DIR = "sdmc:/atmosphere/saves/sysmmc/user/account/0100ff500e34a000/";
    static constexpr auto SAVE_PREFIX = "bfsgame0";
    static constexpr auto SAVE_EXT = ".sav";

    // ui members
    Aether::List* m_saveList;
    Aether::List* m_partySlotList;
    Aether::List* m_partyMemberList;

    Aether::Text* m_statusText;

    // members
    std::filesystem::path m_curSavePath;
    uint8_t m_curTargetSlot;
    uint16_t m_curSelectedPartyMember;

    // think you can take me?
    void onLoad() override;
    void setSavePath(const std::filesystem::path& userDir, std::string_view saveSlot);
    void writeSlot();

   public:
    static inline auto& getInstance() {
        static MainScreen s_instance;
        return s_instance;
    }
};
