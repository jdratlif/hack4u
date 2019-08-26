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

// $Id: MainFrame.cc,v 1.50 2006/03/21 11:53:54 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/xrc/xmlres.h>

#include <cstring>
#include <fstream>

#include "hack4u.hh"
#include "exceptions/FileIOException.hh"
#include "exceptions/InvalidSRAMException.hh"
#include "res/icon16x16.xpm"
#include "model/SaveSlot.hh"
#include "view/FileDropTarget.hh"
#include "view/MainFrame.hh"

using namespace hack4u;

const wxString MainFrame::CHARACTER_NAMES[] = {
    wxT("Mage"), wxT("Bard"), wxT("Fighter"), wxT("Druid"),
    wxT("Tinker"), wxT("Paladin"), wxT("Ranger"), wxT("Shepherd")
};

const wxString MainFrame::CITY_NAMES[] = {
    wxT("Moonglow"), wxT("Britain"), wxT("Jhelom"), wxT("Yew"),
    wxT("Minoc"), wxT("Trinsic"), wxT("Skara Brae"), wxT("Magincia")
};

const std::pair<int, int> MainFrame::BALLOON_LOCATIONS[] = {
    std::pair<int, int>(131, 224), std::pair<int, int>(108, 84),
    std::pair<int, int>(218, 38), std::pair<int, int>(45, 57),
    std::pair<int, int>(22, 159), std::pair<int, int>(186, 104),
    std::pair<int, int>(130, 22), std::pair<int, int>(171, 188),
    
    std::pair<int, int>(106, 216), std::pair<int, int>(50, 26),
    std::pair<int, int>(244, 147),
    
    std::pair<int, int>(148, 96), std::pair<int, int>(59, 199),
    std::pair<int, int>(159, 136), std::pair<int, int>(92, 137)
};

const std::pair<int, int> MainFrame::PIRATESHIP_LOCATIONS[] = {
    std::pair<int, int>(134, 230), std::pair<int, int>(109, 84),
    std::pair<int, int>(222, 40), std::pair<int, int>(18, 57),
    std::pair<int, int>(19, 168), std::pair<int, int>(184, 108),
    std::pair<int, int>(127, 19), std::pair<int, int>(169, 190),
    
    std::pair<int, int>(108, 216), std::pair<int, int>(47, 26),
    std::pair<int, int>(242, 148),
    
    std::pair<int, int>(145, 96), std::pair<int, int>(59, 196),
    std::pair<int, int>(158, 134), std::pair<int, int>(92, 135)
};

const int MainFrame::INN_INDEX[] = {
    1, 1, 1, 1, 1, 0, 1, 2, 3, 4, 5, 6, 1, 1, 7
};

MainFrame::MainFrame() : saveslot(0), sram(0), location(LMOONGLOW),
                         ignoreEvents(false), open(false) {
    SetParent(NULL);
    CreateControls();
    GetSizer()->SetSizeHints(this);
    Centre();
    
    XRCCTRL(*this, "IDN_HACK4U", wxNotebook)->Show(false);
    
    SetDropTarget(new FileDropTarget(this));
}

void MainFrame::CreateControls() {
    wxXmlResource::Get()->LoadFrame(this, GetParent(), wxT("IDF_HACK4U"));
    SetIcon(wxIcon(icon16x16_xpm));
    
    wxMenuBar *mb = GetMenuBar();
    gameMenu = mb->FindMenu(wxT("Game"));
    locationMenu = mb->FindMenu(wxT("Location"));
    
    mb->EnableTop(gameMenu, false);
    mb->EnableTop(locationMenu, false);
    
    wxArrayString letters;
    letters.Add(wxT("A")); letters.Add(wxT("B")); letters.Add(wxT("C"));
    letters.Add(wxT("D")); letters.Add(wxT("E")); letters.Add(wxT("F"));
    letters.Add(wxT("G")); letters.Add(wxT("H")); letters.Add(wxT("I"));
    letters.Add(wxT("J")); letters.Add(wxT("K")); letters.Add(wxT("L"));
    letters.Add(wxT("M")); letters.Add(wxT("N")); letters.Add(wxT("O"));
    letters.Add(wxT("P")); letters.Add(wxT("Q")); letters.Add(wxT("R"));
    letters.Add(wxT("S")); letters.Add(wxT("T")); letters.Add(wxT("U"));
    letters.Add(wxT("V")); letters.Add(wxT("W")); letters.Add(wxT("X"));
    letters.Add(wxT("Y")); letters.Add(wxT("Z")); letters.Add(wxT("a"));
    letters.Add(wxT("b")); letters.Add(wxT("c")); letters.Add(wxT("d"));
    letters.Add(wxT("e")); letters.Add(wxT("f")); letters.Add(wxT("g"));
    letters.Add(wxT("h")); letters.Add(wxT("i")); letters.Add(wxT("j"));
    letters.Add(wxT("k")); letters.Add(wxT("l")); letters.Add(wxT("m"));
    letters.Add(wxT("n")); letters.Add(wxT("o")); letters.Add(wxT("p"));
    letters.Add(wxT("q")); letters.Add(wxT("r")); letters.Add(wxT("s"));
    letters.Add(wxT("t")); letters.Add(wxT("u")); letters.Add(wxT("v"));
    letters.Add(wxT("w")); letters.Add(wxT("x")); letters.Add(wxT("y"));
    letters.Add(wxT("z")); letters.Add(wxT("!")); letters.Add(wxT("-"));
    letters.Add(wxT("_"));
    
    wxTextValidator herosNameValidator(wxFILTER_INCLUDE_CHAR_LIST);
    herosNameValidator.SetIncludes(letters);
    
    XRCCTRL(*this, "IDT_HERO_NAME", wxTextCtrl)->
        SetValidator(herosNameValidator);
    
    wxTextValidator numberValidator(wxFILTER_NUMERIC);
    
    XRCCTRL(*this, "IDT_PARTY_GOLD", wxTextCtrl)->SetValidator(numberValidator);
    XRCCTRL(*this, "IDT_CHARACTER_HP", wxTextCtrl)->
        SetValidator(numberValidator);
    XRCCTRL(*this, "IDT_CHARACTER_MP", wxTextCtrl)->
        SetValidator(numberValidator);
    XRCCTRL(*this, "IDT_CHARACTER_EXPERIENCE", wxTextCtrl)->
        SetValidator(numberValidator);
    XRCCTRL(*this, "IDT_CHARACTER_MAXHP", wxTextCtrl)->
        SetValidator(numberValidator);
    XRCCTRL(*this, "IDT_CHARACTER_MAXMP", wxTextCtrl)->
        SetValidator(numberValidator);
    XRCCTRL(*this, "IDT_CHARACTER_STRENGTH", wxTextCtrl)->
        SetValidator(numberValidator);
    XRCCTRL(*this, "IDT_CHARACTER_INTELLIGENCE", wxTextCtrl)->
        SetValidator(numberValidator);
    XRCCTRL(*this, "IDT_CHARACTER_DEXTERITY", wxTextCtrl)->
        SetValidator(numberValidator);
    
    wxArrayString numbers;
    numbers.Add(wxT("2")); numbers.Add(wxT("3")); numbers.Add(wxT("4"));
    numbers.Add(wxT("5")); numbers.Add(wxT("6")); numbers.Add(wxT("7"));
    numbers.Add(wxT("8"));
    
    wxTextValidator levelValidator(wxFILTER_INCLUDE_CHAR_LIST);
    levelValidator.SetIncludes(numbers);
    
    XRCCTRL(*this, "IDT_CHARACTER_LEVEL", wxTextCtrl)->
        SetValidator(levelValidator);
        
    memberChoice[0] = XRCCTRL(*this, "IDC_PARTY_MEMBER1", wxChoice);
    memberChoice[1] = XRCCTRL(*this, "IDC_PARTY_MEMBER2", wxChoice);
    memberChoice[2] = XRCCTRL(*this, "IDC_PARTY_MEMBER3", wxChoice);
    memberChoice[3] = XRCCTRL(*this, "IDC_PARTY_MEMBER4", wxChoice);
    
    itemChoice[0] = XRCCTRL(*this, "IDC_CHARACTER_EQUIPMENT1", wxChoice);
    itemEquippedCheck[0] =
        XRCCTRL(*this, "IDC_CHARACTER_EQUIPPED1", wxCheckBox);
    
    itemChoice[1] = XRCCTRL(*this, "IDC_CHARACTER_EQUIPMENT2", wxChoice);
    itemEquippedCheck[1] =
        XRCCTRL(*this, "IDC_CHARACTER_EQUIPPED2", wxCheckBox);
    
    itemChoice[2] = XRCCTRL(*this, "IDC_CHARACTER_EQUIPMENT3", wxChoice);
    itemEquippedCheck[2] =
        XRCCTRL(*this, "IDC_CHARACTER_EQUIPPED3", wxCheckBox);
    
    itemChoice[3] = XRCCTRL(*this, "IDC_CHARACTER_EQUIPMENT4", wxChoice);
    itemEquippedCheck[3] =
        XRCCTRL(*this, "IDC_CHARACTER_EQUIPPED4", wxCheckBox);
    
    itemChoice[4] = XRCCTRL(*this, "IDC_CHARACTER_EQUIPMENT5", wxChoice);
    itemEquippedCheck[4] =
        XRCCTRL(*this, "IDC_CHARACTER_EQUIPPED5", wxCheckBox);
    
    itemChoice[5] = XRCCTRL(*this, "IDC_CHARACTER_EQUIPMENT6", wxChoice);
    itemEquippedCheck[5] =
        XRCCTRL(*this, "IDC_CHARACTER_EQUIPPED6", wxCheckBox);
}

void MainFrame::setEquipment(int slot) {
    enum Character character = static_cast<enum Character>
        (XRCCTRL(*this, "IDRB_CHARACTER_SELECT", wxRadioBox)->GetSelection());
    int item = itemChoice[slot]->GetSelection();
    
    if (itemEquippedCheck[slot]->IsChecked() && (item > 0)) {
        item |= 0x80;
    }
    
    saveslot->setEquipment(character, slot, item);
}

void MainFrame::setFeluccaOptions(enum City trammel) {
    wxChoice *feluccaChoice =
        XRCCTRL(*this, "IDC_TRANSPORTATION_FELUCCA", wxChoice);
    feluccaChoice->Clear();
    
    switch (trammel) {
        case MOONGLOW:
            feluccaChoice->Append(CITY_NAMES[MOONGLOW]);
            feluccaChoice->Append(CITY_NAMES[BRITAIN]);
            feluccaChoice->Append(CITY_NAMES[JHELOM]);
            break;
        case BRITAIN:
            feluccaChoice->Append(CITY_NAMES[YEW]);
            feluccaChoice->Append(CITY_NAMES[MINOC]);
            feluccaChoice->Append(CITY_NAMES[TRINSIC]);
            break;
        case JHELOM:
            feluccaChoice->Append(CITY_NAMES[SKARABRAE]);
            feluccaChoice->Append(CITY_NAMES[MAGINCIA]);
            feluccaChoice->Append(CITY_NAMES[MOONGLOW]);
            break;
        case YEW:
            feluccaChoice->Append(CITY_NAMES[BRITAIN]);
            feluccaChoice->Append(CITY_NAMES[JHELOM]);
            feluccaChoice->Append(CITY_NAMES[YEW]);
            break;
        case MINOC:
            feluccaChoice->Append(CITY_NAMES[MINOC]);
            feluccaChoice->Append(CITY_NAMES[TRINSIC]);
            feluccaChoice->Append(CITY_NAMES[SKARABRAE]);
            break;
        case TRINSIC:
            feluccaChoice->Append(CITY_NAMES[MAGINCIA]);
            feluccaChoice->Append(CITY_NAMES[MOONGLOW]);
            feluccaChoice->Append(CITY_NAMES[BRITAIN]);
            break;
        case SKARABRAE:
            feluccaChoice->Append(CITY_NAMES[JHELOM]);
            feluccaChoice->Append(CITY_NAMES[YEW]);
            feluccaChoice->Append(CITY_NAMES[MINOC]);
            break;
        case MAGINCIA:
            feluccaChoice->Append(CITY_NAMES[TRINSIC]);
            feluccaChoice->Append(CITY_NAMES[SKARABRAE]);
            feluccaChoice->Append(CITY_NAMES[MAGINCIA]);
            break;
    }
    
    feluccaChoice->SetSelection(0);
}

bool MainFrame::hasValidEquipment(enum Character character) const {
    bool bow = false;
    bool weapon = false;
    bool armor = false;
    
    for (int i = 0; i < 6; ++i) {
        int item = saveslot->getEquipment(character, i);
        
        if (item & 0x80) {
            item &= 0x7F;
            
            if ((item > 0x1) && (item <= 0x4)) {
                if (bow) {
                    return false;
                }
                
                bow = true;
            } else if ((item > 0x4) && (item <= 0xF)) {
                if (weapon) {
                    return false;
                }
                
                weapon = true;
            } else if ((item > 0xF) && (item <= 0x19)) {
                if (armor) {
                    return false;
                }
                
                armor = true;
            }
        }
    }
    
    return true;
}

bool MainFrame::isValidParty() const {
    char members = 0;
    bool end = false;
    
    for (int i = 0; i < 4; ++i) {
        int member = memberChoice[i]->GetSelection();
        
        if (i > 0) {
            member--;
        }

        if (member == -1) {
            end = true;
        } else {
            if (members & (1 << member)) {
                return false;
            }
        
            if (end) {
                return false;
            }

            members |= (1 << member);
        }
    }
    
    return true;
}

bool MainFrame::close() {
    // we must be open to close
    wxASSERT(isOpen());
    
    if (sram->isModified()) {
        int choice = wxMessageBox(wxT("Save Game File Before Closing?"),
                                  wxT("Warning: Unsaved Changes"),
                                  wxYES_NO | wxCANCEL | wxICON_QUESTION,
                                  this);
        
        if (choice == wxYES) {
            if (!save(sramFile)) {
                return false;
            }
        } else if (choice == wxCANCEL) {
            return false;
        }
    }
    
    XRCCTRL(*this, "IDN_HACK4U", wxNotebook)->Show(false);
    GetMenuBar()->FindItem(XRCID("IDM_GAME_GAME1"))->Check();
    
    open = false;
    
    delete sram;
    sram = 0;
    
    GetMenuBar()->EnableTop(gameMenu, false);
    GetMenuBar()->EnableTop(locationMenu, false);
    
    return true;
}

void MainFrame::load(const wxString &filename) {
    if (isOpen()) {
        if (!close()) {
            return;
        }
    }
    
    try {
        sram = new SRAMFile(filename);
    } catch (InvalidSRAMException &e) {
        if (e.getError() == ISE_NOSUCHFILE) {
            // unable to open file
            wxMessageBox(wxT("Unable to open the SRAM file."),
                         wxT("File Open Error"), wxOK | wxICON_ERROR);
        } else if (e.getError() == ISE_IOERROR) {
            wxMessageBox(wxT("Unable to read the SRAM file."),
                         wxT("File I/O Error"), wxOK | wxICON_ERROR);
        } else {
            // must be a bad checksum if we're here
            wxASSERT(e.getError() == ISE_BADCHECKSUM);
            
            wxMessageBox(wxT("No Ultima: Quest of the Avatar games"
                             " exist in the SRAM file you loaded."),
                         wxT("Error: No Games Found"), wxOK | wxICON_ERROR);
        }
        
        return;
    }
    
    for (int i = 0; i < 3; ++i) {
        if (sram->isValid(i)) {
            loadGame(i);
            break;
        }
    }
    
    open = true;
    
    GetMenuBar()->EnableTop(gameMenu, true);
    GetMenuBar()->EnableTop(locationMenu, true);
}

void MainFrame::loadGame(int game) {
    saveslot = sram->getSaveSlot(game);
    
    ignoreEvents = true;
    
    // load hero's name
    XRCCTRL(*this, "IDT_HERO_NAME", wxTextCtrl)->
        SetValue(saveslot->getHerosName());
        
    // load virtues
    XRCCTRL(*this, "IDS_HERO_HONESTY", wxSlider)->
        SetValue(saveslot->getVirtue(HONESTY));
    XRCCTRL(*this, "IDS_HERO_COMPASSION", wxSlider)->
        SetValue(saveslot->getVirtue(COMPASSION));
    XRCCTRL(*this, "IDS_HERO_VALOR", wxSlider)->
        SetValue(saveslot->getVirtue(VALOR));
    XRCCTRL(*this, "IDS_HERO_JUSTICE", wxSlider)->
        SetValue(saveslot->getVirtue(JUSTICE));
    XRCCTRL(*this, "IDS_HERO_SACRIFICE", wxSlider)->
        SetValue(saveslot->getVirtue(SACRIFICE));
    XRCCTRL(*this, "IDS_HERO_HONOR", wxSlider)->
        SetValue(saveslot->getVirtue(HONOR));
    XRCCTRL(*this, "IDS_HERO_SPIRITUALITY", wxSlider)->
        SetValue(saveslot->getVirtue(SPIRITUALITY));
    XRCCTRL(*this, "IDS_HERO_HUMILITY", wxSlider)->
        SetValue(saveslot->getVirtue(HUMILITY));
        
    // load party's start location
    XRCCTRL(*this, "IDC_PARTY_START", wxChoice)->
        SetSelection(INN_INDEX[saveslot->getStartLocation()]);
        
    // load party's gold
    XRCCTRL(*this, "IDT_PARTY_GOLD", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), saveslot->getGold()));
        
    // load party members
    XRCCTRL(*this, "IDC_PARTY_MEMBER1", wxChoice)->
        SetSelection(saveslot->getMember(0) - 1);
    XRCCTRL(*this, "IDC_PARTY_MEMBER2", wxChoice)->
        SetSelection(saveslot->getMember(1));
    XRCCTRL(*this, "IDC_PARTY_MEMBER3", wxChoice)->
        SetSelection(saveslot->getMember(2));
    XRCCTRL(*this, "IDC_PARTY_MEMBER4", wxChoice)->
        SetSelection(saveslot->getMember(3));
        
    // load joined members
    XRCCTRL(*this, "IDC_PARTY_MAGE", wxCheckBox)->
        SetValue(saveslot->hasJoined(MAGE));
    XRCCTRL(*this, "IDC_PARTY_BARD", wxCheckBox)->
        SetValue(saveslot->hasJoined(BARD));
    XRCCTRL(*this, "IDC_PARTY_FIGHTER", wxCheckBox)->
        SetValue(saveslot->hasJoined(FIGHTER));
    XRCCTRL(*this, "IDC_PARTY_DRUID", wxCheckBox)->
        SetValue(saveslot->hasJoined(DRUID));
    XRCCTRL(*this, "IDC_PARTY_TINKER", wxCheckBox)->
        SetValue(saveslot->hasJoined(TINKER));
    XRCCTRL(*this, "IDC_PARTY_PALADIN", wxCheckBox)->
        SetValue(saveslot->hasJoined(PALADIN));
    XRCCTRL(*this, "IDC_PARTY_RANGER", wxCheckBox)->
        SetValue(saveslot->hasJoined(RANGER));
    XRCCTRL(*this, "IDC_PARTY_SHEPHERD", wxCheckBox)->
        SetValue(saveslot->hasJoined(SHEPHERD));
        
    // load known magic
    XRCCTRL(*this, "IDC_PARTY_LIGHT", wxCheckBox)->
        SetValue(saveslot->hasMagic(LIGHT));
    XRCCTRL(*this, "IDC_PARTY_MISSILE", wxCheckBox)->
        SetValue(saveslot->hasMagic(MISSILE));
    XRCCTRL(*this, "IDC_PARTY_AWAKEN", wxCheckBox)->
        SetValue(saveslot->hasMagic(AWAKEN));
    XRCCTRL(*this, "IDC_PARTY_CURE", wxCheckBox)->
        SetValue(saveslot->hasMagic(CURE));
    XRCCTRL(*this, "IDC_PARTY_WIND", wxCheckBox)->
        SetValue(saveslot->hasMagic(WIND));
    XRCCTRL(*this, "IDC_PARTY_HEAL", wxCheckBox)->
        SetValue(saveslot->hasMagic(HEAL));
    XRCCTRL(*this, "IDC_PARTY_FIRE", wxCheckBox)->
        SetValue(saveslot->hasMagic(FIRE));
    XRCCTRL(*this, "IDC_PARTY_EXIT", wxCheckBox)->
        SetValue(saveslot->hasMagic(EXIT));
    XRCCTRL(*this, "IDC_PARTY_DISPEL", wxCheckBox)->
        SetValue(saveslot->hasMagic(DISPEL));
    XRCCTRL(*this, "IDC_PARTY_VIEW", wxCheckBox)->
        SetValue(saveslot->hasMagic(VIEW));
    XRCCTRL(*this, "IDC_PARTY_PROTECT", wxCheckBox)->
        SetValue(saveslot->hasMagic(PROTECT));
    XRCCTRL(*this, "IDC_PARTY_ICE", wxCheckBox)->
        SetValue(saveslot->hasMagic(ICE));
    XRCCTRL(*this, "IDC_PARTY_BLINK", wxCheckBox)->
        SetValue(saveslot->hasMagic(BLINK));
    XRCCTRL(*this, "IDC_PARTY_ENERGY", wxCheckBox)->
        SetValue(saveslot->hasMagic(ENERGY));
    XRCCTRL(*this, "IDC_PARTY_QUICK", wxCheckBox)->
        SetValue(saveslot->hasMagic(QUICK));
    XRCCTRL(*this, "IDC_PARTY_SLEEP", wxCheckBox)->
        SetValue(saveslot->hasMagic(SLEEP));
    XRCCTRL(*this, "IDC_PARTY_REFLECT", wxCheckBox)->
        SetValue(saveslot->hasMagic(REFLECT));
    XRCCTRL(*this, "IDC_PARTY_NEGATE", wxCheckBox)->
        SetValue(saveslot->hasMagic(NEGATE));
    XRCCTRL(*this, "IDC_PARTY_DESTROY", wxCheckBox)->
        SetValue(saveslot->hasMagic(DESTROY));
    XRCCTRL(*this, "IDC_PARTY_JINX", wxCheckBox)->
        SetValue(saveslot->hasMagic(JINX));
    XRCCTRL(*this, "IDC_PARTY_SQUISH", wxCheckBox)->
        SetValue(saveslot->hasMagic(SQUISH));
    XRCCTRL(*this, "IDC_PARTY_GATE", wxCheckBox)->
        SetValue(saveslot->hasMagic(GATE));
    XRCCTRL(*this, "IDC_PARTY_TREMOR", wxCheckBox)->
        SetValue(saveslot->hasMagic(TREMOR));
    XRCCTRL(*this, "IDC_PARTY_LIFE", wxCheckBox)->
        SetValue(saveslot->hasMagic(LIFE));
    XRCCTRL(*this, "IDC_PARTY_DEFEAT", wxCheckBox)->
        SetValue(saveslot->hasMagic(DEFEAT));
        
    // load herb inventory
    XRCCTRL(*this, "IDS_INVENTORY_ASH", wxSlider)->
        SetValue(saveslot->getHerb(ASH));
    XRCCTRL(*this, "IDS_INVENTORY_GINSENG", wxSlider)->
        SetValue(saveslot->getHerb(GINSENG));
    XRCCTRL(*this, "IDS_INVENTORY_GARLIC", wxSlider)->
        SetValue(saveslot->getHerb(GARLIC));
    XRCCTRL(*this, "IDS_INVENTORY_SILKWEB", wxSlider)->
        SetValue(saveslot->getHerb(SILKWEB));
    XRCCTRL(*this, "IDS_INVENTORY_MOSS", wxSlider)->
        SetValue(saveslot->getHerb(MOSS));
    XRCCTRL(*this, "IDS_INVENTORY_PEARL", wxSlider)->
        SetValue(saveslot->getHerb(PEARL));
    XRCCTRL(*this, "IDS_INVENTORY_FUNGUS", wxSlider)->
        SetValue(saveslot->getHerb(FUNGUS));
    XRCCTRL(*this, "IDS_INVENTORY_MANROOT", wxSlider)->
        SetValue(saveslot->getHerb(MANROOT));
        
    // load rune inventory
    XRCCTRL(*this, "IDC_INVENTORY_HONESTY", wxCheckBox)->
        SetValue(saveslot->hasRune(HONESTY));
    XRCCTRL(*this, "IDC_INVENTORY_COMPASSION", wxCheckBox)->
        SetValue(saveslot->hasRune(COMPASSION));
    XRCCTRL(*this, "IDC_INVENTORY_VALOR", wxCheckBox)->
        SetValue(saveslot->hasRune(VALOR));
    XRCCTRL(*this, "IDC_INVENTORY_JUSTICE", wxCheckBox)->
        SetValue(saveslot->hasRune(JUSTICE));
    XRCCTRL(*this, "IDC_INVENTORY_SACRIFICE", wxCheckBox)->
        SetValue(saveslot->hasRune(SACRIFICE));
    XRCCTRL(*this, "IDC_INVENTORY_HONOR", wxCheckBox)->
        SetValue(saveslot->hasRune(HONOR));
    XRCCTRL(*this, "IDC_INVENTORY_SPIRITUALITY", wxCheckBox)->
        SetValue(saveslot->hasRune(SPIRITUALITY));
    XRCCTRL(*this, "IDC_INVENTORY_HUMILITY", wxCheckBox)->
        SetValue(saveslot->hasRune(HUMILITY));
        
    // load stone inventory
    XRCCTRL(*this, "IDC_INVENTORY_BLUE", wxCheckBox)->
        SetValue(saveslot->hasStone(HONESTY));
    XRCCTRL(*this, "IDC_INVENTORY_YELLOW", wxCheckBox)->
        SetValue(saveslot->hasStone(COMPASSION));
    XRCCTRL(*this, "IDC_INVENTORY_RED", wxCheckBox)->
        SetValue(saveslot->hasStone(VALOR));
    XRCCTRL(*this, "IDC_INVENTORY_GREEN", wxCheckBox)->
        SetValue(saveslot->hasStone(JUSTICE));
    XRCCTRL(*this, "IDC_INVENTORY_ORANGE", wxCheckBox)->
        SetValue(saveslot->hasStone(SACRIFICE));
    XRCCTRL(*this, "IDC_INVENTORY_PURPLE", wxCheckBox)->
        SetValue(saveslot->hasStone(HONOR));
    XRCCTRL(*this, "IDC_INVENTORY_WHITE", wxCheckBox)->
        SetValue(saveslot->hasStone(SPIRITUALITY));
    XRCCTRL(*this, "IDC_INVENTORY_BLACK", wxCheckBox)->
        SetValue(saveslot->hasStone(HUMILITY));
        
    // load tool inventory
    XRCCTRL(*this, "IDS_INVENTORY_TORCH", wxSlider)->
        SetValue(saveslot->getTool(TORCH));
    XRCCTRL(*this, "IDS_INVENTORY_GEM", wxSlider)->
        SetValue(saveslot->getTool(GEM));
    XRCCTRL(*this, "IDS_INVENTORY_OIL", wxSlider)->
        SetValue(saveslot->getTool(OIL));
        
    XRCCTRL(*this, "IDC_INVENTORY_KEY", wxCheckBox)->
        SetValue(saveslot->getTool(KEY));
    XRCCTRL(*this, "IDC_INVENTORY_SEXTANT", wxCheckBox)->
        SetValue(saveslot->getTool(SEXTANT));
    XRCCTRL(*this, "IDC_INVENTORY_SCALE", wxCheckBox)->
        SetValue(saveslot->getTool(SCALE));
    XRCCTRL(*this, "IDC_INVENTORY_FLUTE", wxCheckBox)->
        SetValue(saveslot->getTool(FLUTE));
    XRCCTRL(*this, "IDC_INVENTORY_CANDLE", wxCheckBox)->
        SetValue(saveslot->getTool(CANDLE));
    XRCCTRL(*this, "IDC_INVENTORY_BOOK", wxCheckBox)->
        SetValue(saveslot->getTool(BOOK));
    XRCCTRL(*this, "IDC_INVENTORY_BELL", wxCheckBox)->
        SetValue(saveslot->getTool(BELL));
    XRCCTRL(*this, "IDC_INVENTORY_HORN", wxCheckBox)->
        SetValue(saveslot->getTool(HORN));
    XRCCTRL(*this, "IDC_INVENTORY_SKULL", wxCheckBox)->
        SetValue(saveslot->getTool(SKULL));
    XRCCTRL(*this, "IDC_INVENTORY_TRUTHKEY", wxCheckBox)->
        SetValue(saveslot->getTool(TRUTHKEY));
    XRCCTRL(*this, "IDC_INVENTORY_LOVEKEY", wxCheckBox)->
        SetValue(saveslot->getTool(LOVEKEY));
    XRCCTRL(*this, "IDC_INVENTORY_COURAGEKEY", wxCheckBox)->
        SetValue(saveslot->getTool(COURAGEKEY));
    XRCCTRL(*this, "IDC_INVENTORY_WHEEL", wxCheckBox)->
        SetValue(saveslot->getTool(WHEEL));
        
    // load moongates
    XRCCTRL(*this, "IDC_TRANSPORTATION_TRAMMEL", wxChoice)->
        SetSelection(saveslot->getPhase(TRAMMEL));
    setFeluccaOptions(static_cast<enum City>(saveslot->getPhase(TRAMMEL)));
    XRCCTRL(*this, "IDC_TRANSPORTATION_FELUCCA", wxChoice)->
        SetSelection(saveslot->getPhase(FELUCCA));
        
    // load Balloon location
    std::pair<int, int> balloon = saveslot->getBalloonLocation();
    XRCCTRL(*this, "IDT_TRANSPORTATION_BALLOONLATITUDE", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), balloon.first));
    XRCCTRL(*this, "IDT_TRANSPORTATION_BALLOONLONGITUDE", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), balloon.second));
        
    // load Whirlpool location
    std::pair<int, int> whirlpool = saveslot->getWhirlpoolLocation();
    XRCCTRL(*this, "IDT_TRANSPORTATION_WHIRLPOOLLATITUDE", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), whirlpool.first));
    XRCCTRL(*this, "IDT_TRANSPORTATION_WHIRLPOOLLONGITUDE", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), whirlpool.second));
        
    // load pirate ship locations
    XRCCTRL(*this, "IDC_TRANSPORTATION_SHIP1", wxCheckBox)->
        SetValue(saveslot->hasPirateShip(SHIP1));
    XRCCTRL(*this, "IDC_TRANSPORTATION_SHIP2", wxCheckBox)->
        SetValue(saveslot->hasPirateShip(SHIP2));
    XRCCTRL(*this, "IDC_TRANSPORTATION_SHIP3", wxCheckBox)->
        SetValue(saveslot->hasPirateShip(SHIP3));
    XRCCTRL(*this, "IDC_TRANSPORTATION_SHIP4", wxCheckBox)->
        SetValue(saveslot->hasPirateShip(SHIP4));
        
    std::pair<int, int> ship = saveslot->getPirateShipLocation(SHIP1);
    XRCCTRL(*this, "IDT_TRANSPORTATION_SHIP1LATITUDE", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), ship.first));
    XRCCTRL(*this, "IDT_TRANSPORTATION_SHIP1LONGITUDE", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), ship.second));
        
    ship = saveslot->getPirateShipLocation(SHIP2);
    XRCCTRL(*this, "IDT_TRANSPORTATION_SHIP2LATITUDE", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), ship.first));
    XRCCTRL(*this, "IDT_TRANSPORTATION_SHIP2LONGITUDE", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), ship.second));
        
    ship = saveslot->getPirateShipLocation(SHIP3);
    XRCCTRL(*this, "IDT_TRANSPORTATION_SHIP3LATITUDE", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), ship.first));
    XRCCTRL(*this, "IDT_TRANSPORTATION_SHIP3LONGITUDE", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), ship.second));
        
    ship = saveslot->getPirateShipLocation(SHIP4);
    XRCCTRL(*this, "IDT_TRANSPORTATION_SHIP4LATITUDE", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), ship.first));
    XRCCTRL(*this, "IDT_TRANSPORTATION_SHIP4LONGITUDE", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), ship.second));
        
    // load character stats
    loadStats(static_cast<enum Character>(
        XRCCTRL(*this, "IDRB_CHARACTER_SELECT", wxRadioBox)->GetSelection()));
                      
    // show the notebook
    wxNotebook *notebook = XRCCTRL(*this, "IDN_HACK4U", wxNotebook);
    notebook->SetSelection(0);
    notebook->Show(true);
    
    ignoreEvents = false;
}

void MainFrame::loadStats(enum Character character) {
    // ignore events we're about to generate
    ignoreEvents = true;
    
    XRCCTRL(*this, "IDT_CHARACTER_LEVEL", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), saveslot->getLevel(character)));
    XRCCTRL(*this, "IDT_CHARACTER_HP", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"),
                 saveslot->getCurrentHP(character)));
    XRCCTRL(*this, "IDT_CHARACTER_MP", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"),
                 saveslot->getCurrentMP(character)));
    XRCCTRL(*this, "IDT_CHARACTER_EXPERIENCE", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"),
                 saveslot->getExperience(character)));
    XRCCTRL(*this, "IDT_CHARACTER_MAXHP", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), saveslot->getMaxHP(character)));
    XRCCTRL(*this, "IDT_CHARACTER_MAXMP", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), saveslot->getMaxMP(character)));
    XRCCTRL(*this, "IDT_CHARACTER_STRENGTH", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), saveslot->getStrength(character)));
    XRCCTRL(*this, "IDT_CHARACTER_INTELLIGENCE", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"),
                 saveslot->getIntelligence(character)));
    XRCCTRL(*this, "IDT_CHARACTER_DEXTERITY", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"),
                 saveslot->getDexterity(character)));
                 
    for (int index = 0; index < 6; ++index) {
        int item = saveslot->getEquipment(character, index);
        
        itemChoice[index]->SetSelection(item & 0x7F);
        itemEquippedCheck[index]->SetValue(item & 0x80);
    }
    
    ignoreEvents = false;
}

bool MainFrame::save(const wxString &filename) {
    if (!isValidParty()) {
        int choice = wxMessageBox(wxT("Duplicate or missing party members"
                                      " selected.\nContinue Saving?"),
                                  wxT("Warning: Invalid Party"),
                                  wxYES_NO | wxICON_QUESTION,
                                  this);
                                 
        if (choice != wxYES) {
            return false;
        }
    }
    
    for (int character = MAGE; character < SHEPHERD; ++character) {
        if (!hasValidEquipment(static_cast<enum Character>(character))) {
            int choice = wxMessageBox(CHARACTER_NAMES[character] + 
                                      wxT(" has more than one equipped item of "
                                          "the same type.\nContinue Saving?"),
                                      wxT("Warning: Invalid Equipment"),
                                      wxYES_NO | wxICON_QUESTION,
                                      this);
                                      
            if (choice != wxYES) {
                return false;
            }
        }
    }
    
    try {
        sram->save(filename);
    } catch (FileIOException &e) {
        if (e.getError() == FIE_CANNOTOPEN) {
            wxMessageBox(wxT("Unable to open the SRAM file."),
                         wxT("File Open Error"), wxOK | wxICON_ERROR);
                         
            return false;
        } else {
            // we must be an FIE_IOERROR
            wxASSERT(e.getError() == FIE_IOERROR);
            
            wxMessageBox(wxT("Unable to write to the SRAM file."),
                         wxT("File I/O error"), wxOK | wxICON_ERROR);
            
            return false;
        }
    }
    
    return true;
}

void MainFrame::onBalloonChange(wxCommandEvent &event) {
    if (ignoreEvents) {
        return;
    }
    
    wxTextCtrl *ctrl = dynamic_cast<wxTextCtrl *>(event.GetEventObject());
    int value = std::atoi(ctrl->GetValue());
    std::pair<int, int> location = saveslot->getBalloonLocation();
    
    if (event.GetId() == XRCID("IDT_TRANSPORTATION_BALLOONLATITUDE")) {
        location.first = value;
    } else {
        // we must be longitude if we're here
        wxASSERT(event.GetId() == XRCID("IDT_TRANSPORTATION_BALLOONLONGITUDE"));
        
        location.second = value;
    }
    
    saveslot->setBalloonLocation(location);
}

void MainFrame::onEquipmentChange(wxCommandEvent &event) {
    wxChoice *ctrl = dynamic_cast<wxChoice *>(event.GetEventObject());
    int slot;
    
    for (slot = 0; slot < 6; ++slot) {
        if (ctrl == itemChoice[slot]) {
            break;
        }
    }
    
    setEquipment(slot);
}

void MainFrame::onEquippedChange(wxCommandEvent &event) {
    wxCheckBox *ctrl = dynamic_cast<wxCheckBox *>(event.GetEventObject());
    int slot;
    
    for (slot = 0; slot < 6; ++slot) {
        if (ctrl == itemEquippedCheck[slot]) {
            break;
        }
    }
    
    setEquipment(slot);
}

void MainFrame::onEquippedUpdate(wxUpdateUIEvent &event) {
    if (event.GetId() == XRCID("IDC_CHARACTER_EQUIPPED1")) {
        event.Enable(itemChoice[0]->GetSelection() > 0);
        
        if (itemChoice[0]->GetSelection() == 0) {
            event.Check(false);
        }
    } else if (event.GetId() == XRCID("IDC_CHARACTER_EQUIPPED2")) {
        event.Enable(itemChoice[1]->GetSelection() > 0);
        
        if (itemChoice[1]->GetSelection() == 0) {
            event.Check(false);
        }
    } else if (event.GetId() == XRCID("IDC_CHARACTER_EQUIPPED3")) {
        event.Enable(itemChoice[2]->GetSelection() > 0);
        
        if (itemChoice[2]->GetSelection() == 0) {
            event.Check(false);
        }
    } else if (event.GetId() == XRCID("IDC_CHARACTER_EQUIPPED4")) {
        event.Enable(itemChoice[3]->GetSelection() > 0);
        
        if (itemChoice[3]->GetSelection() == 0) {
            event.Check(false);
        }
    } else if (event.GetId() == XRCID("IDC_CHARACTER_EQUIPPED5")) {
        event.Enable(itemChoice[4]->GetSelection() > 0);
        
        if (itemChoice[4]->GetSelection() == 0) {
            event.Check(false);
        }
    } else {
        // we must be the last box if we're here
        wxASSERT(event.GetId() == XRCID("IDC_CHARACTER_EQUIPPED6"));
        
        event.Enable(itemChoice[5]->GetSelection() > 0);
        
        if (itemChoice[5]->GetSelection() == 0) {
            event.Check(false);
        }
    }
}

void MainFrame::onFileExit(wxCommandEvent &) {
    if (isOpen()) {
        if (close()) {
            Close(true);
        }
    } else {
        Close(true);
    }
}

void MainFrame::onFileOpen(wxCommandEvent &) {
    static wxFileDialog *dlg = new wxFileDialog(this, 
        wxT("Choose a .SAV File"), "", "", 
        wxT("NES SRAM File (*.sav)|*.sav"), (wxOPEN | wxCHANGE_DIR));
        
    int value = dlg->ShowModal();
    
    if (value == wxID_OK) {
        sramFile = dlg->GetPath();
        load(sramFile);
    }
}

void MainFrame::onFileSaveAs(wxCommandEvent &) {
    static wxFileDialog *dlg = new wxFileDialog(this, 
        wxT("Choose a .SAV File"), "", "", 
        wxT("NES SRAM File (*.sav)|*.sav"), (wxSAVE | wxCHANGE_DIR));
    
    int value = dlg->ShowModal();
    
    if (value == wxID_OK) {
        sramFile = dlg->GetPath();
        save(sramFile);
    }
}

void MainFrame::onGameChange(wxCommandEvent &event) {
    if (event.GetId() == XRCID("IDM_GAME_GAME1")) {
        loadGame(0);
    } else if (event.GetId() == XRCID("IDM_GAME_GAME2")) {
        loadGame(1);
    } else if (event.GetId() == XRCID("IDM_GAME_GAME3")) {
        loadGame(2);
    }
}

void MainFrame::onGameMenuUpdate(wxUpdateUIEvent &event) {
    if (isOpen()) {
        if (event.GetId() == XRCID("IDM_GAME_GAME1")) {
            event.Enable(sram->isValid(0));
        } else if (event.GetId() == XRCID("IDM_GAME_GAME2")) {
            event.Enable(sram->isValid(1));
        } else {
            // we must be game 3 if we're here
            wxASSERT(event.GetId() == XRCID("IDM_GAME_GAME3"));
            
            event.Enable(sram->isValid(2));
        }
    } else {
        event.Enable(false);
    }
}

void MainFrame::onGoldChange(wxCommandEvent &) {
    if (ignoreEvents) {
        return;
    }
    
    saveslot->setGold(std::atoi(XRCCTRL(*this, 
                                        "IDT_PARTY_GOLD",
                                        wxTextCtrl)->GetValue()));
}

void MainFrame::onHelpAbout(wxCommandEvent &) {
    wxMessageDialog dlg(this, *Hack4u::APP_NAME + wxT(' ') + 
                        *Hack4u::APP_VERSION + wxT('\n') +
                        *Hack4u::APP_COPYRIGHT + wxT('\n') +
                        *Hack4u::APP_URL, wxT("About ") + 
                        *Hack4u::APP_NAME + wxT("..."),
                        wxOK | wxICON_INFORMATION);
    dlg.ShowModal();
}

void MainFrame::onHerbChange(wxScrollEvent &event) {
    enum Herb herb = MANROOT;
    
    if (event.GetId() == XRCID("IDS_INVENTORY_ASH")) {
        herb = ASH;
    } else if (event.GetId() == XRCID("IDS_INVENTORY_GINSENG")) {
        herb = GINSENG;
    } else if (event.GetId() == XRCID("IDS_INVENTORY_GARLIC")) {
        herb = GARLIC;
    } else if (event.GetId() == XRCID("IDS_INVENTORY_SILKWEB")) {
        herb = SILKWEB;
    } else if (event.GetId() == XRCID("IDS_INVENTORY_MOSS")) {
        herb = MOSS;
    } else if (event.GetId() == XRCID("IDS_INVENTORY_PEARL")) {
        herb = PEARL;
    } else if (event.GetId() == XRCID("IDS_INVENTORY_FUNGUS")) {
        herb = FUNGUS;
    }
    
    saveslot->setHerb(herb, event.GetPosition());
}

void MainFrame::onHerosNameChange(wxCommandEvent &) {
    if (ignoreEvents) {
        return;
    }
    
    saveslot->setHerosName(XRCCTRL(*this,
                                   "IDT_HERO_NAME",
                                   wxTextCtrl)->GetValue());
}

void MainFrame::onJoinedChange(wxCommandEvent &event) {
    if (event.GetId() == XRCID("IDC_PARTY_MAGE")) {
        saveslot->setJoined(MAGE, event.IsChecked());
    } else if (event.GetId() == XRCID("IDC_PARTY_BARD")) {
        saveslot->setJoined(BARD, event.IsChecked());
    } else if (event.GetId() == XRCID("IDC_PARTY_FIGHTER")) {
        saveslot->setJoined(FIGHTER, event.IsChecked());
    } else if (event.GetId() == XRCID("IDC_PARTY_DRUID")) {
        saveslot->setJoined(DRUID, event.IsChecked());
    } else if (event.GetId() == XRCID("IDC_PARTY_TINKER")) {
        saveslot->setJoined(TINKER, event.IsChecked());
    } else if (event.GetId() == XRCID("IDC_PARTY_PALADIN")) {
        saveslot->setJoined(PALADIN, event.IsChecked());
    } else if (event.GetId() == XRCID("IDC_PARTY_RANGER")) {
        saveslot->setJoined(RANGER, event.IsChecked());
    } else {
        // we must be shepherd if we're here
        wxASSERT(event.GetId() == XRCID("IDC_PARTY_SHEPHERD"));
        
        saveslot->setJoined(SHEPHERD, event.IsChecked());
    }
}

void MainFrame::onLocationBalloon(wxCommandEvent &) {
    const std::pair<int, int> &balloon = BALLOON_LOCATIONS[location];
    
    XRCCTRL(*this, "IDT_TRANSPORTATION_BALLOONLATITUDE", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), balloon.first));
    XRCCTRL(*this, "IDT_TRANSPORTATION_BALLOONLONGITUDE", wxTextCtrl)->
        SetValue(wxString::Format(wxT("%d"), balloon.second));
}

void MainFrame::onLocationPlaceChange(wxCommandEvent &event) {
    if (event.GetId() == XRCID("IDM_LOCATION_PLACE_MOONGLOW")) {
        location = LMOONGLOW;
    } else if (event.GetId() == XRCID("IDM_LOCATION_PLACE_BRITAIN")) {
        location = LBRITAIN;
    } else if (event.GetId() == XRCID("IDM_LOCATION_PLACE_JHELOM")) {
        location = LJHELOM;
    } else if (event.GetId() == XRCID("IDM_LOCATION_PLACE_YEW")) {
        location = LYEW;
    } else if (event.GetId() == XRCID("IDM_LOCATION_PLACE_MINOC")) {
        location = LMINOC;
    } else if (event.GetId() == XRCID("IDM_LOCATION_PLACE_TRINSIC")) {
        location = LTRINSIC;
    } else if (event.GetId() == XRCID("IDM_LOCATION_PLACE_SKARABRAE")) {
        location = LSKARABRAE;
    } else if (event.GetId() == XRCID("IDM_LOCATION_PLACE_MAGINCIA")) {
        location = LMAGINCIA;
    } else if (event.GetId() == XRCID("IDM_LOCATION_PLACE_LYCAEUM")) {
        location = LLYCAEUM;
    } else if (event.GetId() == XRCID("IDM_LOCATION_PLACE_EMPATHABBEY")) {
        location = LEMPATHABBEY;
    } else if (event.GetId() == XRCID("IDM_LOCATION_PLACE_SERPENTSHOLD")) {
        location = LSERPENTSHOLD;
    } else if (event.GetId() == XRCID("IDM_LOCATION_PLACE_PAWS")) {
        location = LPAWS;
    } else if (event.GetId() == XRCID("IDM_LOCATION_PLACE_VESPER")) {
        location = LVESPER;
    } else if (event.GetId() == XRCID("IDM_LOCATION_PLACE_BUCCANEERSDEN")) {
        location = LBUCCANEERSDEN;
    } else {
        // we must be Cove if we're here
        wxASSERT(event.GetId() == XRCID("IDM_LOCATION_PLACE_COVE"));
        
        location = LCOVE;
    }
}

void MainFrame::onLocationShip(wxCommandEvent &event) {
    wxCheckBox *check;
    wxTextCtrl *latitude, *longitude;
    enum PirateShip ship;
    
    if (event.GetId() == XRCID("IDM_LOCATION_SHIP1")) {
        ship = SHIP1;
        check = XRCCTRL(*this, "IDC_TRANSPORTATION_SHIP1", wxCheckBox);
        latitude =
            XRCCTRL(*this, "IDT_TRANSPORTATION_SHIP1LATITUDE", wxTextCtrl);
        longitude =
            XRCCTRL(*this, "IDT_TRANSPORTATION_SHIP1LONGITUDE", wxTextCtrl);
    } else if (event.GetId() == XRCID("IDM_LOCATION_SHIP2")) {
        ship = SHIP2;
        check = XRCCTRL(*this, "IDC_TRANSPORTATION_SHIP2", wxCheckBox);
        latitude =
            XRCCTRL(*this, "IDT_TRANSPORTATION_SHIP2LATITUDE", wxTextCtrl);
        longitude =
            XRCCTRL(*this, "IDT_TRANSPORTATION_SHIP2LONGITUDE", wxTextCtrl);
    } else if (event.GetId() == XRCID("IDM_LOCATION_SHIP3")) {
        ship = SHIP3;
        check = XRCCTRL(*this, "IDC_TRANSPORTATION_SHIP3", wxCheckBox);
        latitude =
            XRCCTRL(*this, "IDT_TRANSPORTATION_SHIP3LATITUDE", wxTextCtrl);
        longitude =
            XRCCTRL(*this, "IDT_TRANSPORTATION_SHIP3LONGITUDE", wxTextCtrl);
    } else {
        // we must be ship 4 if we're here
        wxASSERT(event.GetId() == XRCID("IDM_LOCATION_SHIP4"));
        
        ship = SHIP4;
        check = XRCCTRL(*this, "IDC_TRANSPORTATION_SHIP4", wxCheckBox);
        latitude =
            XRCCTRL(*this, "IDT_TRANSPORTATION_SHIP4LATITUDE", wxTextCtrl);
        longitude =
            XRCCTRL(*this, "IDT_TRANSPORTATION_SHIP4LONGITUDE", wxTextCtrl);
    }
    
    const std::pair<int, int> &loc = PIRATESHIP_LOCATIONS[location];
    
    check->SetValue(true);
    latitude->SetValue(wxString::Format(wxT("%d"), loc.first));
    longitude->SetValue(wxString::Format(wxT("%d"), loc.second));
    
    saveslot->setPirateShip(ship, true);
}

void MainFrame::onMagicChange(wxCommandEvent &event) {
    enum Magic magic = DEFEAT;
    
    if (event.GetId() == XRCID("IDC_PARTY_LIGHT")) {
        magic = LIGHT;
    } else if (event.GetId() == XRCID("IDC_PARTY_MISSILE")) {
        magic = MISSILE;
    } else if (event.GetId() == XRCID("IDC_PARTY_AWAKEN")) {
        magic = AWAKEN;
    } else if (event.GetId() == XRCID("IDC_PARTY_CURE")) {
        magic = CURE;
    } else if (event.GetId() == XRCID("IDC_PARTY_WIND")) {
        magic = WIND;
    } else if (event.GetId() == XRCID("IDC_PARTY_HEAL")) {
        magic = HEAL;
    } else if (event.GetId() == XRCID("IDC_PARTY_FIRE")) {
        magic = FIRE;
    } else if (event.GetId() == XRCID("IDC_PARTY_EXIT")) {
        magic = EXIT;
    } else if (event.GetId() == XRCID("IDC_PARTY_DISPEL")) {
        magic = DISPEL;
    } else if (event.GetId() == XRCID("IDC_PARTY_VIEW")) {
        magic = VIEW;
    } else if (event.GetId() == XRCID("IDC_PARTY_PROTECT")) {
        magic = PROTECT;
    } else if (event.GetId() == XRCID("IDC_PARTY_ICE")) {
        magic = ICE;
    } else if (event.GetId() == XRCID("IDC_PARTY_BLINK")) {
        magic = BLINK;
    } else if (event.GetId() == XRCID("IDC_PARTY_ENERGY")) {
        magic = ENERGY;
    } else if (event.GetId() == XRCID("IDC_PARTY_QUICK")) {
        magic = QUICK;
    } else if (event.GetId() == XRCID("IDC_PARTY_SLEEP")) {
        magic = SLEEP;
    } else if (event.GetId() == XRCID("IDC_PARTY_REFLECT")) {
        magic = REFLECT;
    } else if (event.GetId() == XRCID("IDC_PARTY_NEGATE")) {
        magic = NEGATE;
    } else if (event.GetId() == XRCID("IDC_PARTY_DESTROY")) {
        magic = DESTROY;
    } else if (event.GetId() == XRCID("IDC_PARTY_JINX")) {
        magic = JINX;
    } else if (event.GetId() == XRCID("IDC_PARTY_SQUISH")) {
        magic = SQUISH;
    } else if (event.GetId() == XRCID("IDC_PARTY_GATE")) {
        magic = GATE;
    } else if (event.GetId() == XRCID("IDC_PARTY_TREMOR")) {
        magic = TREMOR;
    } else if (event.GetId() == XRCID("IDC_PARTY_LIFE")) {
        magic = LIFE;
    }
    
    saveslot->setMagic(magic, event.IsChecked());
}

void MainFrame::onMemberClassChange(wxCommandEvent &event) {
    int character = event.GetSelection();
    int member = 3;
    
    if (event.GetId() == XRCID("IDC_PARTY_MEMBER1")) {
        member = 0;
    } else if (event.GetId() == XRCID("IDC_PARTY_MEMBER2")) {
        member = 1;
        
        if (character == 0) {
            // remove subsequent members
            wxCommandEvent evt(wxEVT_COMMAND_CHOICE_SELECTED,
                               XRCID("IDC_PARTY_MEMBER3"));
            evt.SetEventObject(memberChoice[2]);
            evt.SetInt(0);
            AddPendingEvent(evt);
            
            memberChoice[2]->SetSelection(0);
        }
    } else if (event.GetId() == XRCID("IDC_PARTY_MEMBER3")) {
        member = 2;
        
        if (character == 0) {
            // remove subsequent members
            wxCommandEvent evt(wxEVT_COMMAND_CHOICE_SELECTED,
                               XRCID("IDC_PARTY_MEMBER4"));
            evt.SetEventObject(memberChoice[3]);
            evt.SetInt(0);
            AddPendingEvent(evt);
            
            memberChoice[3]->SetSelection(0);
        }
    }
    
    saveslot->setMember(member, ((member == 0) ? 
                                              (character + 1) : character));
}

void MainFrame::onMemberUpdate(wxUpdateUIEvent &event) {
    if (event.GetId() == XRCID("IDC_PARTY_MEMBER3")) {
        event.Enable(memberChoice[1]->GetSelection() > 0);
    } else {
        // we must be 4 if we're here
        wxASSERT(event.GetId() == XRCID("IDC_PARTY_MEMBER4"));
        
        event.Enable(memberChoice[2]->GetSelection() > 0);
    }
}

void MainFrame::onPhaseChange(wxCommandEvent &event) {
    enum City trammel;
    int felucca;
    
    if (event.GetId() == XRCID("IDC_TRANSPORTATION_TRAMMEL")) {
        trammel = static_cast<enum City>(event.GetSelection());
        setFeluccaOptions(trammel);
    } else {
        trammel = static_cast<enum City>
            (XRCCTRL(*this,
                     "IDC_TRANSPORTATION_TRAMMEL",
                     wxChoice)->GetSelection());
    }
    
    felucca =
        XRCCTRL(*this, "IDC_TRANSPORTATION_FELUCCA", wxChoice)->GetSelection();
    saveslot->setPhase(trammel, felucca);
}

void MainFrame::onRuneChange(wxCommandEvent &event) {
    enum Virtue rune = HUMILITY;
    
    if (event.GetId() == XRCID("IDC_INVENTORY_HONESTY")) {
        rune = HONESTY;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_COMPASSION")) {
        rune = COMPASSION;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_VALOR")) {
        rune = VALOR;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_JUSTICE")) {
        rune = JUSTICE;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_SACRIFICE")) {
        rune = SACRIFICE;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_HONOR")) {
        rune = HONOR;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_SPIRITUALITY")) {
        rune = SPIRITUALITY;
    }
    
    saveslot->setRune(rune, event.IsChecked());
}

void MainFrame::onSaveUpdate(wxUpdateUIEvent &event) {
    // no need to save unless we have an open modified game
    event.Enable(isOpen() &&
        (sram->getSaveSlot(0)->isModified() ||
         sram->getSaveSlot(1)->isModified() ||
         sram->getSaveSlot(2)->isModified()));
}

void MainFrame::onShipChange(wxCommandEvent &event) {
    enum PirateShip ship;
    
    if (event.GetId() == XRCID("IDC_TRANSPORTATION_SHIP1")) {
        ship = SHIP1;
    } else if (event.GetId() == XRCID("IDC_TRANSPORTATION_SHIP2")) {
        ship = SHIP2;
    } else if (event.GetId() == XRCID("IDC_TRANSPORTATION_SHIP3")) {
        ship = SHIP3;
    } else {
        // we must be the last ship if we're here
        wxASSERT(event.GetId() == XRCID("IDC_TRANSPORTATION_SHIP4"));
        
        ship = SHIP4;
    }
    
    saveslot->setPirateShip(ship, event.IsChecked());
}

void MainFrame::onShipLocationChange(wxCommandEvent &event) {
    if (ignoreEvents) {
        return;
    }
    
    wxTextCtrl *ctrl = dynamic_cast<wxTextCtrl *>(event.GetEventObject());
    int value = std::atoi(ctrl->GetValue());
    enum PirateShip ship;
    std::pair<int, int> location;
    
    if (event.GetId() == XRCID("IDT_TRANSPORTATION_SHIP1LATITUDE")) {
        ship = SHIP1;
        location = saveslot->getPirateShipLocation(ship);
        location.first = value;
    } else if (event.GetId() == XRCID("IDT_TRANSPORTATION_SHIP2LATITUDE")) {
        ship = SHIP2;
        location = saveslot->getPirateShipLocation(ship);
        location.first = value;
    } else if (event.GetId() == XRCID("IDT_TRANSPORTATION_SHIP3LATITUDE")) {
        ship = SHIP3;
        location = saveslot->getPirateShipLocation(ship);
        location.first = value;
    } else if (event.GetId() == XRCID("IDT_TRANSPORTATION_SHIP4LATITUDE")) {
        ship = SHIP4;
        location = saveslot->getPirateShipLocation(ship);
        location.first = value;
    } else if (event.GetId() == XRCID("IDT_TRANSPORTATION_SHIP1LONGITUDE")) {
        ship = SHIP1;
        location = saveslot->getPirateShipLocation(ship);
        location.second = value;
    } else if (event.GetId() == XRCID("IDT_TRANSPORTATION_SHIP2LONGITUDE")) {
        ship = SHIP2;
        location = saveslot->getPirateShipLocation(ship);
        location.second = value;
    } else if (event.GetId() == XRCID("IDT_TRANSPORTATION_SHIP3LONGITUDE")) {
        ship = SHIP3;
        location = saveslot->getPirateShipLocation(ship);
        location.second = value;
    } else {
        // we must be the fourth ship's longitude if we're here
        wxASSERT(event.GetId() == XRCID("IDT_TRANSPORTATION_SHIP4LONGITUDE"));
        
        ship = SHIP4;
        location = saveslot->getPirateShipLocation(ship);
        location.second = value;
    }
    
    saveslot->setPirateShipLocation(ship, location);
}

void MainFrame::onShipUpdate(wxUpdateUIEvent &event) {
    if ((event.GetId() == XRCID("IDT_TRANSPORTATION_SHIP1LATITUDE")) ||
       (event.GetId() == XRCID("IDT_TRANSPORTATION_SHIP1LONGITUDE"))) {
        event.Enable(XRCCTRL(*this,
                             "IDC_TRANSPORTATION_SHIP1",
                             wxCheckBox)->IsChecked());
    } else if ((event.GetId() == XRCID("IDT_TRANSPORTATION_SHIP2LATITUDE")) ||
               (event.GetId() == XRCID("IDT_TRANSPORTATION_SHIP2LONGITUDE"))) {
        event.Enable(XRCCTRL(*this,
                             "IDC_TRANSPORTATION_SHIP2",
                             wxCheckBox)->IsChecked());
    } else if ((event.GetId() == XRCID("IDT_TRANSPORTATION_SHIP3LATITUDE")) ||
               (event.GetId() == XRCID("IDT_TRANSPORTATION_SHIP3LONGITUDE"))) {
        event.Enable(XRCCTRL(*this,
                             "IDC_TRANSPORTATION_SHIP3",
                             wxCheckBox)->IsChecked());
    } else {
        // we must be the fourth ship
        wxASSERT((event.GetId() == XRCID("IDT_TRANSPORTATION_SHIP4LATITUDE")) ||
                 (event.GetId() == XRCID("IDT_TRANSPORTATION_SHIP4LONGITUDE")));
        
        event.Enable(XRCCTRL(*this,
                             "IDC_TRANSPORTATION_SHIP4",
                             wxCheckBox)->IsChecked());
    }
}

void MainFrame::onStartLocationChange(wxCommandEvent &event) {
    int city = event.GetSelection();
    
    for (int i = MOONGLOW_INN; i <= VESPER_INN; ++i) {
        if (city == INN_INDEX[i]) {
            saveslot->setStartLocation(static_cast<enum StartLocation>(i));
            break;
        }
    }
}

void MainFrame::onStatChange(wxCommandEvent &event) {
    if (ignoreEvents) {
        return;
    }
    
    wxTextCtrl *ctrl = dynamic_cast<wxTextCtrl *>(event.GetEventObject());
    enum Character character = static_cast<enum Character>
        (XRCCTRL(*this, "IDRB_CHARACTER_SELECT", wxRadioBox)->GetSelection());
    int value = std::atoi(ctrl->GetValue());

    if (event.GetId() == XRCID("IDT_CHARACTER_LEVEL")) {
        saveslot->setLevel(character, value);
    } else if (event.GetId() == XRCID("IDT_CHARACTER_HP")) {
        saveslot->setCurrentHP(character, value);
    } else if (event.GetId() == XRCID("IDT_CHARACTER_MP")) {
        saveslot->setCurrentMP(character, value);
    } else if (event.GetId() == XRCID("IDT_CHARACTER_EXPERIENCE")) {
        saveslot->setExperience(character, value);
    } else if (event.GetId() == XRCID("IDT_CHARACTER_MAXHP")) {
        saveslot->setMaxHP(character, value);
    } else if (event.GetId() == XRCID("IDT_CHARACTER_MAXMP")) {
        saveslot->setMaxMP(character, value);
    } else if (event.GetId() == XRCID("IDT_CHARACTER_STRENGTH")) {
        saveslot->setStrength(character, value);
    } else if (event.GetId() == XRCID("IDT_CHARACTER_INTELLIGENCE")) {
        saveslot->setIntelligence(character, value);
    } else if (event.GetId() == XRCID("IDT_CHARACTER_DEXTERITY")) {
        saveslot->setDexterity(character, value);
    }
}

void MainFrame::onStoneChange(wxCommandEvent &event) {
    enum Virtue stone = HUMILITY;

    if (event.GetId() == XRCID("IDC_INVENTORY_BLUE")) {
        stone = HONESTY;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_YELLOW")) {
        stone = COMPASSION;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_RED")) {
        stone = VALOR;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_GREEN")) {
        stone = JUSTICE;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_ORANGE")) {
        stone = SACRIFICE;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_PURPLE")) {
        stone = HONOR;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_WHITE")) {
        stone = SPIRITUALITY;
    }
    
    saveslot->setStone(stone, event.IsChecked());
}

void MainFrame::onToolHaveChange(wxCommandEvent &event) {
    enum Tool tool = WHEEL;

    if (event.GetId() == XRCID("IDC_INVENTORY_KEY")) {
        tool = KEY;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_SEXTANT")) {
        tool = SEXTANT;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_SCALE")) {
        tool = SCALE;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_FLUTE")) {
        tool = FLUTE;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_CANDLE")) {
        tool = CANDLE;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_BOOK")) {
        tool = BOOK;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_BELL")) {
        tool = BELL;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_HORN")) {
        tool = HORN;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_SKULL")) {
        tool = SKULL;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_TRUTHKEY")) {
        tool = TRUTHKEY;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_LOVEKEY")) {
        tool = LOVEKEY;
    } else if (event.GetId() == XRCID("IDC_INVENTORY_COURAGEKEY")) {
        tool = COURAGEKEY;
    }
    
    saveslot->setTool(tool, (event.IsChecked() ? 1 : 0));
}

void MainFrame::onToolQuantityChange(wxScrollEvent &event) {
    enum Tool tool = OIL;
    
    if (event.GetId() == XRCID("IDS_INVENTORY_TORCH")) {
        tool = TORCH;
    } else if (event.GetId() == XRCID("IDS_INVENTORY_GEM")) {
        tool = GEM;
    }
    
    saveslot->setTool(tool, event.GetPosition());
}

void MainFrame::onVirtueChange(wxScrollEvent &event) {
    enum Virtue virtue = HUMILITY;

    if (event.GetId() == XRCID("IDS_HERO_HONESTY")) {
        virtue = HONESTY;
    } else if (event.GetId() == XRCID("IDS_HERO_COMPASSION")) {
        virtue = COMPASSION;
    } else if (event.GetId() == XRCID("IDS_HERO_VALOR")) {
        virtue = VALOR;
    } else if (event.GetId() == XRCID("IDS_HERO_JUSTICE")) {
        virtue = JUSTICE;
    } else if (event.GetId() == XRCID("IDS_HERO_SACRIFICE")) {
        virtue = SACRIFICE;
    } else if (event.GetId() == XRCID("IDS_HERO_HONOR")) {
        virtue = HONOR;
    } else if (event.GetId() == XRCID("IDS_HERO_SPIRITUALITY")) {
        virtue = SPIRITUALITY;
    }
    
    saveslot->setVirtue(virtue, event.GetPosition());
}

void MainFrame::onWhirlpoolChange(wxCommandEvent &event) {
    if (ignoreEvents) {
        return;
    }
    
    wxTextCtrl *ctrl = dynamic_cast<wxTextCtrl *>(event.GetEventObject());
    std::pair<int, int> location = saveslot->getWhirlpoolLocation();
    int value = std::atoi(ctrl->GetValue());
    
    if (event.GetId() == XRCID("IDT_TRANSPORTATION_WHIRLPOOLLATITUDE")) {
        location.first = value;
    } else {
        // we must be longitude if we're here
        wxASSERT(event.GetId() ==
                 XRCID("IDT_TRANSPORTATION_WHIRLPOOLLONGITUDE"));
                 
        location.second = value;
    }
    
    saveslot->setWhirlpoolLocation(location);
}

void MainFrame::onWindowClosing(wxCloseEvent &event) {
    if (event.CanVeto()) {
        if (isOpen()) {
            if (!close()) {
                event.Veto();
                return;
            }
        }
    }
    
    Destroy();
}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_CHECKBOX(XRCID("IDC_PARTY_MAGE"), MainFrame::onJoinedChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_BARD"), MainFrame::onJoinedChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_FIGHTER"), MainFrame::onJoinedChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_DRUID"), MainFrame::onJoinedChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_TINKER"), MainFrame::onJoinedChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_PALADIN"), MainFrame::onJoinedChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_RANGER"), MainFrame::onJoinedChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_SHEPHERD"), MainFrame::onJoinedChange)

    EVT_CHECKBOX(XRCID("IDC_PARTY_LIGHT"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_MISSILE"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_AWAKEN"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_CURE"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_WIND"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_HEAL"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_FIRE"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_EXIT"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_DISPEL"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_VIEW"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_PROTECT"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_ICE"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_BLINK"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_ENERGY"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_QUICK"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_SLEEP"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_REFLECT"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_NEGATE"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_DESTROY"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_JINX"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_SQUISH"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_GATE"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_TREMOR"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_LIFE"), MainFrame::onMagicChange)
    EVT_CHECKBOX(XRCID("IDC_PARTY_DEFEAT"), MainFrame::onMagicChange)
    
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_HONESTY"), MainFrame::onRuneChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_COMPASSION"), MainFrame::onRuneChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_VALOR"), MainFrame::onRuneChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_JUSTICE"), MainFrame::onRuneChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_SACRIFICE"), MainFrame::onRuneChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_HONOR"), MainFrame::onRuneChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_SPIRITUALITY"), MainFrame::onRuneChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_HUMILITY"), MainFrame::onRuneChange)
    
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_BLUE"), MainFrame::onStoneChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_YELLOW"), MainFrame::onStoneChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_RED"), MainFrame::onStoneChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_GREEN"), MainFrame::onStoneChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_ORANGE"), MainFrame::onStoneChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_PURPLE"), MainFrame::onStoneChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_WHITE"), MainFrame::onStoneChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_BLACK"), MainFrame::onStoneChange)
    
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_KEY"), MainFrame::onToolHaveChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_SEXTANT"), MainFrame::onToolHaveChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_SCALE"), MainFrame::onToolHaveChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_FLUTE"), MainFrame::onToolHaveChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_CANDLE"), MainFrame::onToolHaveChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_BOOK"), MainFrame::onToolHaveChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_BELL"), MainFrame::onToolHaveChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_HORN"), MainFrame::onToolHaveChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_SKULL"), MainFrame::onToolHaveChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_TRUTHKEY"), MainFrame::onToolHaveChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_COURAGEKEY"), MainFrame::onToolHaveChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_LOVEKEY"), MainFrame::onToolHaveChange)
    EVT_CHECKBOX(XRCID("IDC_INVENTORY_WHEEL"), MainFrame::onToolHaveChange)
    
    EVT_CHECKBOX(XRCID("IDC_TRANSPORTATION_SHIP1"), MainFrame::onShipChange)
    EVT_CHECKBOX(XRCID("IDC_TRANSPORTATION_SHIP2"), MainFrame::onShipChange)
    EVT_CHECKBOX(XRCID("IDC_TRANSPORTATION_SHIP3"), MainFrame::onShipChange)
    EVT_CHECKBOX(XRCID("IDC_TRANSPORTATION_SHIP4"), MainFrame::onShipChange)
    
    EVT_CHECKBOX(XRCID("IDC_CHARACTER_EQUIPPED1"),
        MainFrame::onEquippedChange)
    EVT_CHECKBOX(XRCID("IDC_CHARACTER_EQUIPPED2"),
        MainFrame::onEquippedChange)
    EVT_CHECKBOX(XRCID("IDC_CHARACTER_EQUIPPED3"),
        MainFrame::onEquippedChange)
    EVT_CHECKBOX(XRCID("IDC_CHARACTER_EQUIPPED4"),
        MainFrame::onEquippedChange)
    EVT_CHECKBOX(XRCID("IDC_CHARACTER_EQUIPPED5"),
        MainFrame::onEquippedChange)
    EVT_CHECKBOX(XRCID("IDC_CHARACTER_EQUIPPED6"),
        MainFrame::onEquippedChange)
        
    EVT_CHOICE(XRCID("IDC_PARTY_START"), MainFrame::onStartLocationChange)
        
    EVT_CHOICE(XRCID("IDC_PARTY_MEMBER1"), MainFrame::onMemberClassChange)
    EVT_CHOICE(XRCID("IDC_PARTY_MEMBER2"), MainFrame::onMemberClassChange)
    EVT_CHOICE(XRCID("IDC_PARTY_MEMBER3"), MainFrame::onMemberClassChange)
    EVT_CHOICE(XRCID("IDC_PARTY_MEMBER4"), MainFrame::onMemberClassChange)
    
    EVT_CHOICE(XRCID("IDC_TRANSPORTATION_TRAMMEL"), MainFrame::onPhaseChange)
    EVT_CHOICE(XRCID("IDC_TRANSPORTATION_FELUCCA"), MainFrame::onPhaseChange)
    
    EVT_CHOICE(XRCID("IDC_CHARACTER_EQUIPMENT1"), MainFrame::onEquipmentChange)
    EVT_CHOICE(XRCID("IDC_CHARACTER_EQUIPMENT2"), MainFrame::onEquipmentChange)
    EVT_CHOICE(XRCID("IDC_CHARACTER_EQUIPMENT3"), MainFrame::onEquipmentChange)
    EVT_CHOICE(XRCID("IDC_CHARACTER_EQUIPMENT4"), MainFrame::onEquipmentChange)
    EVT_CHOICE(XRCID("IDC_CHARACTER_EQUIPMENT5"), MainFrame::onEquipmentChange)
    EVT_CHOICE(XRCID("IDC_CHARACTER_EQUIPMENT6"), MainFrame::onEquipmentChange)
    
    EVT_CLOSE(MainFrame::onWindowClosing)
    
    EVT_COMMAND_SCROLL(XRCID("IDS_HERO_HONESTY"), MainFrame::onVirtueChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_HERO_COMPASSION"), MainFrame::onVirtueChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_HERO_VALOR"), MainFrame::onVirtueChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_HERO_JUSTICE"), MainFrame::onVirtueChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_HERO_SACRIFICE"), MainFrame::onVirtueChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_HERO_HONOR"), MainFrame::onVirtueChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_HERO_SPIRITUALITY"),MainFrame::onVirtueChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_HERO_HUMILITY"), MainFrame::onVirtueChange)

    EVT_COMMAND_SCROLL(XRCID("IDS_INVENTORY_ASH"), MainFrame::onHerbChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_INVENTORY_GINSENG"), MainFrame::onHerbChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_INVENTORY_GARLIC"), MainFrame::onHerbChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_INVENTORY_SILKWEB"), MainFrame::onHerbChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_INVENTORY_MOSS"), MainFrame::onHerbChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_INVENTORY_PEARL"), MainFrame::onHerbChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_INVENTORY_FUNGUS"), MainFrame::onHerbChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_INVENTORY_MANROOT"), MainFrame::onHerbChange)
    
    EVT_COMMAND_SCROLL(XRCID("IDS_INVENTORY_TORCH"),
        MainFrame::onToolQuantityChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_INVENTORY_GEM"),
        MainFrame::onToolQuantityChange)
    EVT_COMMAND_SCROLL(XRCID("IDS_INVENTORY_OIL"),
        MainFrame::onToolQuantityChange)
        
    EVT_MENU(wxID_OPEN, MainFrame::onFileOpen)
    EVT_MENU(wxID_SAVE, MainFrame::onFileSave)
    EVT_MENU(wxID_SAVEAS, MainFrame::onFileSaveAs)
    EVT_MENU(wxID_CLOSE, MainFrame::onFileClose)
    EVT_MENU(wxID_EXIT, MainFrame::onFileExit)

    EVT_MENU(XRCID("IDM_GAME_GAME1"), MainFrame::onGameChange)
    EVT_MENU(XRCID("IDM_GAME_GAME2"), MainFrame::onGameChange)
    EVT_MENU(XRCID("IDM_GAME_GAME3"), MainFrame::onGameChange)
    
    EVT_MENU(XRCID("IDM_LOCATION_PLACE_MOONGLOW"),
        MainFrame::onLocationPlaceChange)
    EVT_MENU(XRCID("IDM_LOCATION_PLACE_BRITAIN"),
        MainFrame::onLocationPlaceChange)
    EVT_MENU(XRCID("IDM_LOCATION_PLACE_JHELOM"),
        MainFrame::onLocationPlaceChange)
    EVT_MENU(XRCID("IDM_LOCATION_PLACE_YEW"),
        MainFrame::onLocationPlaceChange)
    EVT_MENU(XRCID("IDM_LOCATION_PLACE_MINOC"),
        MainFrame::onLocationPlaceChange)
    EVT_MENU(XRCID("IDM_LOCATION_PLACE_TRINSIC"),
        MainFrame::onLocationPlaceChange)
    EVT_MENU(XRCID("IDM_LOCATION_PLACE_SKARABRAE"),
        MainFrame::onLocationPlaceChange)
    EVT_MENU(XRCID("IDM_LOCATION_PLACE_MAGINCIA"),
        MainFrame::onLocationPlaceChange)
    
    EVT_MENU(XRCID("IDM_LOCATION_PLACE_LYCAEUM"),
        MainFrame::onLocationPlaceChange)
    EVT_MENU(XRCID("IDM_LOCATION_PLACE_EMPATHABBEY"),
        MainFrame::onLocationPlaceChange)
    EVT_MENU(XRCID("IDM_LOCATION_PLACE_SERPENTSHOLD"),
        MainFrame::onLocationPlaceChange)
    
    EVT_MENU(XRCID("IDM_LOCATION_PLACE_PAWS"),
        MainFrame::onLocationPlaceChange)
    EVT_MENU(XRCID("IDM_LOCATION_PLACE_VESPER"),
        MainFrame::onLocationPlaceChange)
    EVT_MENU(XRCID("IDM_LOCATION_PLACE_BUCCANEERSDEN"),
        MainFrame::onLocationPlaceChange)
    EVT_MENU(XRCID("IDM_LOCATION_PLACE_COVE"),
        MainFrame::onLocationPlaceChange)
    
    EVT_MENU(XRCID("IDM_LOCATION_BALLOON"), MainFrame::onLocationBalloon)
    
    EVT_MENU(XRCID("IDM_LOCATION_SHIP1"), MainFrame::onLocationShip)
    EVT_MENU(XRCID("IDM_LOCATION_SHIP2"), MainFrame::onLocationShip)
    EVT_MENU(XRCID("IDM_LOCATION_SHIP3"), MainFrame::onLocationShip)
    EVT_MENU(XRCID("IDM_LOCATION_SHIP4"), MainFrame::onLocationShip)

    EVT_MENU(wxID_ABOUT, MainFrame::onHelpAbout)
    
    EVT_RADIOBOX(XRCID("IDRB_CHARACTER_SELECT"), MainFrame::onCharacterChange)
    
    EVT_TEXT(XRCID("IDT_HERO_NAME"), MainFrame::onHerosNameChange)
    
    EVT_TEXT(XRCID("IDT_PARTY_GOLD"), MainFrame::onGoldChange)
    
    EVT_TEXT(XRCID("IDT_TRANSPORTATION_BALLOONLATITUDE"),
        MainFrame::onBalloonChange)
    EVT_TEXT(XRCID("IDT_TRANSPORTATION_BALLOONLONGITUDE"),
        MainFrame::onBalloonChange)
        
    EVT_TEXT(XRCID("IDT_TRANSPORTATION_WHIRLPOOLLATITUDE"),
        MainFrame::onWhirlpoolChange)
    EVT_TEXT(XRCID("IDT_TRANSPORTATION_WHIRLPOOLLONGITUDE"),
        MainFrame::onWhirlpoolChange)
    
    EVT_TEXT(XRCID("IDT_TRANSPORTATION_SHIP1LATITUDE"),
        MainFrame::onShipLocationChange)
    EVT_TEXT(XRCID("IDT_TRANSPORTATION_SHIP1LONGITUDE"),
        MainFrame::onShipLocationChange)
    EVT_TEXT(XRCID("IDT_TRANSPORTATION_SHIP2LATITUDE"),
        MainFrame::onShipLocationChange)
    EVT_TEXT(XRCID("IDT_TRANSPORTATION_SHIP2LONGITUDE"),
        MainFrame::onShipLocationChange)
    EVT_TEXT(XRCID("IDT_TRANSPORTATION_SHIP3LATITUDE"),
        MainFrame::onShipLocationChange)
    EVT_TEXT(XRCID("IDT_TRANSPORTATION_SHIP3LONGITUDE"),
        MainFrame::onShipLocationChange)
    EVT_TEXT(XRCID("IDT_TRANSPORTATION_SHIP4LATITUDE"),
        MainFrame::onShipLocationChange)
    EVT_TEXT(XRCID("IDT_TRANSPORTATION_SHIP4LONGITUDE"),
        MainFrame::onShipLocationChange)
        
    EVT_TEXT(XRCID("IDT_CHARACTER_LEVEL"), MainFrame::onStatChange)
    EVT_TEXT(XRCID("IDT_CHARACTER_EXPERIENCE"), MainFrame::onStatChange)
    EVT_TEXT(XRCID("IDT_CHARACTER_HP"), MainFrame::onStatChange)
    EVT_TEXT(XRCID("IDT_CHARACTER_MP"), MainFrame::onStatChange)
    EVT_TEXT(XRCID("IDT_CHARACTER_MAXHP"), MainFrame::onStatChange)
    EVT_TEXT(XRCID("IDT_CHARACTER_MAXMP"), MainFrame::onStatChange)
    EVT_TEXT(XRCID("IDT_CHARACTER_STRENGTH"), MainFrame::onStatChange)
    EVT_TEXT(XRCID("IDT_CHARACTER_INTELLIGENCE"), MainFrame::onStatChange)
    EVT_TEXT(XRCID("IDT_CHARACTER_DEXTERITY"), MainFrame::onStatChange)
    
    EVT_UPDATE_UI(wxID_CLOSE, MainFrame::onSaveCloseUpdate)
    EVT_UPDATE_UI(wxID_SAVE, MainFrame::onSaveUpdate)
    EVT_UPDATE_UI(wxID_SAVEAS, MainFrame::onSaveCloseUpdate)
    
    EVT_UPDATE_UI(XRCID("IDM_GAME_GAME1"), MainFrame::onGameMenuUpdate)
    EVT_UPDATE_UI(XRCID("IDM_GAME_GAME2"), MainFrame::onGameMenuUpdate)
    EVT_UPDATE_UI(XRCID("IDM_GAME_GAME3"), MainFrame::onGameMenuUpdate)
    
    EVT_UPDATE_UI(XRCID("IDC_PARTY_MEMBER3"), MainFrame::onMemberUpdate)
    EVT_UPDATE_UI(XRCID("IDC_PARTY_MEMBER4"), MainFrame::onMemberUpdate)
    
    EVT_UPDATE_UI(XRCID("IDT_TRANSPORTATION_SHIP1LATITUDE"),
        MainFrame::onShipUpdate)
    EVT_UPDATE_UI(XRCID("IDT_TRANSPORTATION_SHIP2LATITUDE"),
        MainFrame::onShipUpdate)
    EVT_UPDATE_UI(XRCID("IDT_TRANSPORTATION_SHIP3LATITUDE"),
        MainFrame::onShipUpdate)
    EVT_UPDATE_UI(XRCID("IDT_TRANSPORTATION_SHIP4LATITUDE"),
        MainFrame::onShipUpdate)
    
    EVT_UPDATE_UI(XRCID("IDT_TRANSPORTATION_SHIP1LONGITUDE"),
        MainFrame::onShipUpdate)
    EVT_UPDATE_UI(XRCID("IDT_TRANSPORTATION_SHIP2LONGITUDE"),
        MainFrame::onShipUpdate)
    EVT_UPDATE_UI(XRCID("IDT_TRANSPORTATION_SHIP3LONGITUDE"),
        MainFrame::onShipUpdate)
    EVT_UPDATE_UI(XRCID("IDT_TRANSPORTATION_SHIP4LONGITUDE"),
        MainFrame::onShipUpdate)
    
    EVT_UPDATE_UI(XRCID("IDC_CHARACTER_EQUIPPED1"), MainFrame::onEquippedUpdate)
    EVT_UPDATE_UI(XRCID("IDC_CHARACTER_EQUIPPED2"), MainFrame::onEquippedUpdate)
    EVT_UPDATE_UI(XRCID("IDC_CHARACTER_EQUIPPED3"), MainFrame::onEquippedUpdate)
    EVT_UPDATE_UI(XRCID("IDC_CHARACTER_EQUIPPED4"), MainFrame::onEquippedUpdate)
    EVT_UPDATE_UI(XRCID("IDC_CHARACTER_EQUIPPED5"), MainFrame::onEquippedUpdate)
    EVT_UPDATE_UI(XRCID("IDC_CHARACTER_EQUIPPED6"), MainFrame::onEquippedUpdate)
END_EVENT_TABLE()

IMPLEMENT_CLASS(MainFrame, wxFrame)

