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

// $Id: MainFrame.hh,v 1.18 2004/12/03 03:05:48 technoplaza Exp $

#ifndef _MAIN_FRAME_HH_
#define _MAIN_FRAME_HH_

#include <wx/xrc/xmlres.h>
#include <wx/frame.h>
#include <wx/notebook.h>
#include <wx/spinctrl.h>

#include "../model/SaveSlot.hh"
#include "FileDropTarget.hh"

#define SRAM_OFFSET 0x1A00
#define SRAM_SIZE 0x2000
#define SAVE_SIZE 0x200
#define SANITY_OFFSET 0x1900
#define SANITY_XOR1 0xAA
#define SANITY_XOR2 0x55

namespace hack4u {
    class SaveSlot;
    class FileDropTarget;
    
    class MainFrame : public wxFrame
    {
    public:
        MainFrame();
        void CreateControls();
        
        friend class FileDropTarget;
    private:
        DECLARE_DYNAMIC_CLASS(MainFrame)
        DECLARE_EVENT_TABLE()
        
        void setFeluccaOptions(int);
        void loadStats(SaveSlot &, int);
        void loadGame(int);

        void load(wxString &);
        void fileLoad(wxCommandEvent &);
        
        bool isValidParty();
        bool hasValidEquipment(int);
        
        bool save(wxString &);
        void fileSave(wxCommandEvent &);
        void fileSaveAs(wxCommandEvent &);
        
        bool isOpen() { return open; }
        void setOpen(bool);
        
        bool close();
        void fileClose(wxCommandEvent &);
        void fileExit(wxCommandEvent &);
        
        void windowClosing(wxCloseEvent &);
        
        void gameChange(wxCommandEvent &);
        void helpAbout(wxCommandEvent &);
        
        void herosNameChange(wxCommandEvent &);
        void memberClassChange(wxCommandEvent &);
        void virtueChange(wxScrollEvent &);
        void magicChange(wxCommandEvent &);
        void phaseChange(wxCommandEvent &);
        
        void goldChange(wxCommandEvent &);
        void herbChange(wxScrollEvent &);
        void runeChange(wxCommandEvent &);
        void stoneChange(wxCommandEvent &);
        void toolQuantityChange(wxScrollEvent &);
        void toolHaveChange(wxCommandEvent &);
        
        void characterChange(wxCommandEvent &);
        void statChange(wxCommandEvent &);
        
        void setEquipment(int);
        void equipmentChange(wxCommandEvent &);
        void equippedChange(wxCommandEvent &);

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
        
        static const wxString CITY_NAMES[];
        static const wxString CHARACTER_NAMES[];
        static const char *ICON[];
    };
}

#endif

