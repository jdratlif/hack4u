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

// $Id: ModelConstants.hh,v 1.10 2008/12/16 22:12:52 jdratlif Exp $

#ifndef HACK4U_MODELCONSTANTS_HH_
#define HACK4U_MODELCONSTANTS_HH_

#include <utility>

/// SRAM offset for partial avatarhoods
#define AVATAR_OFFSET 0x14

/// SRAM offset for the Balloon's latitude
#define BALLOON_LATITUDE_OFFSET 0xF1

/// SRAM offset for the Balloon's longitude
#define BALLOON_LONGITUDE_OFFSET 0xF0

/// SRAM offset for the primary checksum
#define CHECKSUM_OFFSET 0x00

/// Starting SRAM offset for chracater current HP
#define CURRENT_HP_OFFSET 0x71

/// Starting SRAM offset for chracater current MP
#define CURRENT_MP_OFFSET 0x91

/// Starting SRAM offset for chracater dexterity
#define DEXTERITY_OFFSET 0xB1

/// Starting SRAM offset for equipment
#define EQUIPMENT_OFFSET 0x39

/// Starting SRAM offset for chracater experience
#define EXPERIENCE_OFFSET 0xB9

/// SRAM offset for gold
#define GOLD_OFFSET 0x27

/// Starting SRAM offset for herbs
#define HERB_OFFSET 0x1F

/// Starting SRAM offset for chracater intelligence
#define INTELLIGENCE_OFFSET 0xA9

/// SRAM offset for joined members
#define JOINED_OFFSET 0xB

/// Starting SRAM offset for chracater levels
#define LEVEL_OFFSET 0x69

/// Starting SRAM offset for magic
#define MAGIC_OFFSET 0x1B

/// Starting SRAM offset for chracater max HP
#define MAX_HP_OFFSET 0x81

/// Starting SRAM offset for chracater max MP
#define MAX_MP_OFFSET 0x99

/// Starting SRAM offset for the party members
#define MEMBER_OFFSET 0x15

/// SRAM offset for the moon phases
#define MOON_OFFSET 0x01

/// SRAM offset for the hero's name
#define NAME_OFFSET 0x02

/// SRAM offset for captured pirate ships
#define PIRATESHIP_OFFSET 0xED

/// Starting SRAM offset for Pirate Ship latitude
#define PIRATESHIP_LATITUDE_OFFSET 0xF5

/// Starting SRAM offset for Pirate Ship longitude
#define PIRATESHIP_LONGITUDE_OFFSET 0xF4

/// SRAM offset for Runes
#define RUNES_OFFSET 0x1A

/// The starting offset within the SRAM of the sanity values
#define SANITY_OFFSET 0x1900

/// The first sanity check XOR
#define SANITY_XOR1 0xAA

/// The second sanity check XOR
#define SANITY_XOR2 0x55

/// The size of a particular save game
#define SAVE_SIZE 0x200

/// Starting offset within the SRAM of the save games
#define SRAM_OFFSET 0x1A00

/// The size of SRAM
#define SRAM_SIZE 0x2000

/// The start location
#define START_LOCATION 0x107

/// SRAM offset for Stones
#define STONES_OFFSET 0x19

/// Starting SRAM offset for chracater strength
#define STRENGTH_OFFSET 0xA1

/// Starting SRAM offset for tools
#define TOOL_OFFSET 0x29

/// Starting SRAM offset for virtues 
#define VIRTUE_OFFSET 0x0C

/// SRAM offset for the whirlpool's latitude
#define WHIRLPOOL_LATITUDE_OFFSET 0xF3

/// SRAM offset for the whirlpool's longitude
#define WHIRLPOOL_LONGITUDE_OFFSET 0xF2

namespace hack4u {
    /// The eight characters
    enum Character {MAGE, BARD, FIGHTER, DRUID, 
                    TINKER, PALADIN, RANGER, SHEPHERD};
    
    /// The eight cities of virtue
    enum City {MOONGLOW, BRITAIN, JHELOM, YEW, 
               MINOC, TRINSIC, SKARABRAE, MAGINCIA};
                    
    /// The eight herbs (reagents)
    enum Herb {ASH, GINSENG, GARLIC, SILKWEB, MOSS, PEARL, FUNGUS, MANROOT};
                     
    /// The possible magic in the game
    enum Magic {LIGHT, MISSILE, AWAKEN, CURE, WIND, HEAL, FIRE, EXIT, DISPEL,
                VIEW, PROTECT, ICE, BLINK, ENERGY, QUICK, INVALID1, SLEEP,
                REFLECT, NEGATE, INVALID2, DESTROY, JINX, SQUISH, GATE,
                TREMOR, LIFE, INVALID3, DEFEAT};
                
    /// The two moons of Ultima
    enum Moon {TRAMMEL, FELUCCA};
    
    /// The capture pirate ships
    enum PirateShip {SHIP1, SHIP2, SHIP3, SHIP4};
    
    /// The possible starting locations
    enum StartLocation {MOONGLOW_INN = 0x5, BRITAIN_INN, JHELOM_INN, YEW_INN,
                        MINOC_INN, TRINSIC_INN, SKARABRAE_INN,
                        VESPER_INN = 0xE};
    
    /// The tools
    enum Tool {TORCH, GEM, KEY, OIL, SEXTANT, SCALE, FLUTE, CANDLE, BOOK,
                BELL, WHEEL, HORN, SKULL, TRUTHKEY, COURAGEKEY, LOVEKEY};
                
    /// The eight virtues
    enum Virtue {HONESTY, COMPASSION, VALOR, JUSTICE,
                  SACRIFICE, HONOR, SPIRITUALITY, HUMILITY};
                  
    /// Found offsets for the eight runes
    extern const std::pair<int, int> FOUND_RUNES_OFFSET[];
    
    /// Found offsets for the eight stones
    extern const std::pair<int, int> FOUND_STONES_OFFSET[];
    
    ///  Found offset for the Bell of Courage
    extern const std::pair<int, int> FOUND_BELL_OFFSET;
    
    /// Found offset for the Book of Truth
    extern const std::pair<int, int> FOUND_BOOK_OFFSET;
    
    /// Found offset for the Candle of Love
    extern const std::pair<int, int> FOUND_CANDLE_OFFSET;
    
    /// Found offset for the Flute
    extern const std::pair<int, int> FOUND_FLUTE_OFFSET;
    
    /// Found offset for the Silver Horn
    extern const std::pair<int, int> FOUND_HORN_OFFSET;
    
    /// Found offset for the Scale
    extern const std::pair<int, int> FOUND_SCALE_OFFSET;
    
    /// Found offset for Mondain's Skull
    extern const std::pair<int, int> FOUND_SKULL_OFFSET;
}

#endif

