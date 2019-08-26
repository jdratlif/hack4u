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

// $Id: MainFrame.hh,v 1.20 2005/08/03 11:11:39 technoplaza Exp $

#ifndef _MAIN_FRAME_HH_
#define _MAIN_FRAME_HH_

#include <wx/xrc/xmlres.h>
#include <wx/frame.h>
#include <wx/notebook.h>
#include <wx/spinctrl.h>

#include "../model/SaveSlot.hh"
#include "FileDropTarget.hh"

/// Starting offset within the SRAM of the save games
#define SRAM_OFFSET 0x1A00

/// The size of SRAM
#define SRAM_SIZE 0x2000

/// The size of a particular save game
#define SAVE_SIZE 0x200

/// The starting offset within the SRAM of the sanity values
#define SANITY_OFFSET 0x1900

/// The first sanity check XOR
#define SANITY_XOR1 0xAA

/// The second sanity check XOR
#define SANITY_XOR2 0x55

namespace hack4u {
    class SaveSlot;
    class FileDropTarget;
    
    /**
     * The main frame of the application.
     */
    class MainFrame : public wxFrame
    {
    public:
        /**
         * Constructor for the MainFrame.
         */
        MainFrame();
        
        /**
         * Sets up the controls for this Frame.
         */
        void CreateControls();
        
        friend class FileDropTarget;
    private:
        DECLARE_DYNAMIC_CLASS(MainFrame)
        DECLARE_EVENT_TABLE()
        
        /**
         * Changes the options for the Felucca moon control depending upon the
         * phase of Trammel.
         *
         * @param trammel The phase of trammel.
         */
        void setFeluccaOptions(int trammel);
        
        /**
         * Loads the stats of a particular character into the character tab.
         *
         * @param slot The current save slot.
         * @param character The character. Valid values are in the Characters
         *                  enumeration.
         */
        void loadStats(SaveSlot &slot, int character);
        
        /**
         * Loads the game values into the frame controls.
         *
         * @param game The game number to load (0, 1, or 2).
         */
        void loadGame(int game);

        /**
         * Loads an SRAM file.
         *
         * @param filename The SRAM file.
         */
        void load(wxString &filename);
        
        /**
         * Callback when open is selected from the file menu.
         *
         * @param event The associated command event.
         */
        void fileOpen(wxCommandEvent &event);
        
        /**
         * Checks if the current party formation is valid.
         *
         * @return true if valid; false otherwise.
         */
        bool isValidParty() const;
        
        /**
         * Checks if a character has valid equipment.
         *
         * @param character The character. Valid values are in the Characters
         *                  enumeration.
         * 
         * @return true if valid; false otherwise.
         */
        bool hasValidEquipment(int character) const;
        
        /**
         * Saves the SRAM to disk.
         *
         * @param filename The filename to save the SRAM to.
         *
         * @return true if saved; false otherwise.
         */
        bool save(wxString &filename);
        
        /**
         * Callback when save is selected from the file menu.
         *
         * @param event The associated command event.
         */
        void fileSave(wxCommandEvent &event);
        
        /**
         * Callback when save as is selected from the file menu.
         * 
         * @param event The associated command event.
         */
        void fileSaveAs(wxCommandEvent &event);
        
        /**
         * Checks if an SRAM file is currently open.
         *
         * @return true if open; false otherwise.
         */
        bool isOpen() { return open; }
        
        /**
         * Sets whether an SRAM file is open or not.
         *
         * @param open true if open; false otherwise.
         */
        void setOpen(bool open);
        
        /**
         * Closes the current SRAM file.
         *
         * @return true if closed; false otherwise.
         */
        bool close();
        
        /**
         * Callback when close is selected from the file menu.
         * 
         * @param event The associated command event.
         */
        void fileClose(wxCommandEvent &event);
        
        /**
         * Callback when exit is selected from the file menu.
         * 
         * @param event The associated command event.
         */
        void fileExit(wxCommandEvent &event);
        
        /**
         * Callback when the window is closing.
         * 
         * @param event The associated close event.
         */
        void windowClosing(wxCloseEvent &event);
        
        /**
         * Callback when one of the game menu items are selected.
         * 
         * @param event The associated command event.
         */
        void gameChange(wxCommandEvent &event);
        
        /**
         * Callback when about is selected from the help menu.
         * 
         * @param event The associated command event.
         */
        void helpAbout(wxCommandEvent &event);
        
        /**
         * Callback when the hero's name is changed.
         * 
         * @param event The associated command event.
         */
        void herosNameChange(wxCommandEvent &event);
        
        /**
         * Callback when one of the member's classes is changed.
         * 
         * @param event The associated command event.
         */
        void memberClassChange(wxCommandEvent &event);
        
        /**
         * Callback when one of the virtue values is changed.
         * 
         * @param event The associated scroll event.
         */
        void virtueChange(wxScrollEvent &event);
        
        /**
         * Callback when one of the magics is changed.
         * 
         * @param event The associated command event.
         */
        void magicChange(wxCommandEvent &event);
        
        /**
         * Callback when one of the moon phases is changed.
         * 
         * @param event The associated command event.
         */
        void phaseChange(wxCommandEvent &event);
        
        /**
         * Callback when the gold amount is changed.
         * 
         * @param event The associated command event.
         */
        void goldChange(wxCommandEvent &event);
        
        /**
         * Callback when one of the herbs is changed.
         * 
         * @param event The associated scroll event.
         */
        void herbChange(wxScrollEvent &event);
        
        /**
         * Callback when one of the runes is changed.
         * 
         * @param event The associated command event.
         */
        void runeChange(wxCommandEvent &event);
        
        /**
         * Callback when one of the stones is changed.
         * 
         * @param event The associated command event.
         */
        void stoneChange(wxCommandEvent &event);
        
        /**
         * Callback when one of the quantity tools is changed.
         * 
         * @param event The associated scroll event.
         */
        void toolQuantityChange(wxScrollEvent &event);
        
        /**
         * Callback when one of the have/have not tools is changed.
         * 
         * @param event The associated command event.
         */
        void toolHaveChange(wxCommandEvent &event);
        
        /**
         * Callback when one of the characters is selected.
         * 
         * @param event The associated command event.
         */
        void characterChange(wxCommandEvent &event);
        
        /**
         * Callback when one of the character stats is changed.
         * 
         * @param event The associated command event.
         */
        void statChange(wxCommandEvent &event);
        
        /**
         * Sets the equipment value for a particular slot.
         *
         * @param slot The slot to set (0-5).
         */
        void setEquipment(int slot);
        
        /**
         * Callback when a characters equipment is changed.
         * 
         * @param event The associated command event.
         */
        void equipmentChange(wxCommandEvent &event);
        
        /**
         * Callback when a characters equipped equipment is changed.
         * 
         * @param event The associated command event.
         */
        void equippedChange(wxCommandEvent &event);

        SaveSlot *saveslot[3];
        int currentSlot;
        bool open;
        
        char *sram;
        wxString sramFile;

        wxNotebook *notebook;
        
        wxMenuItem *games[3];
        wxMenuItem *fileSaveItem;
        wxMenuItem *fileSaveAsItem;
        wxMenuItem *fileCloseItem;

        wxTextCtrl *herosNameText;
        wxChoice *memberClass[4];

        wxSlider *honestySlider;
        wxSlider *compassionSlider;
        wxSlider *valorSlider;
        wxSlider *justiceSlider;
        wxSlider *sacrificeSlider;
        wxSlider *honorSlider;
        wxSlider *spiritualitySlider;
        wxSlider *humilitySlider;

        wxCheckBox *lightSpellCheck;
        wxCheckBox *missileSpellCheck;
        wxCheckBox *awakenSpellCheck;
        wxCheckBox *cureSpellCheck;
        wxCheckBox *windSpellCheck;
        wxCheckBox *healSpellCheck;
        wxCheckBox *fireSpellCheck;
        wxCheckBox *exitSpellCheck;
        wxCheckBox *dispelSpellCheck;
        wxCheckBox *viewSpellCheck;
        wxCheckBox *protectSpellCheck;
        wxCheckBox *iceSpellCheck;
        wxCheckBox *blinkSpellCheck;
        wxCheckBox *energySpellCheck;
        wxCheckBox *quickSpellCheck;
        wxCheckBox *sleepSpellCheck;
        wxCheckBox *reflectSpellCheck;
        wxCheckBox *negateSpellCheck;
        wxCheckBox *destroySpellCheck;
        wxCheckBox *jinxSpellCheck;
        wxCheckBox *squishSpellCheck;
        wxCheckBox *gateSpellCheck;
        wxCheckBox *tremorSpellCheck;
        wxCheckBox *lifeSpellCheck;
        wxCheckBox *defeatSpellCheck;

        wxChoice *trammelChoice;
        wxChoice *feluccaChoice;

        wxTextCtrl *goldText;

        wxSlider *ashSlider;
        wxSlider *ginsengSlider;
        wxSlider *garlicSlider;
        wxSlider *silkwebSlider;
        wxSlider *mossSlider;
        wxSlider *pearlSlider;
        wxSlider *fungusSlider;
        wxSlider *manrootSlider;

        wxCheckBox *honestyRuneCheck;
        wxCheckBox *compassionRuneCheck;
        wxCheckBox *valorRuneCheck;
        wxCheckBox *justiceRuneCheck;
        wxCheckBox *sacrificeRuneCheck;
        wxCheckBox *honorRuneCheck;
        wxCheckBox *spiritualityRuneCheck;
        wxCheckBox *humilityRuneCheck;

        wxCheckBox *blueStoneCheck;
        wxCheckBox *yellowStoneCheck;
        wxCheckBox *redStoneCheck;
        wxCheckBox *greenStoneCheck;
        wxCheckBox *orangeStoneCheck;
        wxCheckBox *purpleStoneCheck;
        wxCheckBox *whiteStoneCheck;
        wxCheckBox *blackStoneCheck;

        wxSlider *torchSlider;
        wxSlider *gemSlider;
        wxSlider *oilSlider;

        wxCheckBox *keyCheck;
        wxCheckBox *sextantCheck;
        wxCheckBox *scaleCheck;
        wxCheckBox *fluteCheck;
        wxCheckBox *candleCheck;
        wxCheckBox *bookCheck;
        wxCheckBox *bellCheck;
        wxCheckBox *hornCheck;
        wxCheckBox *skullCheck;
        wxCheckBox *truthKeyCheck;
        wxCheckBox *courageKeyCheck;
        wxCheckBox *loveKeyCheck;
        wxCheckBox *wheelCheck;

        wxChoice *characterChoice;

        wxTextCtrl *levelText;
        wxTextCtrl *experienceText;
        wxTextCtrl *currentHPText;
        wxTextCtrl *currentMPText;
        wxTextCtrl *maxHPText;
        wxTextCtrl *maxMPText;
        wxTextCtrl *strengthText;
        wxTextCtrl *intelligenceText;
        wxTextCtrl *dexterityText;

        wxChoice *itemChoice[6];
        wxCheckBox *itemEquippedCheck[6];
        
        /**
         * Array of the names of the eight cities of virtue.
         */
        static const wxString CITY_NAMES[];
        
        /**
         * Array of the character class names.
         */
        static const wxString CHARACTER_NAMES[];
        
        /**
         * XPM icon used for the Frame icon.
         */
        static const char *ICON[];
    };
}

#endif

