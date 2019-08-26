/*
 * hack4u
 * Copyright (C) 2004-2006 emuWorks
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

// $Id: MainFrame.hh,v 1.39 2006/03/21 12:00:18 technoplaza Exp $

#ifndef _MAINFRAME_HH_
#define _MAINFRAME_HH_

#include "model/ModelConstants.hh"

namespace hack4u {
    class SaveSlot;
    class SRAMFile;
    
    /// the possible locations for the location menu
    enum Location {
        LMOONGLOW, LBRITAIN, LJHELOM, LYEW, LMINOC, LTRINSIC, LSKARABRAE,
        LMAGINCIA, LLYCAEUM, LEMPATHABBEY, LSERPENTSHOLD, LPAWS, LVESPER,
        LBUCCANEERSDEN, LCOVE
    };
    
    /**
     * The main frame of the application.
     */
    class MainFrame : public wxFrame {
        DECLARE_CLASS(MainFrame)
        DECLARE_EVENT_TABLE()
        
        friend class FileDropTarget;
        
    private:
        wxCheckBox *itemEquippedCheck[6];
        wxChoice *itemChoice[6];
        wxChoice *memberChoice[4];
        wxString sramFile;
        SaveSlot *saveslot;
        SRAMFile *sram;
        enum Location location;
        int gameMenu, locationMenu;
        bool ignoreEvents;
        bool open;
        
        /// Array of the character class names.
        static const wxString CHARACTER_NAMES[];
        
        /// Array of the names of the eight cities of virtue.
        static const wxString CITY_NAMES[];
        
        /// Array of locations for the balloon
        static const std::pair<int, int> BALLOON_LOCATIONS[];
        
        /// Array of locations for the pirate ships
        static const std::pair<int, int> PIRATESHIP_LOCATIONS[];
        
        /// Array of indicies mapping start locations to choice selection
        static const int INN_INDEX[];
        
        /**
         * Sets up the controls for this Frame.
         */
        void CreateControls();
        
        /**
         * Sets the equipment value for a particular slot.
         *
         * @param slot The slot to set (0-5).
         */
        void setEquipment(int slot);
        
        /**
         * Changes the options for the Felucca moon control depending upon the
         * phase of Trammel.
         *
         * @param trammel The phase of trammel.
         */
        void setFeluccaOptions(enum City trammel);
        
        /**
         * Checks if an SRAM file is currently open.
         *
         * @return true if open; false otherwise.
         */
        bool isOpen();
        
        /**
         * Checks if a character has valid equipment.
         *
         * @param character The character.
         * 
         * @return true if valid; false otherwise.
         */
        bool hasValidEquipment(enum Character character) const;
        
        /**
         * Checks if the current party formation is valid.
         *
         * @return true if valid; false otherwise.
         */
        bool isValidParty() const;

        /**
         * Closes the current SRAM file.
         *
         * @return true if closed; false otherwise.
         */
        bool close();
        
        /**
         * Loads an SRAM file.
         *
         * @param filename The SRAM file.
         */
        void load(const wxString &filename);
        
        /**
         * Loads the game values into the frame controls.
         *
         * @param game The game number to load (0, 1, or 2).
         */
        void loadGame(int game);
        
        /**
         * Loads the stats of a particular character into the character tab.
         *
         * @param character The character.
         */
        void loadStats(enum Character character);
        
        /**
         * Saves the SRAM to disk.
         *
         * @param filename The filename to save the SRAM to.
         *
         * @return true if saved; false otherwise.
         */
        bool save(const wxString &filename);
        
        /**
         * Callback when the Balloon's location is changed.
         *
         * @param event The associated command event.
         */
        void onBalloonChange(wxCommandEvent &event);
        
        /**
         * Callback when one of the characters is selected.
         * 
         * @param event The associated command event.
         */
        void onCharacterChange(wxCommandEvent &event);
        
        /**
         * Callback when a characters equipment is changed.
         * 
         * @param event The associated command event.
         */
        void onEquipmentChange(wxCommandEvent &event);
        
        /**
         * Callback when a character's equipped item is changed.
         * 
         * @param event The associated command event.
         */
        void onEquippedChange(wxCommandEvent &event);
        
        /**
         * Callback to update the equipped checkboxes.
         *
         * @param event The associated update UI event.
         */
        void onEquippedUpdate(wxUpdateUIEvent &event);
        
        /**
         * Callback when close is selected from the file menu.
         * 
         * @param event The associated command event.
         */
        void onFileClose(wxCommandEvent &event);
        
        /**
         * Callback when exit is selected from the file menu.
         * 
         * @param event The associated command event.
         */
        void onFileExit(wxCommandEvent &event);

        /**
         * Callback when open is selected from the file menu.
         *
         * @param event The associated command event.
         */
        void onFileOpen(wxCommandEvent &event);
        
        /**
         * Callback when save is selected from the file menu.
         *
         * @param event The associated command event.
         */
        void onFileSave(wxCommandEvent &event);
        
        /**
         * Callback when save as is selected from the file menu.
         * 
         * @param event The associated command event.
         */
        void onFileSaveAs(wxCommandEvent &event);
        
        /**
         * Callback when one of the game menu items are selected.
         * 
         * @param event The associated command event.
         */
        void onGameChange(wxCommandEvent &event);
        
        /**
         * Callback when the game menu needs updated.
         *
         * @param event The associated update UI event.
         */
        void onGameMenuUpdate(wxUpdateUIEvent &event);
        
        /**
         * Callback when the gold amount is changed.
         * 
         * @param event The associated command event.
         */
        void onGoldChange(wxCommandEvent &event);
        
        /**
         * Callback when about is selected from the help menu.
         * 
         * @param event The associated command event.
         */
        void onHelpAbout(wxCommandEvent &event);
        
        /**
         * Callback when one of the herbs is changed.
         * 
         * @param event The associated scroll event.
         */
        void onHerbChange(wxScrollEvent &event);
        
        /**
         * Callback when the hero's name is changed.
         * 
         * @param event The associated command event.
         */
        void onHerosNameChange(wxCommandEvent &event);
        
        /**
         * Callback when one of the joined members is changed.
         *
         * @param event The associated command event.
         */
        void onJoinedChange(wxCommandEvent &event);
        
        /**
         * Callback when balloon is selected from the location menu.
         *
         * @param event The associated command event.
         */
        void onLocationBalloon(wxCommandEvent &event);
        
        /**
         * Callback when the location place is changed.
         *
         * @param event The associated command event.
         */
        void onLocationPlaceChange(wxCommandEvent &event);
        
        /**
         * Callback when a ship is selected from the location menu.
         *
         * @param event The associated command event.
         */
        void onLocationShip(wxCommandEvent &event);
        
        /**
         * Callback when one of the magics is changed.
         * 
         * @param event The associated command event.
         */
        void onMagicChange(wxCommandEvent &event);
        
        /**
         * Callback when one of the member's classes is changed.
         * 
         * @param event The associated command event.
         */
        void onMemberClassChange(wxCommandEvent &event);
        
        /**
         * Callback when the party member choices need updated.
         *
         * @param event The associated update UI event.
         */
        void onMemberUpdate(wxUpdateUIEvent &event);
        
        /**
         * Callback when one of the moon phases is changed.
         * 
         * @param event The associated command event.
         */
        void onPhaseChange(wxCommandEvent &event);
        
        /**
         * Callback when one of the runes is changed.
         * 
         * @param event The associated command event.
         */
        void onRuneChange(wxCommandEvent &event);
        
        /**
         * Callback when the save or close file menu items need updating.
         *
         * @param event The associated update UI event.
         */
        void onSaveCloseUpdate(wxUpdateUIEvent &event);
        
        /**
         * Callback when the save as file menu item needs updating.
         *
         * @param event The associated update UI event.
         */
        void onSaveUpdate(wxUpdateUIEvent &event);
        
        /**
         * Callback when one the pirate ships is changed.
         *
         * @param event The associated command event.
         */
        void onShipChange(wxCommandEvent &event);
        
        /**
         * Callback when the location of a pirate ship is changed.
         *
         * @param event The associated command event.
         */
        void onShipLocationChange(wxCommandEvent &event);
        
        /**
         * Callback when a ship location item needs updating.
         *
         * @param event The associated update UI event.
         */
        void onShipUpdate(wxUpdateUIEvent &event);
        
        /**
         * Callback when the start location is changed.
         *
         * @param event The associated command event.
         */
        void onStartLocationChange(wxCommandEvent &event);
        
        /**
         * Callback when one of the character stats is changed.
         * 
         * @param event The associated command event.
         */
        void onStatChange(wxCommandEvent &event);
        
        /**
         * Callback when one of the stones is changed.
         * 
         * @param event The associated command event.
         */
        void onStoneChange(wxCommandEvent &event);
        
        /**
         * Callback when one of the have/have not tools is changed.
         * 
         * @param event The associated command event.
         */
        void onToolHaveChange(wxCommandEvent &event);
        
        /**
         * Callback when one of the quantity tools is changed.
         * 
         * @param event The associated scroll event.
         */
        void onToolQuantityChange(wxScrollEvent &event);
        
        /**
         * Callback when one of the virtue values is changed.
         * 
         * @param event The associated scroll event.
         */
        void onVirtueChange(wxScrollEvent &event);
        
        /**
         * Callback when the whirlpool's location is changed.
         *
         * @param event The associated command event.
         */
        void onWhirlpoolChange(wxCommandEvent &event);
        
        /**
         * Callback when the window is closing.
         * 
         * @param event The associated close event.
         */
        void onWindowClosing(wxCloseEvent &event);
        
    public:
        /**
         * Constructor for the MainFrame.
         */
        MainFrame();
    };
    
    inline bool MainFrame::isOpen()
        { return open; }
    
    inline void MainFrame::onCharacterChange(wxCommandEvent &event)
        { loadStats(static_cast<enum Character>(event.GetSelection())); }
        
    inline void MainFrame::onFileClose(wxCommandEvent &)
        { close(); }
    
    inline void MainFrame::onFileSave(wxCommandEvent &)
        { save(sramFile); }
        
    inline void MainFrame::onSaveCloseUpdate(wxUpdateUIEvent &event)
        { event.Enable(isOpen()); }
}

#endif

