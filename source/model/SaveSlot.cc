/*
 * Copyright (C) 2004 emuWorks
 * http://games.technoplaza.net/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

// $Id: SaveSlot.cc,v 1.7 2004/12/05 02:59:28 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <cstring>
#include "SaveSlot.hh"

using namespace hack4u;

const int SaveSlot::CHECKSUM_XORS[] = {
    0x55, 0xAA, 0x33, 0xCC,
    0xA5, 0x5A, 0xBB, 0x99
};

SaveSlot::SaveSlot(const unsigned char *data) {
    nvram = new unsigned char[0x200];
    memcpy(nvram, data, 0x200);
    
    setModified(false);
    
    if (checksum() == nvram[0]) {
        valid = true;
    } else {
        valid = false;
    }
}

SaveSlot::~SaveSlot() {
    delete nvram;
}

unsigned char SaveSlot::checksum() const {
    unsigned char sum = 0;
    int index = 0;
    
    for (int i = 1; i < 0x200; i++) {
        sum += (nvram[i] ^ CHECKSUM_XORS[index]);
        
        index++;
        index &= 0x7;
    }
    
    return sum;
}

int SaveSlot::getPhase(int moon) const {
    int phase = nvram[MOON_OFFSET];
    
    if (moon == TRAMMEL) {
        return (phase / 3);
    }
    
    return (phase % 3);
}

void SaveSlot::setPhase(int trammel, int felucca) {
    int phase = (trammel * 3) + felucca;

    nvram[MOON_OFFSET] = phase;
    setModified();
}

wxString SaveSlot::getHerosName() const {
    wxString name;
    
    for (int offset = NAME_OFFSET; offset <= (NAME_OFFSET + 5); offset++) {
        if (nvram[offset] == 0) {
            break;
        }
        
        char letter = fromNES(nvram[offset]);
        name.append(1, letter);
    }
    
    return name;
}

void SaveSlot::setHerosName(wxString &name) {
    int pos;
    int length = name.size();
    
    for (pos = 0; pos < 5; pos++) {
        if ((length - 1) < pos) {
            nvram[NAME_OFFSET + pos] = 0;
        } else {
            nvram[NAME_OFFSET + pos] = toNES(name.at(pos));
        }
    }
    
    setModified();
}

int SaveSlot::getVirtue(int virtue) const {
    return (int)(nvram[VIRTUE_OFFSET + virtue]);
}

void SaveSlot::setVirtue(int virtue, unsigned char value) {
    unsigned char *virtues = (nvram + VIRTUE_OFFSET + virtue);
    *virtues = value;
    
    int mask = (1 << virtue);
    unsigned char *avatar = (nvram + AVATAR_OFFSET);
    
    if (value < 100) {
        mask = ~mask;
        (*avatar) &= mask;
    } else {
        (*avatar) |= mask;
    }
    
    setModified();
}

int SaveSlot::getMember(int position) const {
    return (nvram[MEMBER_OFFSET + position]);
}

void SaveSlot::setMember(int position, int character) {
    nvram[MEMBER_OFFSET + position] = character;
    setModified();
}

bool SaveSlot::hasStone(int stone) const {
    unsigned char stones = *(nvram + STONES_OFFSET);
    
    return (stones & (1 << stone));
}

void SaveSlot::setStone(int stone, bool give) {
    unsigned char *stones = (nvram + STONES_OFFSET);
    int mask = (1 << stone);
    
    if (give) {
        (*stones) |= mask;
    } else {
        mask = ~mask;
        (*stones) &= mask;
    }
    
    setModified();
}

bool SaveSlot::hasRune(int rune) const {
    unsigned char runes = *(nvram + RUNES_OFFSET);
    
    return (runes & (1 << rune));
}

void SaveSlot::setRune(int rune, bool give) {
    unsigned char *runes = (nvram + RUNES_OFFSET);
    int mask = (1 << rune);
    
    if (give) {
        (*runes) |= mask;
    } else {
        mask = ~mask;
        (*runes) &= mask;
    }
    
    setModified();
}

bool SaveSlot::hasMagic(int magic) const {
    int offset = MAGIC_OFFSET;
    
    if (magic > 7) {
        offset += (magic / 8);
        magic %= 8;
    }

    return (nvram[offset] & (1 << magic));
}

void SaveSlot::setMagic(int magic, bool give) {
    int offset = MAGIC_OFFSET;
    
    if (magic > 7) {
        offset += (magic / 8);
        magic %= 8;
    }
    
    unsigned char *magics = (nvram + offset);
    int mask = (1 << magic);
    
    if (give) {
        (*magics) |= mask;
    } else {
        mask = ~mask;
        (*magics) &= mask;
    }
    
    setModified();
}

int SaveSlot::getHerb(int herb) const {
    return nvram[HERB_OFFSET + herb];
}

void SaveSlot::setHerb(int herb, unsigned char value) {
    nvram[HERB_OFFSET + herb] = value;
    setModified();
}

wxInt16 SaveSlot::getGold() const {
    wxUint16 *ptr = (wxUint16 *)(nvram + GOLD_OFFSET);
    
    return wxINT16_SWAP_ON_BE(ptr[0]);
}

void SaveSlot::setGold(wxInt16 gold) {
    wxUint16 *ptr = (wxUint16 *)(nvram + GOLD_OFFSET);
    
    ptr[0] = wxINT16_SWAP_ON_BE(gold);
    setModified();
}

int SaveSlot::getTool(int tool) const {
    return (int)nvram[TOOL_OFFSET + tool];
}

void SaveSlot::setTool(int tool, unsigned char value) {
    nvram[TOOL_OFFSET + tool] = value;
    setModified();
}

int SaveSlot::getEquipment(int character, int slot) const {
    return nvram[EQUIPMENT_OFFSET + (character * 6) + slot];
}

void SaveSlot::setEquipment(int character, int slot, unsigned char value) {
    nvram[EQUIPMENT_OFFSET + (character * 6) + slot] = value;
    setModified();
}

int SaveSlot::getLevel(int character) const {
    return nvram[LEVEL_OFFSET + character];
}

void SaveSlot::setLevel(int character, unsigned char level) {
    nvram[LEVEL_OFFSET + character] = level;
    setModified();
}

wxInt16 SaveSlot::getCurrentHP(int character) const {
    wxInt16 *ptr = (wxInt16 *)(nvram + CURRENT_HP_OFFSET + (character * 2));
    
    return wxINT16_SWAP_ON_BE(ptr[0]);
}

void SaveSlot::setCurrentHP(int character, wxInt16 value) {
    wxInt16 *ptr = (wxInt16 *)(nvram + CURRENT_HP_OFFSET + (character * 2));
    
    ptr[0] = wxINT16_SWAP_ON_BE(value);
    setModified();
}

wxInt16 SaveSlot::getMaxHP(int character) const {
    wxInt16 *ptr = (wxInt16 *)(nvram + MAX_HP_OFFSET + (character * 2));
    
    return wxINT16_SWAP_ON_BE(ptr[0]);
}

void SaveSlot::setMaxHP(int character, wxInt16 value) {
    wxInt16 *ptr = (wxInt16 *)(nvram + MAX_HP_OFFSET + (character * 2));
    
    ptr[0] = wxINT16_SWAP_ON_BE(value);
    setModified();
}

int SaveSlot::getCurrentMP(int character) const {
    return nvram[CURRENT_MP_OFFSET + character];
}

void SaveSlot::setCurrentMP(int character, unsigned char value) {
    nvram[CURRENT_MP_OFFSET + character] = value;
    setModified();
}

int SaveSlot::getMaxMP(int character) const {
    return nvram[MAX_MP_OFFSET + character];
}

void SaveSlot::setMaxMP(int character, unsigned char value) {
    nvram[MAX_MP_OFFSET + character] = value;
    setModified();
}

int SaveSlot::getStrength(int character) const {
    return nvram[STRENGTH_OFFSET + character];
}

void SaveSlot::setStrength(int character, unsigned char value) {
    nvram[STRENGTH_OFFSET + character] = value;
    setModified();
}

int SaveSlot::getIntelligence(int character) const {
    return nvram[INTELLIGENCE_OFFSET + character];
}

void SaveSlot::setIntelligence(int character, unsigned char value) {
    nvram[INTELLIGENCE_OFFSET + character] = value;
    setModified();
}

int SaveSlot::getDexterity(int character) const {
    return nvram[DEXTERITY_OFFSET + character];
}

void SaveSlot::setDexterity(int character, unsigned char value) {
    nvram[DEXTERITY_OFFSET + character] = value;
    setModified();
}

wxInt16 SaveSlot::getExperience(int character) const {
    wxInt16 *ptr = (wxInt16 *)(nvram + EXPERIENCE_OFFSET + (character * 2));
    
    return wxINT16_SWAP_ON_BE(ptr[0]);
}

void SaveSlot::setExperience(int character, wxInt16 value) {
    wxInt16 *ptr = (wxInt16 *)(nvram + EXPERIENCE_OFFSET + (character * 2));
    
    ptr[0] = wxINT16_SWAP_ON_BE(value);
    setModified();
}

void SaveSlot::setModified(bool modified) {
    this->modified = modified;
    
    if (modified) {
        nvram[CHECKSUM_OFFSET] = checksum();
    }
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

