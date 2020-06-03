#include "game.hpp"

#include <fstream>

namespace game {

void writePartyToSave(std::filesystem::path& savePath, Save::Party party) {
    auto p_save = std::make_unique<Save>();

    // count members and move up members if empty is mixed in between
    auto partyCheckMoveFrom = 0;
    auto partyCheckMoveTo = -1;
    while (partyCheckMoveFrom < PARTY_SLOT_COUNT) {
        if (party.ids[partyCheckMoveFrom] != 0) {
            partyCheckMoveTo++;
            auto movedOut = party.ids[partyCheckMoveFrom];
            party.ids[partyCheckMoveFrom] = 0;
            party.ids[partyCheckMoveTo] = movedOut;
        }
        partyCheckMoveFrom++;
    }
    auto partyMemberCount = static_cast<uint8_t>(partyCheckMoveTo + 1);

    auto saveFstream = std::fstream{savePath, std::fstream::binary | std::fstream::in | std::fstream::out};
    saveFstream.read(reinterpret_cast<char*>(p_save.get()), sizeof(Save));

    p_save->partyIds = party;
    p_save->partyMemberCount = partyMemberCount;

    saveFstream.seekp(0);
    saveFstream.write(reinterpret_cast<char*>(p_save.get()), sizeof(Save));
}

}  // namespace game
