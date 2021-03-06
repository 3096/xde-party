#pragma once

#include <cstdint>
#include <filesystem>
#include <list>
#include <string>
#include <vector>

namespace game {

// const
constexpr auto AMS_SAVE_GAME_DIR = "sdmc:/atmosphere/saves/sysmmc/user/account/0100ff500e34a000/";
const auto SAVE_MANAGER_GAME_DIRS = std::list<std::string>{
    "sdmc:/switch/Checkpoint/saves/0x0100FF500E34A000 Xenoblade Chronicles  Definitive Edition/",  // checkpoint
    "sdmc:/JKSV/Xenoblade Chronicles Definitive Edition/",                                        // JKSV
};
constexpr auto SAVE_PREFIX = "bfsgame0";
constexpr auto SAVE_EXT = ".sav";
const auto SAVE_NUMBERS = std::list<std::string>{"0a", "0", "1", "2"};

constexpr auto PARTY_SLOT_COUNT = 7;

// type
struct PartyMember {
    uint16_t id;
    std::string name;
};

const auto PARTY_MEMBERS = std::vector<PartyMember>{
    {0x0, "Empty"}, {0x1, "Shulk"}, {0x2, "Reyn"},  {0x3, "Fiora"},   {0x4, "Dunban"},  {0x5, "Sharla"},
    {0x6, "Riki"},  {0x7, "Melia"}, {0x8, "Fiora"}, {0x9, "Dickson"}, {0xA, "Mumkhar"}, {0xB, "Alvis"},
};

struct Save {
    uint8_t unk0[0x152318];
    struct Party {
        uint16_t ids[game::PARTY_SLOT_COUNT];
    } partyIds;
    uint8_t unk1[0x18 - game::PARTY_SLOT_COUNT * sizeof(uint16_t)];
    uint8_t partyMemberCount;
    uint8_t unk2[0x152F];
};

void writePartyToSave(std::filesystem::path& savePath, Save::Party party);

}  // namespace game
