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

// $Id: SaveSlot.hh,v 1.4 2004/11/30 03:35:59 technoplaza Exp $

#ifndef _SAVE_SLOT_HH
#define _SAVE_SLOT_HH

#include "../view/MainFrame.hh"

#define CHECKSUM_OFFSET 0x00
#define MOON_OFFSET 0x01
#define NAME_OFFSET 0x02
#define VIRTUE_OFFSET 0x0C
#define AVATAR_OFFSET 0x14
#define MEMBER_OFFSET 0x15
#define STONES_OFFSET 0x19
#define RUNES_OFFSET 0x1A
#define MAGIC_OFFSET 0x1B
#define HERB_OFFSET 0x1F
#define GOLD_OFFSET 0x27
#define TOOL_OFFSET 0x29
#define EQUIPMENT_OFFSET 0x39
#define LEVEL_OFFSET 0x69
#define CURRENT_HP_OFFSET 0x71
#define MAX_HP_OFFSET 0x81
#define CURRENT_MP_OFFSET 0x91
#define MAX_MP_OFFSET 0x99
#define STRENGTH_OFFSET 0xA1
#define INTELLIGENCE_OFFSET 0xA9
#define DEXTERITY_OFFSET 0xB1
#define EXPERIENCE_OFFSET 0xB9

namespace hack4u {
    enum Moons {TRAMMEL, FELUCCA};
    enum City {MOONGLOW, BRITAIN, JHELOM, YEW, 
               MINOC, TRINSIC, SKARABRAE, MAGINCIA};
    enum Virtues {HONESTY, COMPASSION, VALOR, JUSTICE,
                  SACRIFICE, HONOR, SPIRITUALITY, HUMILITY};
    enum Characters {MAGE, BARD, FIGHTER, DRUID, 
                     TINKER, PALADIN, RANGER, SHEPHERD};
    enum Magic {LIGHT, MISSILE, AWAKEN, CURE, WIND, HEAL, FIRE, EXIT, DISPEL,
                VIEW, PROTECT, ICE, BLINK, ENERGY, QUICK, INVALID1, SLEEP,
                REFLECT, NEGATE, INVALID2, DESTROY, JINX, SQUISH, GATE,
                TREMOR, LIFE, INVALID3, DEFEAT};
    enum Herbs {ASH, GINSENG, GARLIC, SILKWEB, MOSS, PEARL, FUNGUS, MANROOT};
    enum Tools {TORCH, GEM, KEY, OIL, SEXTANT, SCALE, FLUTE, CANDLE, BOOK,
                BELL, WHEEL, HORN, SKULL, TRUTHKEY, COURAGEKEY, LOVEKEY};            
    enum Equipment {SLING, BOW, XBOW, PLUS1BOW, DAGGER, STAFF, CLUB, AXE,
                    SWORD, PLUS1SWORD, PLUS2SWORD, PLUS1AXE, WAND, PLUS2AXE,
                    SWORDOFPARADISE,CLOTH,LEATHER,CHAIN,RING,PLUS1CLOTH,
                    PLATE,PLUS1CHAIN,PLUS1PLATE,ROBE,EXOTICARMOR};
    
    class MainFrame;
                    
    class SaveSlot {
    public:
        SaveSlot(const unsigned char *);
        ~SaveSlot();
        
        unsigned char checksum();
        bool isValid() { return valid; }
        bool isModified() { return modified; }
        
        int getPhase(int);
        void setPhase(int, int);
        
        wxString getHerosName();
        void setHerosName(wxString &);
        
        int getVirtue(int);
        void setVirtue(int, unsigned char);
        
        int getMember(int);
        void setMember(int, int);
        
        bool hasStone(int);
        void setStone(int, bool = true);
        
        bool hasRune(int);
        void setRune(int, bool = true);
        
        bool hasMagic(int);
        void setMagic(int, bool = true);
        
        int getHerb(int);
        void setHerb(int, unsigned char);
        
        wxInt16 getGold();
        void setGold(wxInt16);
        
        int getTool(int);
        void setTool(int, unsigned char = 1);
        
        int getEquipment(int, int);
        void setEquipment(int, int, unsigned char);
        
        int getLevel(int);
        void setLevel(int, unsigned char);
        
        wxInt16 getCurrentHP(int);
        void setCurrentHP(int, wxInt16);
        
        wxInt16 getMaxHP(int);
        void setMaxHP(int, wxInt16);
        
        int getCurrentMP(int);
        void setCurrentMP(int, unsigned char);
        
        int getMaxMP(int);
        void setMaxMP(int, unsigned char);
        
        int getStrength(int);
        void setStrength(int, unsigned char);
        
        int getIntelligence(int);
        void setIntelligence(int, unsigned char);
        
        int getDexterity(int);
        void setDexterity(int, unsigned char);
        
        wxInt16 getExperience(int);
        void setExperience(int, wxInt16);
        
        friend class MainFrame;
    private:
        void setModified(bool = true);
        unsigned char toNES(char);
        char fromNES(unsigned char);
    
        unsigned char *nvram;
        bool valid;
        bool modified;
        
        static const int CHECKSUM_XORS[];
    };
}

#endif

