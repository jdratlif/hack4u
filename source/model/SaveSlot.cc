/*
 * hack4u
 * Copyright (C) 2004-2008 emuWorks
 * http://games.technoplaza.net/
 *
 * This file is part of hack4u.
 *
 * hack4u is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * hack4u is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with hack4u; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

// $Id: SaveSlot.cc,v 1.21 2008/12/16 22:12:52 jdratlif Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <cstring>

#include "model/ModelConstants.hh"
#include "model/SaveSlot.hh"

using namespace hack4u;

const std::pair<int, int> hack4u::FOUND_RUNES_OFFSET[] = {
    std::pair<int, int>(0xD4, 4), std::pair<int, int>(0xD4, 5),
    std::pair<int, int>(0xD4, 6), std::pair<int, int>(0xD4, 7),
    std::pair<int, int>(0xD5, 0), std::pair<int, int>(0xD5, 1),
    std::pair<int, int>(0xD5, 2), std::pair<int, int>(0xD5, 3)
};

const std::pair<int, int> hack4u::FOUND_STONES_OFFSET[] = {
    std::pair<int, int>(0xD6, 7), std::pair<int, int>(0xD7, 0),
    std::pair<int, int>(0xD7, 1), std::pair<int, int>(0xD7, 2),
    std::pair<int, int>(0xD7, 3), std::pair<int, int>(0xD7, 4),
    std::pair<int, int>(0xD7, 5), std::pair<int, int>(0xD7, 6)
};

const std::pair<int, int> hack4u::FOUND_BELL_OFFSET(0xD6, 1);
const std::pair<int, int> hack4u::FOUND_BOOK_OFFSET(0xD6, 0);
const std::pair<int, int> hack4u::FOUND_CANDLE_OFFSET(0xD5, 7);
const std::pair<int, int> hack4u::FOUND_FLUTE_OFFSET(0xD5, 5);
const std::pair<int, int> hack4u::FOUND_HORN_OFFSET(0xD6, 3);
const std::pair<int, int> hack4u::FOUND_SCALE_OFFSET(0xD5, 4);
const std::pair<int, int> hack4u::FOUND_SKULL_OFFSET(0xD6, 4);

const int SaveSlot::CHECKSUM_XORS[] = {
    0x55, 0xAA, 0x33, 0xCC,
    0xA5, 0x5A, 0xBB, 0x99
};

SaveSlot::SaveSlot(const char *data) {
    nvram = new unsigned char[SAVE_SIZE];
    std::memcpy(nvram, data, SAVE_SIZE);
    
    setModified(false);
}

SaveSlot::~SaveSlot() {
    delete nvram;
}

std::pair<int, int> SaveSlot::getBalloonLocation() const {
    return std::pair<int, int>(nvram[BALLOON_LATITUDE_OFFSET],
                               nvram[BALLOON_LONGITUDE_OFFSET]);
}

void SaveSlot::setBalloonLocation(std::pair<int, int> location) {
    nvram[BALLOON_LATITUDE_OFFSET] = location.first;
    nvram[BALLOON_LONGITUDE_OFFSET] = location.second;
    
    setModified();
}

wxInt16 SaveSlot::getCurrentHP(enum Character character) const {
    wxInt16 *ptr = reinterpret_cast<wxInt16 *>
        (nvram + CURRENT_HP_OFFSET + (character * 2));
    
    return wxINT16_SWAP_ON_BE(ptr[0]);
}

void SaveSlot::setCurrentHP(enum Character character, wxInt16 value) {
    wxInt16 *ptr = reinterpret_cast<wxInt16 *>
        (nvram + CURRENT_HP_OFFSET + (character * 2));
    
    ptr[0] = wxINT16_SWAP_ON_BE(value);
    setModified();
}

int SaveSlot::getCurrentMP(enum Character character) const {
    return nvram[CURRENT_MP_OFFSET + character];
}

void SaveSlot::setCurrentMP(enum Character character, unsigned char value) {
    nvram[CURRENT_MP_OFFSET + character] = value;
    setModified();
}

int SaveSlot::getDexterity(enum Character character) const {
    return nvram[DEXTERITY_OFFSET + character];
}

void SaveSlot::setDexterity(enum Character character, unsigned char value) {
    nvram[DEXTERITY_OFFSET + character] = value;
    setModified();
}

int SaveSlot::getEquipment(enum Character character, int slot) const {
    return nvram[EQUIPMENT_OFFSET + (character * 6) + slot];
}

void SaveSlot::setEquipment(enum Character character,
                            int slot, unsigned char value) {
    nvram[EQUIPMENT_OFFSET + (character * 6) + slot] = value;
    setModified();
}

wxInt16 SaveSlot::getExperience(enum Character character) const {
    wxInt16 *ptr = reinterpret_cast<wxInt16 *>
        (nvram + EXPERIENCE_OFFSET + (character * 2));
    
    return wxINT16_SWAP_ON_BE(ptr[0]);
}

void SaveSlot::setExperience(enum Character character, wxInt16 value) {
    wxInt16 *ptr = reinterpret_cast<wxInt16 *>
        (nvram + EXPERIENCE_OFFSET + (character * 2));
    
    ptr[0] = wxINT16_SWAP_ON_BE(value);
    setModified();
}

wxInt16 SaveSlot::getGold() const {
    wxUint16 *ptr = reinterpret_cast<wxUint16 *>(nvram + GOLD_OFFSET);
    
    return wxINT16_SWAP_ON_BE(ptr[0]);
}

void SaveSlot::setGold(wxInt16 gold) {
    wxUint16 *ptr = reinterpret_cast<wxUint16 *>(nvram + GOLD_OFFSET);
    
    ptr[0] = wxINT16_SWAP_ON_BE(gold);
    setModified();
}

int SaveSlot::getHerb(enum Herb herb) const {
    return nvram[HERB_OFFSET + herb];
}

void SaveSlot::setHerb(enum Herb herb, unsigned char value) {
    nvram[HERB_OFFSET + herb] = value;
    setModified();
}

wxString SaveSlot::getHerosName() const {
    wxString name;
    
    for (int offset = NAME_OFFSET; offset <= (NAME_OFFSET + 5); ++offset) {
        if (nvram[offset] == 0) {
            break;
        }
        
        char letter = fromNES(nvram[offset]);
        name.append(1, letter);
    }
    
    return name;
}

void SaveSlot::setHerosName(const wxString &name) {
    int pos;
    int length = name.size();
    
    for (pos = 0; pos < 5; ++pos) {
        if ((length - 1) < pos) {
            nvram[NAME_OFFSET + pos] = 0;
        } else {
            nvram[NAME_OFFSET + pos] = toNES(name.at(pos));
        }
    }
    
    setModified();
}

int SaveSlot::getIntelligence(enum Character character) const {
    return nvram[INTELLIGENCE_OFFSET + character];
}

void SaveSlot::setIntelligence(enum Character character, unsigned char value) {
    nvram[INTELLIGENCE_OFFSET + character] = value;
    setModified();
}

bool SaveSlot::hasJoined(enum Character character) const {
    return (nvram[JOINED_OFFSET] & (1 << character));
}

void SaveSlot::setJoined(enum Character character, bool value) {
    int mask = 1 << character;
    
    if (value) {
        nvram[JOINED_OFFSET] |= mask;
    } else {
        nvram[JOINED_OFFSET] &= ~mask;
    }
    
    setModified();
}

int SaveSlot::getLevel(enum Character character) const {
    return nvram[LEVEL_OFFSET + character];
}

void SaveSlot::setLevel(enum Character character, unsigned char level) {
    nvram[LEVEL_OFFSET + character] = level;
    setModified();
}

bool SaveSlot::hasMagic(enum Magic magic) const {
    int offset = MAGIC_OFFSET;
    int temp = magic;
    
    if (temp > 7) {
        offset += (temp / 8);
        temp %= 8;
    }

    return (nvram[offset] & (1 << temp));
}

void SaveSlot::setMagic(enum Magic magic, bool give) {
    // make sure we're not giving invalid magic
    wxASSERT((magic != INVALID1) && (magic != INVALID2) && (magic != INVALID3));
    
    int offset = MAGIC_OFFSET;
    int temp = magic;
    
    if (temp > 7) {
        offset += (temp / 8);
        temp %= 8;
    }

    int mask = 1 << temp;
    
    if (give) {
        nvram[offset] |= mask;
    } else {
        nvram[offset] &= ~mask;
    }
    
    setModified();
}

wxInt16 SaveSlot::getMaxHP(enum Character character) const {
    wxInt16 *ptr = reinterpret_cast<wxInt16 *>
        (nvram + MAX_HP_OFFSET + (character * 2));
    
    return wxINT16_SWAP_ON_BE(ptr[0]);
}

void SaveSlot::setMaxHP(enum Character character, wxInt16 value) {
    wxInt16 *ptr = reinterpret_cast<wxInt16 *>
        (nvram + MAX_HP_OFFSET + (character * 2));
    
    ptr[0] = wxINT16_SWAP_ON_BE(value);
    setModified();
}

int SaveSlot::getMaxMP(enum Character character) const {
    return nvram[MAX_MP_OFFSET + character];
}

void SaveSlot::setMaxMP(enum Character character, unsigned char value) {
    nvram[MAX_MP_OFFSET + character] = value;
    setModified();
}

int SaveSlot::getMember(int position) const {
    return (nvram[MEMBER_OFFSET + position]);
}

void SaveSlot::setMember(int position, int character) {
    nvram[MEMBER_OFFSET + position] = character;
    setModified();
}

void SaveSlot::setModified(bool modified) {
    this->modified = modified;
    
    if (modified) {
        nvram[CHECKSUM_OFFSET] = checksum();
    }
}

int SaveSlot::getPhase(enum Moon moon) const {
    int phase = nvram[MOON_OFFSET];
    
    if (moon == TRAMMEL) {
        return (phase / 3);
    }
    
    return (phase % 3);
}

void SaveSlot::setPhase(enum City trammel, int felucca) {
    int phase = (trammel * 3) + felucca;

    nvram[MOON_OFFSET] = phase;
    setModified();
}

bool SaveSlot::hasPirateShip(enum PirateShip ship) const {
    return (nvram[PIRATESHIP_OFFSET] & (1 << ship));
}

void SaveSlot::setPirateShip(enum PirateShip ship, bool give) {
    int mask = 1 << ship;
    
    if (give) {
        nvram[PIRATESHIP_OFFSET] |= mask;
    } else {
        nvram[PIRATESHIP_OFFSET] &= ~mask;
    }
    
    setModified();
}

std::pair<int, int>
SaveSlot::getPirateShipLocation(enum PirateShip ship) const {
    return std::pair<int, int>
        (nvram[PIRATESHIP_LATITUDE_OFFSET + (ship << 1)],
         nvram[PIRATESHIP_LONGITUDE_OFFSET + (ship << 1)]);
}

void SaveSlot::setPirateShipLocation(enum PirateShip ship,
                                     std::pair<int, int> location) {
    nvram[PIRATESHIP_LATITUDE_OFFSET + (ship << 1)] = location.first;
    nvram[PIRATESHIP_LONGITUDE_OFFSET + (ship << 1)] = location.second;
    
    setModified();
}

bool SaveSlot::hasRune(enum Virtue rune) const {
    return (nvram[RUNES_OFFSET] & (1 << rune));
}

void SaveSlot::setRune(enum Virtue rune, bool give) {
    const std::pair<int, int> &found = FOUND_RUNES_OFFSET[rune];
    
    if (give) {
        nvram[RUNES_OFFSET] |= (1 << rune);
        nvram[found.first] |= (1 << found.second);
    } else {
        nvram[RUNES_OFFSET] &= ~(1 << rune);
        nvram[found.first] &= ~(1 << found.second);
    }
    
    setModified();
}

enum StartLocation SaveSlot::getStartLocation() const {
    return static_cast<enum StartLocation>(nvram[START_LOCATION]);
}

void SaveSlot::setStartLocation(enum StartLocation location) {
    nvram[START_LOCATION] = location;
    setModified();
}

bool SaveSlot::hasStone(enum Virtue stone) const {
    return (nvram[STONES_OFFSET] & (1 << stone));
}

void SaveSlot::setStone(enum Virtue stone, bool give) {
    const std::pair<int, int> &found = FOUND_STONES_OFFSET[stone];
    
    if (give) {
        nvram[STONES_OFFSET] |= (1 << stone);
        nvram[found.first] |= (1 << found.second);
    } else {
        nvram[STONES_OFFSET] &= ~(1 << stone);
        nvram[found.first] &= ~(1 << found.second);
    }
    
    setModified();
}

int SaveSlot::getStrength(enum Character character) const {
    return nvram[STRENGTH_OFFSET + character];
}

void SaveSlot::setStrength(enum Character character, unsigned char value) {
    nvram[STRENGTH_OFFSET + character] = value;
    setModified();
}

int SaveSlot::getTool(enum Tool tool) const {
    return nvram[TOOL_OFFSET + tool];
}

void SaveSlot::setTool(enum Tool tool, unsigned char value) {
    nvram[TOOL_OFFSET + tool] = value;
    
    const std::pair<int, int> *found = 0;
    
    if (tool == BELL) {
        found = &FOUND_BELL_OFFSET;
    } else if (tool == BOOK) {
        found = &FOUND_BOOK_OFFSET;
    } else if (tool == CANDLE) {
        found = &FOUND_CANDLE_OFFSET;
    } else if (tool == FLUTE) {
        found = &FOUND_FLUTE_OFFSET;
    } else if (tool == HORN) {
        found = &FOUND_HORN_OFFSET;
    } else if (tool == SCALE) {
        found = &FOUND_SCALE_OFFSET;
    } else if (tool == SKULL) {
        found = &FOUND_SKULL_OFFSET;
    }
    
    if (found) {
        if (value > 0) {
            nvram[found->first] |= (1 << found->second);
        } else {
            nvram[found->first] &= ~(1 << found->second);
        }
    }
    
    setModified();
}

int SaveSlot::getVirtue(enum Virtue virtue) const {
    return nvram[VIRTUE_OFFSET + virtue];
}

void SaveSlot::setVirtue(enum Virtue virtue, unsigned char value) {
    int mask = 1 << virtue;
    
    if (value == 100) {
        nvram[AVATAR_OFFSET] |= mask;
    } else {
        nvram[AVATAR_OFFSET] &= ~mask;
    }
    
    nvram[VIRTUE_OFFSET + virtue] = value;
    setModified();
}

char SaveSlot::fromNES(unsigned char letter) {
    if ((letter >= 0x91) && (letter <= 0xAA)) {
        return ((letter - 0x91) + 'A');
    } else if ((letter >= 0xD1) && (letter <= 0xEA)) {
        return ((letter - 0xD1) + 'a');
    } else if (letter == 0xD0) {
        return '-';
    } else if (letter == 0x90) {
        return '!';
    }
    
    // return  _ underscore for all else
    return '_';
}

unsigned char SaveSlot::toNES(char letter) {
    if ((letter >= 'A') && (letter <= 'Z')) {
        return (unsigned char)(0x91 + (letter - 'A'));
    } else if ((letter >= 'a') && (letter <= 'z')) {
        return (unsigned char)(0xD1 + (letter - 'a'));
    } else if (letter == '-') {
        return (unsigned char)0xD0;
    } else if (letter == '!') {
        return (unsigned char)0x90;
    }
    
    // return _ underscore for all else
    return (unsigned char)0xBC;
}

std::pair<int, int> SaveSlot::getWhirlpoolLocation() const {
    return std::pair<int, int>(nvram[WHIRLPOOL_LATITUDE_OFFSET],
                               nvram[WHIRLPOOL_LONGITUDE_OFFSET]);
}

void SaveSlot::setWhirlpoolLocation(std::pair<int, int> location) {
    nvram[WHIRLPOOL_LATITUDE_OFFSET] = location.first;
    nvram[WHIRLPOOL_LONGITUDE_OFFSET] = location.second;
    
    setModified();
}

unsigned char SaveSlot::checksum() const {
    unsigned char sum = 0;
    int index = 0;
    
    for (int i = 1; i < SAVE_SIZE; ++i) {
        sum += (nvram[i] ^ CHECKSUM_XORS[index]);
        
        ++index &= 0x7;
    }
    
    return sum;
}

