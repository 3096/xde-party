#include "main_screen.hpp"

#include <functional>

#include "app.hpp"

auto getUserNameById(AccountUid userID) {
    auto profile = AccountProfile{};
    auto userdata = AccountUserData{};
    auto profilebase = AccountProfileBase{};

    auto rc = Result{};
    if (R_FAILED(rc = accountGetProfile(&profile, userID))) fatalThrow(rc);
    if (R_FAILED(rc = accountProfileGet(&profile, &userdata, &profilebase))) fatalThrow(rc);

    auto result = std::string_view{profilebase.nickname};
    accountProfileClose(&profile);

    return result;
}

MainScreen::MainScreen()
    : m_saveList(new Aether::List(0, 0, 420, 550)),
      m_partySlotList(new Aether::List(421, 0, 420, 550)),
      m_partyMemberList(new Aether::List(842, 0, 420, 550)),
      m_statusText(new Aether::Text(50, 570, "", 32)) {
    addElement(m_saveList);
    addElement(m_partySlotList);
    addElement(m_partyMemberList);
    addElement(m_statusText);

    auto* controls = new Aether::Controls();
    controls->addItem(new Aether::ControlItem(Aether::Button::A, "OK"));
    controls->addItem(new Aether::ControlItem(Aether::Button::Y, "Write Party Member"));
    controls->addItem(new Aether::ControlItem(Aether::Button::PLUS, "Exit"));
    onButtonPress(Aether::Button::Y, [this]() { writeSlot(); });
    onButtonPress(Aether::Button::PLUS, Application::exitApp);
    addElement(controls);

    setFocused(m_saveList);
}

MainScreen::~MainScreen() {}

void MainScreen::onLoad() {
    for (auto& userDirEntry : std::filesystem::directory_iterator(AMS_GAME_SAVE_DIR)) {
        if (not userDirEntry.is_directory()) continue;

        m_statusText->setString(std::to_string(userDirEntry.path().stem().string().size()));
        for (auto saveSlot : {"0", "0a", "2", "3"}) {
            // m_saveList->addElement(
            //     new Aether::ListButton("", [this, userDirEntry, saveSlot]() { setSavePath(userDirEntry, saveSlot);
            //     }));
        }
    }
}

void MainScreen::writeSlot() {}

void MainScreen::setSavePath(const std::filesystem::path& userDir, std::string_view saveSlot) {}
