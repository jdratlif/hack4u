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

// $Id: SaveSlot.hh,v 1.19 2008/12/16 22:12:52 jdratlif Exp $

#ifndef HACK4U_SAVESLOT_HH_
#define HACK4U_SAVESLOT_HH_

#include <utility>

#include <wx/string.h>

#include "model/SRAMFile.hh"

namespace hack4u {
    /**
     * A class representing a single game save slot.
     */
    class SaveSlot {
        friend void SRAMFile::save(const wxString &);
        
    private:
        unsigned char *nvram;
        bool modified;
        
        /// Array of checksum xors used by the sanity algorithm.
        static const int CHECKSUM_XORS[];
        
        /**
         * Sets whether this slot is modified or not.
         *
         * @param modified true if modified; false otherwise.
         */
        void setModified(bool modified = true);
        
        /**
         * Translates an Ultima alphabet character to ASCII.
         *
         * @param letter The letter to translate.
         *
         * @return The translated character.
         */
        static char fromNES(unsigned char letter);
        
        /**
         * Translates an ASCII character to the Ultima alphabet.
         *
         * @param letter The letter to translate.
         *
         * @return The translated character.
         */
        static unsigned char toNES(char letter);

    public:
        /**
         * Constructor for a SaveSlot.
         *
         * @param data The SRAM data
         */
        SaveSlot(const char *data);
        
        /**
         * Destructor for a SaveSlot.
         */
        ~SaveSlot();
        
        /**
         * Gets the location of the Balloon.
         *
         * @return The Balloon's location (latitude, longitude).
         */
        std::pair<int, int> getBalloonLocation() const;
        
        /**
         * Sets the baloon's location.
         *
         * @param location The new location (latitude, longitude).
         */
        void setBalloonLocation(std::pair<int, int> location); 
        
        /**
         * Gets the current HP of a character.
         *
         * @param character The character.
         *
         * @return The current HP.
         */
        wxInt16 getCurrentHP(enum Character character) const;
        
        /**
         * Sets the current HP of a character.
         *
         * @param character The character.
         * @param value The new current HP.
         */
        void setCurrentHP(enum Character character, wxInt16 value);
        
        /**
         * Gets the current MP of a character.
         *
         * @param character The character.
         *
         * @return The current MP.
         */
        int getCurrentMP(enum Character character) const;
        
        /**
         * Sets the current MP of a character.
         *
         * @param character The character.
         * @param value The new current MP.
         */
        void setCurrentMP(enum Character character, unsigned char value);
        
        /**
         * Gets the dexterity of a character.
         *
         * @param character The character.
         *
         * @return The dexterity.
         */
        int getDexterity(enum Character character) const;
        
        /**
         * Sets the dexterity of a character.
         *
         * @param character The character.
         * @param value The new dexterity.
         */
        void setDexterity(enum Character character, unsigned char value);
        
        /**
         * Gets the item held by a particular player in a particular slot.
         *
         * @param character The character whose equipment to get.
         * @param slot The inventory slot (0-5).
         *
         * @return The equipment item.
         */
        int getEquipment(enum Character character, int slot) const;
        
        /**
         * Sets the item held by a particular player in a particular slot.
         *
         * @param character The character whose equipment to set.
         * @param slot The inventory slot (0-5).
         * @param value The new item value.
         */
        void setEquipment(enum Character character,
                          int slot, unsigned char value);
        
        /**
         * Gets the experience of a character.
         *
         * @param character The character.
         *
         * @return The experience.
         */
        wxInt16 getExperience(enum Character character) const;
        
        /**
         * Sets the experience of a character.
         *
         * @param character The character.
         * @param value The new experience.
         */
        void setExperience(enum Character character, wxInt16 value);
        
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
         * Gets the current amount of a particular herb the party has.
         *
         * @param herb The herb whose value to get.
         *
         * @return The amount of the particular herb the party has.
         */
        int getHerb(enum Herb herb) const;
        
        /**
         * Sets the amount of a particular herb the party has.
         *
         * @param herb The herb whose value to set.
         * @param value The new value.
         */
        void setHerb(enum Herb herb, unsigned char value);
        
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
        void setHerosName(const wxString &name);
        
        /**
         * Gets the intelligence of a character.
         *
         * @param character The character.
         *
         * @return The intelligence.
         */
        int getIntelligence(enum Character character) const;
        
        /**
         * Sets the intelligence of a character.
         *
         * @param character The character.
         * @param value The new intelligence.
         */
        void setIntelligence(enum Character character, unsigned char value);
        
        /**
         * Checks if a character has joined the party or not.
         *
         * @param character The character.
         *
         * @return true if the character has joined; false otherwise.
         */
        bool hasJoined(enum Character character) const;
        
        /**
         * Sets whether a character has joined the party or not.
         *
         * @param character The character.
         * @param value true if joined; false otherwise.
         */
        void setJoined(enum Character character, bool value);
        
        /**
         * Gets the level of a character.
         *
         * @param character The character.
         *
         * @return The character's level.
         */
        int getLevel(enum Character character) const;
        
        /**
         * Sets the level of a character.
         *
         * @param character The character.
         * @param value The new level.
         */
        void setLevel(enum Character character, unsigned char value);
        
        /**
         * Queries whether the party has a particular magic or not.
         *
         * @param magic The magic to check for.
         */
        bool hasMagic(enum Magic magic) const;
        
        /**
         * Sets whether the party has a particular magic of not.
         * 
         * @param magic The magic. Valid values are any of the members in the
         *              Magic enumeration other than INVALIDx.
         * @param give true to give the magic; false to take it away.
         */
        void setMagic(enum Magic magic, bool give = true);
        
        /**
         * Gets the max HP of a character.
         * 
         * @param character The character.
         *
         * @return The Max HP.
         */
        wxInt16 getMaxHP(enum Character character) const;
        
        /**
         * Sets the max HP of a character.
         *
         * @param character The character.
         * @param value The new max HP.
         */
        void setMaxHP(enum Character character, wxInt16 value);
        
        /**
         * Gets the max MP of a character.
         *
         * @param character The character.
         *
         * @return The max MP.
         */
        int getMaxMP(enum Character character) const;
        
        /**
         * Sets the max MP of a charcter.
         *
         * @param character The character.
         * @param value The new max MP.
         */
        void setMaxMP(enum Character character, unsigned char value);
        
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
         * Queries if this SaveSlot has been modified.
         *
         * @return true if modified; false otherwise.
         */
        bool isModified() const;
        
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
        int getPhase(enum Moon moon) const;
        
        /**
         * Sets the phases of the moons.
         *
         * @param trammel The phase for trammel. Must be one of the eight cities
         *                of virtue.
         * @param felucca The phase for felucca. Must be 0, 1, or 2 representing
         *                one of the three destination cities from Trammel.
         */
        void setPhase(enum City trammel, int felucca);
        
        /**
         * Checks if the party has captured a particular ship.
         *
         * @param ship The ship to check for.
         *
         * @return true if the ship has been taken; false otherwise.
         */
        bool hasPirateShip(enum PirateShip ship) const;
        
        /**
         * Sets whether the party has a particular pirate ship or not.
         *
         * @param ship The pirate ship.
         * @param give true to give the ship; false otherwise.
         */
        void setPirateShip(enum PirateShip ship, bool give);
        
        /**
         * Gets the location of one of the captured pirate ships.
         *
         * @param ship The ship.
         *
         * @return The location of the ship (latitude, longitude).
         */
        std::pair<int, int> getPirateShipLocation(enum PirateShip ship) const;
        
        /**
         * Sets the location of a captured pirate ship.
         *
         * @param ship The pirate ship.
         * @param location The location (latitude, longitude).
         */
        void setPirateShipLocation(enum PirateShip ship,
                                   std::pair<int, int> location);
        
        /**
         * Queries whether the party has a particular rune or not.
         *
         * @param rune The rune.
         *
         * @return true if they have the rune; false otherwise.
         */
        bool hasRune(enum Virtue rune) const;
        
        /**
         * Sets whether the party has a particular rune of not.
         *
         * @param rune The rune.
         * @param give true to give the rune; false to take it away.
         */
        void setRune(enum Virtue rune, bool give = true);
        
        /**
         * Gets the start location.
         *
         * @return The start location.
         */
        enum StartLocation getStartLocation() const;
        
        /**
         * Sets the start location.
         *
         * @param location The start location.
         */
        void setStartLocation(enum StartLocation location);
        
        /**
         * Queries if the party has a particular stone in their inventory.
         *
         * @param stone The stone to check for.
         *
         * @return true if they have the stone; false otherwise.
         */
        bool hasStone(enum Virtue stone) const;
        
        /**
         * Sets whether the party has a particular stone or not.
         *
         * @param stone The stone.
         * @param give true to give the stone; false to take it away.
         */
        void setStone(enum Virtue stone, bool give = true);
        
        /**
         * Gets the strength of a character.
         *
         * @param character The character.
         *
         * @return The strength.
         */        
        int getStrength(enum Character character) const;
        
        /**
         * Sets the strength of a charater.
         *
         * @param character The character.
         * @param value The new strength.
         */
        void setStrength(enum Character character, unsigned char value);
        
        /**
         * Gets the amount of a tool the party has.
         *
         * @param tool The tool to get the amount of.
         *
         * @return The amount of the particular tool.
         */
        int getTool(enum Tool tool) const;
        
        /**
         * Sets the amount of a tool the party has.
         *
         * @param tool The tool to set the amount of.
         * @param value The new amount.
         */
        void setTool(enum Tool tool, unsigned char value = 1);
        
        /**
         * Gets the value for one of the eight virtues.
         *
         * @param virtue The virtue whose value to retrieve.
         *
         * @return The value for the particular virtue.
         */
        int getVirtue(enum Virtue virtue) const;
        
        /**
         * Sets the value for one of the eight virtues.
         *
         * @param virtue The virtue to set.
         * @param value The new value for the virtue.
         */
        void setVirtue(enum Virtue virtue, unsigned char value);
        
        /**
         * Gets the location of the whirlpool.
         *
         * @return The location.
         */
        std::pair<int, int> getWhirlpoolLocation() const;
        
        /**
         * Sets the location of the whirlpool.
         *
         * @param location The location.
         */
        void setWhirlpoolLocation(std::pair<int, int> location);
        
        /**
         * Generates the checksum for the current data.
         *
         * @return The checksum.
         */
        unsigned char checksum() const;
    };
    
    inline bool SaveSlot::isModified() const
        { return modified; }
}

#endif

