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

// $Id: MainFrame.hh,v 1.14 2004/11/30 14:29:34 technoplaza Exp $

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
        
        void save(wxString &);
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
        void virtueChange(wxCommandEvent &);
        void magicChange(wxCommandEvent &);
        void phaseChange(wxCommandEvent &);
        
        void goldChange(wxCommandEvent &);
        void herbChange(wxCommandEvent &);
        void runeChange(wxCommandEvent &);
        void stoneChange(wxCommandEvent &);
        void toolQuantityChange(wxCommandEvent &);
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

        wxChoice *firstMemberClass;
        wxChoice *secondMemberClass;
        wxChoice *thirdMemberClass;
        wxChoice *fourthMemberClass;

        wxSpinCtrl *honestySpinner;
        wxSpinCtrl *compassionSpinner;
        wxSpinCtrl *valorSpinner;
        wxSpinCtrl *justiceSpinner;
        wxSpinCtrl *sacrificeSpinner;
        wxSpinCtrl *honorSpinner;
        wxSpinCtrl *spiritualitySpinner;
        wxSpinCtrl *humilitySpinner;

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

        wxSpinCtrl *goldSpinner;

        wxSpinCtrl *ashSpinner;
        wxSpinCtrl *ginsengSpinner;
        wxSpinCtrl *garlicSpinner;
        wxSpinCtrl *silkwebSpinner;
        wxSpinCtrl *mossSpinner;
        wxSpinCtrl *pearlSpinner;
        wxSpinCtrl *fungusSpinner;
        wxSpinCtrl *manrootSpinner;

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

        wxSpinCtrl *torchSpinner;
        wxSpinCtrl *gemSpinner;
        wxSpinCtrl *oilSpinner;

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

        wxSpinCtrl *levelSpinner;
        wxSpinCtrl *experienceSpinner;
        wxSpinCtrl *currentHPSpinner;
        wxSpinCtrl *currentMPSpinner;
        wxSpinCtrl *maxHPSpinner;
        wxSpinCtrl *maxMPSpinner;
        wxSpinCtrl *strengthSpinner;
        wxSpinCtrl *intelligenceSpinner;
        wxSpinCtrl *dexteritySpinner;

        wxChoice *itemChoice[6];
        wxCheckBox *itemEquippedCheck[6];
        
        static const wxString CITY_NAMES[];
    };
}

#endif

