#include "main_screen.hpp"

#include "app.hpp"

auto getUserNameByIdStr(std::string userIdStr) {
    auto userId = AccountUid{std::stoul(userIdStr.substr(16, 16), nullptr, 16),
                             std::stoul(userIdStr.substr(0, 16), nullptr, 16)};

    auto profile = AccountProfile{};
    auto userdata = AccountUserData{};
    auto profilebase = AccountProfileBase{};

    auto rc = Result{};
    if (R_FAILED(rc = accountGetProfile(&profile, userId))) fatalThrow(rc);
    if (R_FAILED(rc = accountProfileGet(&profile, &userdata, &profilebase))) fatalThrow(rc);

    auto result = std::string{profilebase.nickname};
    accountProfileClose(&profile);

    return result;
}

MainScreen::MainScreen()
    : mp_saveList(new Aether::List(0, 0, 420, 550)),
      m_curSaveDir(),
      m_curSaveSlot(),
      mp_partySlotDisplayList(new Aether::List(421, 0, 420, 550)),
      m_party{},
      mp_partyMemberList(new Aether::List(842, 0, 420, 550)),
      mp_statusText(new Aether::TextBlock(50, 570, "", 28, 1180)) {
    //
    // scan AMS save dir

    if (std::filesystem::exists(game::AMS_SAVE_GAME_DIR)) {
        for (auto& userDirEntry : std::filesystem::directory_iterator(game::AMS_SAVE_GAME_DIR)) {
            if (not userDirEntry.is_directory()) continue;

            auto userName = getUserNameByIdStr(userDirEntry.path().stem().string());
            for (auto saveSlot : game::SAVE_NUMBERS) {
                auto curSaveIndex = m_saveListButtons.size();
                auto* saveListButton =
                    new Aether::ListButton(userName + "-" + saveSlot, [this, curSaveIndex, userDirEntry, saveSlot]() {
                        setSelectedSave(curSaveIndex, userDirEntry.path(), saveSlot);
                        m_curSaveDirIsAmsSave = true;
                    });
                m_saveListButtons.push_back(saveListButton);
                mp_saveList->addElement(saveListButton);
            }
        }
    }

    // scan save manager save dirs
    for (auto& saveManagerGameDir : game::SAVE_MANAGER_GAME_DIRS) {
        if (not std::filesystem::exists(saveManagerGameDir)) continue;

        for (auto& saveDirEntry : std::filesystem::directory_iterator(saveManagerGameDir)) {
            if (not saveDirEntry.is_directory()) continue;

            auto saveName = saveDirEntry.path().stem().string();
            for (auto saveSlot : game::SAVE_NUMBERS) {
                auto curSaveIndex = m_saveListButtons.size();
                auto* saveListButton =
                    new Aether::ListButton(saveName + "-" + saveSlot, [this, curSaveIndex, saveDirEntry, saveSlot]() {
                        setSelectedSave(curSaveIndex, saveDirEntry.path(), saveSlot);
                        m_curSaveDirIsAmsSave = false;
                    });
                m_saveListButtons.push_back(saveListButton);
                mp_saveList->addElement(saveListButton);
            }
        }
    }

    addElement(mp_saveList);

    // party slot list
    for (auto i = size_t{0}; i < game::PARTY_SLOT_COUNT; i++) {
        mp_partySlotDisplayListButtons[i] =
            new Aether::ListButton(std::to_string(i) + ": " + game::PARTY_MEMBERS[m_party.ids[i]].name, [this, i]() {
                mp_partySlotDisplayListButtons[m_curPartySlotTarget]->setTextColour(Aether::Theme::Dark.text);
                m_curPartySlotTarget = i;
                mp_partySlotDisplayListButtons[m_curPartySlotTarget]->setTextColour(Aether::Theme::Dark.accent);
                mp_statusText->setString("Selected slot " + std::to_string(m_curPartySlotTarget));
            });
        mp_partySlotDisplayList->addElement(mp_partySlotDisplayListButtons[i]);
    }
    addElement(mp_partySlotDisplayList);

    // party member list
    for (auto& partyMember : game::PARTY_MEMBERS) {
        mp_partyMemberList->addElement(new Aether::ListButton(partyMember.name, [this, partyMember]() {
            m_party.ids[m_curPartySlotTarget] = partyMember.id;
            mp_partySlotDisplayListButtons[m_curPartySlotTarget]->setText(std::to_string(m_curPartySlotTarget) + ": " +
                                                                          partyMember.name);
        }));
    }
    addElement(mp_partyMemberList);

    addElement(mp_statusText);

    auto* controls = new Aether::Controls();
    controls->addItem(new Aether::ControlItem(Aether::Button::A, "OK"));
    controls->addItem(new Aether::ControlItem(Aether::Button::Y, "Write Party Member"));
    controls->addItem(new Aether::ControlItem(Aether::Button::PLUS, "Exit"));
    onButtonPress(Aether::Button::Y, [this]() { writeToSave(); });
    onButtonPress(Aether::Button::PLUS, Application::exitApp);
    addElement(controls);

    setFocused(mp_saveList);
}

MainScreen::~MainScreen() {}

void MainScreen::setSelectedSave(size_t saveIndex, std::filesystem::path saveDir, std::string saveSlot) {
    // highlight button
    m_saveListButtons[m_curSelectedSaveIndex]->setTextColour(Aether::Theme::Dark.text);
    m_curSelectedSaveIndex = saveIndex;
    m_saveListButtons[m_curSelectedSaveIndex]->setTextColour(Aether::Theme::Dark.accent);
    // set save target
    m_curSaveDir = saveDir;
    m_curSaveSlot = saveSlot;
    mp_statusText->setString(m_curSaveDir.string() + "-" + m_curSaveSlot);
}

void MainScreen::writeToSave() {
    if (m_curSaveSlot.empty()) return;

    auto saveFilePath = std::filesystem::path{game::SAVE_PREFIX + m_curSaveSlot + game::SAVE_EXT};

    if (m_curSaveDirIsAmsSave) {
        auto targetPath0 = m_curSaveDir;
        targetPath0 /= "0";
        targetPath0 /= saveFilePath;
        writePartyToSave(targetPath0, m_party);

        auto targetPath1 = m_curSaveDir;
        targetPath1 /= "1";
        targetPath1 /= saveFilePath;
        writePartyToSave(targetPath1, m_party);
    } else {
        auto targetPath = m_curSaveDir;
        targetPath /= saveFilePath;
        writePartyToSave(targetPath, m_party);
    }

    mp_statusText->setString("Written " + saveFilePath.string());
}
