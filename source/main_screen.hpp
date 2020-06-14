#pragma once

#include <filesystem>

#include "Aether/Aether.hpp"
#include "game.hpp"

class MainScreen : public Aether::Screen {
   private:
    MainScreen();
    MainScreen(const MainScreen&) = delete;
    ~MainScreen();

    // saves
    Aether::List* mp_saveList;
    std::vector<Aether::ListButton*> m_saveListButtons;
    size_t m_curSelectedSaveIndex;
    std::filesystem::path m_curSaveDir;
    bool m_curSaveDirIsAmsSave;
    std::string m_curSaveSlot;

    // party slots
    Aether::List* mp_partySlotDisplayList;
    Aether::ListButton* mp_partySlotDisplayListButtons[game::PARTY_SLOT_COUNT];
    game::Save::Party m_party;
    size_t m_curPartySlotTarget;

    // party members
    Aether::List* mp_partyMemberList;

    // ui
    Aether::TextBlock* mp_statusText;

    // helpers
    void setSelectedSave(size_t saveIndex, std::filesystem::path saveDir, std::string saveSlot);
    void writeToSave();

   public:
    static inline auto& getInstance() {
        static MainScreen s_instance;
        return s_instance;
    }
};
