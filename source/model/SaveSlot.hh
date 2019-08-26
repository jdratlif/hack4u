/*
 * hack4u
 * Copyright (C) 2004-2005 emuWorks
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

// $Id: SaveSlot.hh,v 1.6 2005/08/03 11:11:39 technoplaza Exp $

#ifndef _SAVE_SLOT_HH
#define _SAVE_SLOT_HH

#include "../view/MainFrame.hh"

/// SRAM offset for the primary checksum
#define CHECKSUM_OFFSET 0x00

/// SRAM offset for the moon phases
#define MOON_OFFSET 0x01

/// SRAM offset for the hero's name
#define NAME_OFFSET 0x02

/// Starting SRAM offset for virtues 
#define VIRTUE_OFFSET 0x0C

/// SRAM offset for partial avatarhoods
#define AVATAR_OFFSET 0x14

/// Starting SRAM offset for the party members
#define MEMBER_OFFSET 0x15

/// SRAM offset for Stones
#define STONES_OFFSET 0x19

/// SRAM offset for Runes
#define RUNES_OFFSET 0x1A

/// Starting SRAM offset for magic
#define MAGIC_OFFSET 0x1B

/// Starting SRAM offset for herbs
#define HERB_OFFSET 0x1F

/// SRAM offset for gold
#define GOLD_OFFSET 0x27

/// Starting SRAM offset for tools
#define TOOL_OFFSET 0x29

/// Starting SRAM offset for equipment
#define EQUIPMENT_OFFSET 0x39

/// Starting SRAM offset for chracater levels
#define LEVEL_OFFSET 0x69

/// Starting SRAM offset for chracater current HP
#define CURRENT_HP_OFFSET 0x71

/// Starting SRAM offset for chracater max HP
#define MAX_HP_OFFSET 0x81

/// Starting SRAM offset for chracater current MP
#define CURRENT_MP_OFFSET 0x91

/// Starting SRAM offset for chracater max MP
#define MAX_MP_OFFSET 0x99

/// Starting SRAM offset for chracater strength
#define STRENGTH_OFFSET 0xA1

/// Starting SRAM offset for chracater intelligence
#define INTELLIGENCE_OFFSET 0xA9

/// Starting SRAM offset for chracater dexterity
#define DEXTERITY_OFFSET 0xB1

/// Starting SRAM offset for chracater experience
#define EXPERIENCE_OFFSET 0xB9

namespace hack4u {
    /// The two moons of Ultima
    enum Moons {TRAMMEL, FELUCCA};
    
    /// The eight cities of virtue
    enum City {MOONGLOW, BRITAIN, JHELOM, YEW, 
               MINOC, TRINSIC, SKARABRAE, MAGINCIA};
               
    /// The eight virtues
    enum Virtues {HONESTY, COMPASSION, VALOR, JUSTICE,
                  SACRIFICE, HONOR, SPIRITUALITY, HUMILITY};
    
    /// The eight characters
    enum Characters {MAGE, BARD, FIGHTER, DRUID, 
                     TINKER, PALADIN, RANGER, SHEPHERD};
                     
    /// The possible magic in the game
    enum Magic {LIGHT, MISSILE, AWAKEN, CURE, WIND, HEAL, FIRE, EXIT, DISPEL,
                VIEW, PROTECT, ICE, BLINK, ENERGY, QUICK, INVALID1, SLEEP,
                REFLECT, NEGATE, INVALID2, DESTROY, JINX, SQUISH, GATE,
                TREMOR, LIFE, INVALID3, DEFEAT};
                
    /// The eight herbs (reagents)
    enum Herbs {ASH, GINSENG, GARLIC, SILKWEB, MOSS, PEARL, FUNGUS, MANROOT};
    
    /// The tools
    enum Tools {TORCH, GEM, KEY, OIL, SEXTANT, SCALE, FLUTE, CANDLE, BOOK,
                BELL, WHEEL, HORN, SKULL, TRUTHKEY, COURAGEKEY, LOVEKEY};
    
    class MainFrame;
    
    /**
     * A class representing a single game save slot.
     */
    class SaveSlot {
    public:
        /**
         * Constructor for a SaveSlot.
         *
         * @param data The SRAM data
         */
        SaveSlot(const unsigned char *data);
        
        /**
         * Destructor for a SaveSlot.
         */
        ~SaveSlot();
        
        /**
         * Generates the checksum for the current data.
         *
         * @return The checksum.
         */
        unsigned char checksum() const;
        
        /**
         * Queries if this save slot is valid. Initially determined by
         * generating a checksum on the provided data and checking it against
         * the contained checksum, just like the real game.
         *
         * @return true if valid; false otherwise.
         */
        bool isValid() const { return valid; }
        
        /**
         * Queries if this SaveSlot has been modified.
         *
         * @return true if modified; false otherwise.
         */
        bool isModified() const { return modified; }
        
        /**
         * Gets the current phase of one of the moons. Valid values are either
         * TRAMMEL or FELUCCA.
         *
         * @param moon The moon whose phase to return.
         *
         * @return The phase of the moon. Note that felucca's phase depends upon
         *         trammel's phase and can be only 0, 1, or 2 representing one
         *         of the three destination cities. Trammel's phase will always
         *         be one of the eight cities of virtue.
         */
        int getPhase(int moon) const;
        
        /**
         * Sets the phases of the moons.
         *
         * @param trammel The phase for trammel. Must be one of the eight cities
         *                of virtue.
         * @param felucca The phase for felucca. Must be 0, 1, or 2 representing
         *                one of the three destination cities from Trammel.
         */
        void setPhase(int trammel, int felucca);
        
        /**
         * Gets the Hero's Name.
         *
         * @return wxString with the name of the Hero translated to a proper
         *         PC alphabet.
         */
        wxString getHerosName() const;
        
        /**
         * Sets the Hero's Name.
         *
         * @param name The new name of the hero. Valid values must not exceed 5
         *             characters. Excess lengths will be ignored.
         */
        void setHerosName(wxString &name);
        
        /**
         * Gets the value for one of the eight virtues.
         *
         * @param virtue The virtue whose value to retrieve. Must be one of the
         *               eight virtues in the Virtues enumeration.
         *
         * @return The value for the particular virtue.
         */
        int getVirtue(int virtue) const;
        
        /**
         * Sets the value for one of the eight virtues.
         *
         * @param virtue The virtue to set. Must be one of the eight virtues in
         *               the Virtues enumeration.
         * @param value The new value for the virtue.
         */
        void setVirtue(int virtue, unsigned char value);
        
        /**
         * Gets the party member at a given position.
         *
         * @param position The party position number (0-3).
         *
         * @return The character at that position. Return values range between
         *         0 and 1 + one of the character values in the Characters
         *         enumeration. 1 = Mage, 8 = Shepherd, 0 = No one.
         */
        int getMember(int position) const;
        
        /**
         * Sets the party member at a given position.
         *
         * @param position The party position number (0-3).
         * @param character What character class should be here, or 0 for no
         *                  one. Use the Characters enumeration + 1 for proper
         *                  character values (e.g. MAGE + 1).
         */
        void setMember(int position, int character);
        
        /**
         * Queries if the party has a particular stone in their inventory.
         *
         * @param stone The stone to check for. Valid values are one of the
         *              eight virtues in the Virtues enumeration.
         *
         * @return true if they have the stone; false otherwise.
         */
        bool hasStone(int stone) const;
        
        /**
         * Sets whether the party has a particular stone or not.
         *
         * @param stone The stone. Valid values are one of the eight virtues in
         *              the Virtues enumeration.
         * @param give true to give the stone; false to take it away.
         */
        void setStone(int stone, bool give = true);
        
        /**
         * Queries whether the party has a particular rune or not.
         *
         * @param rune The rune. Valid values are one of the eight virtues in
         *             the Virtues enumeration.
         *
         * @return true if they have the rune; false otherwise.
         */
        bool hasRune(int rune) const;
        
        /**
         * Sets whether the party has a particular rune of not.
         *
         * @param rune The rune. Valid values are one of the eight virtues in
         *             the Virtues enumeration.
         * @param give true to give the rune; false to take it away.
         */
        void setRune(int rune, bool give = true);
        
        /**
         * Queries whether the party has a particular magic or not.
         */
        bool hasMagic(int magic) const;
        
        /**
         * Sets whether the party has a particular magic of not.
         * 
         * @param magic The magic. Valid values are any of the members in the
         *              Magic enumeration other than INVALID.
         * @param give true to give the magic; false to take it away.
         */
        void setMagic(int magic, bool give = true);
        
        /**
         * Gets the current amount of a particular herb the party has.
         *
         * @param herb The herb whose value to get. Valid values are any of the
         *             members of the Herbs enumeration.
         *
         * @return The amount of the particular herb the party has.
         */
        int getHerb(int herb) const;
        
        /**
         * Sets the amount of a particular herb the party has.
         *
         * @param herb The herb whose value to set. Valid values are any of the
         *             members of the Herbs enumeration.
         * @param value The new value.
         */
        void setHerb(int herb, unsigned char value);
        
        /**
         * Gets the amount of gold held by the party.
         *
         * @return The amount of gold.
         */
        wxInt16 getGold() const;
        
        /**
         * Sets the amount of gold held by the party.
         *
         * @param gold The new amount of gold.
         */
        void setGold(wxInt16 gold);
        
        /**
         * Gets the amount of a tool the party has.
         *
         * @param tool The tool to get the amount of.
         *
         * @return The amount of the particular tool.
         */
        int getTool(int tool) const;
        
        /**
         * Sets the amount of a tool the party has.
         *
         * @param tool The tool to set the amount of.
         * @param value The new amount.
         */
        void setTool(int tool, unsigned char value = 1);
        
        /**
         * Gets the item held by a particular player in a particular slot.
         *
         * @param character The character whose equipment to get. Valid values
         *                  are in the Character enumeration.
         * @param slot The inventory slot (0-5).
         *
         * @return The equipment item.
         */
        int getEquipment(int character, int slot) const;
        
        /**
         * Sets the item held by a particular player in a particular slot.
         *
         * @param character The character whose equipment to set. Valid values
         *                  are in the Character enumeration.
         * @param slot The inventory slot (0-5).
         * @param value The new item value.
         */
        void setEquipment(int character, int slot, unsigned char value);
        
        /**
         * Gets the level of a character.
         *
         * @param character The character. Valid values are in the Character
         *                  enumeration.
         *
         * @return The character's level.
         */
        int getLevel(int character) const;
        
        /**
         * Sets the level of a character.
         *
         * @param character The character. Valid values are in the Character
         *                  enumeration.
         * @param value The new level.
         */
        void setLevel(int character, unsigned char value);
        
        /**
         * Gets the current HP of a character.
         *
         * @param character The character. Valid values are in the Character
         *                  enumeration.
         *
         * @return The current HP.
         */
        wxInt16 getCurrentHP(int character) const;
        
        /**
         * Sets the current HP of a character.
         *
         * @param character The character. Valid values are in the Character
         *                  enumeration.
         * @param value The new current HP.
         */
        void setCurrentHP(int character, wxInt16 value);
        
        /**
         * Gets the max HP of a character.
         * 
         * @param character The character. Valid values are in the Character
         *                  enumeration.
         *
         * @return The Max HP.
         */
        wxInt16 getMaxHP(int character) const;
        
        /**
         * Sets the max HP of a character.
         *
         * @param character The character. Valid values are in the Character
         *                  enumeration.
         * @param value The new max HP.
         */
        void setMaxHP(int character, wxInt16 value);
        
        /**
         * Gets the current MP of a character.
         *
         * @param character The character. Valid values are in the Character
         *                  enumeration.
         *
         * @return The current MP.
         */
        int getCurrentMP(int character) const;
        
        /**
         * Sets the current MP of a character.
         *
         * @param character The character. Valid values are in the Character
         *                  enumeration.
         * @param value The new current MP.
         */
        void setCurrentMP(int character, unsigned char value);
        
        /**
         * Gets the max MP of a character.
         *
         * @param character The character. Valid values are in the Character
         *                  enumeration.
         *
         * @return The max MP.
         */
        int getMaxMP(int character) const;
        
        /**
         * Sets the max MP of a charcter.
         *
         * @param character The character. Valid values are in the Character
         *                  enumeration.
         * @param value The new max MP.
         */
        void setMaxMP(int character, unsigned char value);

        /**
         * Gets the strength of a character.
         *
         * @param character The character. Valid values are in the Character
         *                  enumeration.
         *
         * @return The strength.
         */        
        int getStrength(int character) const;
        
        /**
         * Sets the strength of a charater.
         *
         * @param character The character. Valid values are in the Character
         *                  enumeration.
         * @param value The new strength.
         */
        void setStrength(int character, unsigned char value);
        
        /**
         * Gets the intelligence of a character.
         *
         * @param character The character. Valid values are in the Character
         *                  enumeration.
         *
         * @return The intelligence.
         */
        int getIntelligence(int character) const;
        
        /**
         * Sets the intelligence of a character.
         *
         * @param character The character. Valid values are in the Character
         *                  enumeration.
         * @param value The new intelligence.
         */
        void setIntelligence(int character, unsigned char value);
        
        /**
         * Gets the dexterity of a character.
         *
         * @param character The character. Valid values are in the Character
         *                  enumeration.
         *
         * @return The dexterity.
         */
        int getDexterity(int character) const;
        
        /**
         * Sets the dexterity of a character.
         *
         * @param character The character. Valid values are in the Character
         *                  enumeration.
         * @param value The new dexterity.
         */
        void setDexterity(int character, unsigned char value);
        
        /**
         * Gets the experience of a character.
         *
         * @param character The character. Valid values are in the Character
         *                  enumeration.
         *
         * @return The experience.
         */
        wxInt16 getExperience(int character) const;
        
        /**
         * Sets the experience of a character.
         *
         * @param character The character. Valid values are in the Character
         *                  enumeration.
         * @param value The new experience.
         */
        void setExperience(int character, wxInt16 value);
        
        friend class MainFrame;
    private:
        /**
         * Sets whether this slot is modified or not.
         *
         * @param modified true if modified; false otherwise.
         */
        void setModified(bool modified = true);
        
        /**
         * Translates an ASCII character to the Ultima alphabet.
         *
         * @param letter The letter to translate.
         *
         * @return The translated character.
         */
        static unsigned char toNES(char letter);
        
        /**
         * Translates an Ultima alphabet character to ASCII.
         *
         * @param letter The letter to translate.
         *
         * @return The translated character.
         */
        static char fromNES(unsigned char letter);

        unsigned char *nvram;
        bool valid;
        bool modified;
        
        /// Array of checksum xors used by the sanity algorithm.
        static const int CHECKSUM_XORS[];
    };
}

#endif

