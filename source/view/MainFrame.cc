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

// $Id: MainFrame.cc,v 1.23 2004/12/03 10:34:46 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <fstream>
#include <cstring>

#include "MainFrame.hh"
#include "../hack4u.hh"

using namespace hack4u;

const wxString MainFrame::CITY_NAMES[] = {
    wxT("Moonglow"), wxT("Britain"), wxT("Jhelom"), wxT("Yew"),
    wxT("Minoc"), wxT("Trinsic"), wxT("Skara Brae"), wxT("Magincia")
};

const wxString MainFrame::CHARACTER_NAMES[] = {
    wxT("Mage"), wxT("Bard"), wxT("Fighter"), wxT("Druid"),
    wxT("Tinker"), wxT("Paladin"), wxT("Ranger"), wxT("Shepherd")
};

const char *MainFrame::ICON[] = {
    "16 16 5 1",
    " 	c None",
    "!	c #BCBCBC",
    "#	c #747474",
    "$	c #FCFCFC",
    "%	c black",
    "!!!!!#$$$$$$!!!!",
    "!!!!#!$$$$$$$!!!",
    "!!!#!!######$$!!",
    "!!!%!##%%%%##$!!",
    "!!!%###!!!%##$!!",
    "!!!%%##!!!%##%!!",
    "!!!!%%##!%##%!!!",
    "#%$$$$%####$$$$$",
    "!%!$$$$$##$$$$$$",
    "!%#############$",
    "!%%%%%%%##%%%%%$",
    "!!!!!!%%##!!!!!!",
    "!!%%%%%%##!!!!!!",
    "%%%%%%%%##!!!!!!",
    "!%%%%%%%%%!!!!!!",
    "!!!!!!!!!!!!!!!!"
};

IMPLEMENT_DYNAMIC_CLASS(MainFrame, wxFrame)

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_CLOSE(MainFrame::windowClosing)

    EVT_MENU(XRCID("IDM_FILE_LOAD"), MainFrame::fileLoad)
    EVT_MENU(XRCID("IDM_FILE_SAVE"), MainFrame::fileSave)
    EVT_MENU(XRCID("IDM_FILE_SAVE_AS"), MainFrame::fileSaveAs)
    EVT_MENU(XRCID("IDM_FILE_CLOSE"), MainFrame::fileClose)
    EVT_MENU(XRCID("IDM_FILE_EXIT"), MainFrame::fileExit)
    
    EVT_MENU(XRCID("IDM_GAME_GAME1"), MainFrame::gameChange)
    EVT_MENU(XRCID("IDM_GAME_GAME2"), MainFrame::gameChange)
    EVT_MENU(XRCID("IDM_GAME_GAME3"), MainFrame::gameChange)
    
    EVT_MENU(XRCID("IDM_HELP_ABOUT"), MainFrame::helpAbout)
    
    EVT_TEXT(XRCID("ID_GENERAL_HEROSNAME"), MainFrame::herosNameChange)
    
    EVT_CHOICE(XRCID("ID_GENERAL_PARTY1"), MainFrame::memberClassChange)
    EVT_CHOICE(XRCID("ID_GENERAL_PARTY2"), MainFrame::memberClassChange)
    EVT_CHOICE(XRCID("ID_GENERAL_PARTY3"), MainFrame::memberClassChange)
    EVT_CHOICE(XRCID("ID_GENERAL_PARTY4"), MainFrame::memberClassChange)
    
    EVT_COMMAND_SCROLL(XRCID("ID_GENERAL_HONESTY"), MainFrame::virtueChange)
    EVT_COMMAND_SCROLL(XRCID("ID_GENERAL_COMPASSION"), MainFrame::virtueChange)
    EVT_COMMAND_SCROLL(XRCID("ID_GENERAL_VALOR"), MainFrame::virtueChange)
    EVT_COMMAND_SCROLL(XRCID("ID_GENERAL_JUSTICE"), MainFrame::virtueChange)
    EVT_COMMAND_SCROLL(XRCID("ID_GENERAL_SACRIFICE"), MainFrame::virtueChange)
    EVT_COMMAND_SCROLL(XRCID("ID_GENERAL_HONOR"), MainFrame::virtueChange)
    EVT_COMMAND_SCROLL(XRCID("ID_GENERAL_SPIRITUALITY"), MainFrame::virtueChange)
    EVT_COMMAND_SCROLL(XRCID("ID_GENERAL_HUMILITY"), MainFrame::virtueChange)
    
    EVT_CHECKBOX(XRCID("ID_GENERAL_LIGHT"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_MISSILE"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_AWAKEN"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_CURE"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_WIND"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_HEAL"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_FIRE"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_EXIT"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_DISPEL"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_VIEW"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_PROTECT"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_ICE"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_BLINK"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_ENERGY"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_QUICK"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_SLEEP"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_REFLECT"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_NEGATE"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_DESTROY"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_JINX"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_SQUISH"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_GATE"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_TREMOR"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_LIFE"), MainFrame::magicChange)
    EVT_CHECKBOX(XRCID("ID_GENERAL_DEFEAT"), MainFrame::magicChange)
    
    EVT_CHOICE(XRCID("ID_GENERAL_TRAMMEL"), MainFrame::phaseChange)
    EVT_CHOICE(XRCID("ID_GENERAL_FELUCCA"), MainFrame::phaseChange)
    
    EVT_TEXT(XRCID("ID_INVENTORY_GOLD"), MainFrame::goldChange)
    
    EVT_COMMAND_SCROLL(XRCID("ID_INVENTORY_ASH"), MainFrame::herbChange)
    EVT_COMMAND_SCROLL(XRCID("ID_INVENTORY_GINSENG"), MainFrame::herbChange)
    EVT_COMMAND_SCROLL(XRCID("ID_INVENTORY_GARLIC"), MainFrame::herbChange)
    EVT_COMMAND_SCROLL(XRCID("ID_INVENTORY_SILKWEB"), MainFrame::herbChange)
    EVT_COMMAND_SCROLL(XRCID("ID_INVENTORY_MOSS"), MainFrame::herbChange)
    EVT_COMMAND_SCROLL(XRCID("ID_INVENTORY_PEARL"), MainFrame::herbChange)
    EVT_COMMAND_SCROLL(XRCID("ID_INVENTORY_FUNGUS"), MainFrame::herbChange)
    EVT_COMMAND_SCROLL(XRCID("ID_INVENTORY_MANROOT"), MainFrame::herbChange)
    
    EVT_CHECKBOX(XRCID("ID_INVENTORY_HONESTY"), MainFrame::runeChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_COMPASSION"), MainFrame::runeChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_VALOR"), MainFrame::runeChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_JUSTICE"), MainFrame::runeChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_SACRIFICE"), MainFrame::runeChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_HONOR"), MainFrame::runeChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_SPIRITUALITY"), MainFrame::runeChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_HUMILITY"), MainFrame::runeChange)
    
    EVT_CHECKBOX(XRCID("ID_INVENTORY_BLUE"), MainFrame::stoneChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_YELLOW"), MainFrame::stoneChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_RED"), MainFrame::stoneChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_GREEN"), MainFrame::stoneChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_ORANGE"), MainFrame::stoneChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_PURPLE"), MainFrame::stoneChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_WHITE"), MainFrame::stoneChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_BLACK"), MainFrame::stoneChange)
    
    EVT_COMMAND_SCROLL(XRCID("ID_INVENTORY_TORCH"), MainFrame::toolQuantityChange)
    EVT_COMMAND_SCROLL(XRCID("ID_INVENTORY_GEM"), MainFrame::toolQuantityChange)
    EVT_COMMAND_SCROLL(XRCID("ID_INVENTORY_OIL"), MainFrame::toolQuantityChange)
    
    EVT_CHECKBOX(XRCID("ID_INVENTORY_KEY"), MainFrame::toolHaveChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_SEXTANT"), MainFrame::toolHaveChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_SCALE"), MainFrame::toolHaveChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_FLUTE"), MainFrame::toolHaveChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_CANDLE"), MainFrame::toolHaveChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_BOOK"), MainFrame::toolHaveChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_BELL"), MainFrame::toolHaveChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_HORN"), MainFrame::toolHaveChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_SKULL"), MainFrame::toolHaveChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_TRUTHKEY"), MainFrame::toolHaveChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_COURAGEKEY"), MainFrame::toolHaveChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_LOVEKEY"), MainFrame::toolHaveChange)
    EVT_CHECKBOX(XRCID("ID_INVENTORY_WHEEL"), MainFrame::toolHaveChange)
    
    EVT_CHOICE(XRCID("ID_CHARACTER_CHARACTER"), MainFrame::characterChange)
    
    EVT_TEXT(XRCID("ID_CHARACTER_LEVEL"), MainFrame::statChange)
    EVT_TEXT(XRCID("ID_CHARACTER_EXPERIENCE"), MainFrame::statChange)
    EVT_TEXT(XRCID("ID_CHARACTER_CURRENTHP"), MainFrame::statChange)
    EVT_TEXT(XRCID("ID_CHARACTER_CURRENTMP"), MainFrame::statChange)
    EVT_TEXT(XRCID("ID_CHARACTER_MAXHP"), MainFrame::statChange)
    EVT_TEXT(XRCID("ID_CHARACTER_MAXMP"), MainFrame::statChange)
    EVT_TEXT(XRCID("ID_CHARACTER_STRENGTH"), MainFrame::statChange)
    EVT_TEXT(XRCID("ID_CHARACTER_INTELLIGENCE"), MainFrame::statChange)
    EVT_TEXT(XRCID("ID_CHARACTER_DEXTERITY"), MainFrame::statChange)
    
    EVT_CHOICE(XRCID("ID_CHARACTER_FIRST"), MainFrame::equipmentChange)
    EVT_CHOICE(XRCID("ID_CHARACTER_SECOND"), MainFrame::equipmentChange)
    EVT_CHOICE(XRCID("ID_CHARACTER_THIRD"), MainFrame::equipmentChange)
    EVT_CHOICE(XRCID("ID_CHARACTER_FOURTH"), MainFrame::equipmentChange)
    EVT_CHOICE(XRCID("ID_CHARACTER_FIFTH"), MainFrame::equipmentChange)
    EVT_CHOICE(XRCID("ID_CHARACTER_SIXTH"), MainFrame::equipmentChange)
    
    EVT_CHECKBOX(XRCID("ID_CHARACTER_FIRSTEQUIPPED"), MainFrame::equippedChange)
    EVT_CHECKBOX(XRCID("ID_CHARACTER_SECONDEQUIPPED"), MainFrame::equippedChange)
    EVT_CHECKBOX(XRCID("ID_CHARACTER_THIRDEQUIPPED"), MainFrame::equippedChange)
    EVT_CHECKBOX(XRCID("ID_CHARACTER_FOURTHEQUIPPED"), MainFrame::equippedChange)
    EVT_CHECKBOX(XRCID("ID_CHARACTER_FIFTHEQUIPPED"), MainFrame::equippedChange)
    EVT_CHECKBOX(XRCID("ID_CHARACTER_SIXTHEQUIPPED"), MainFrame::equippedChange)
END_EVENT_TABLE()

MainFrame::MainFrame() {
    currentSlot = -1;
    
    SetParent(NULL);
    CreateControls();
    Centre();
    
    SetDropTarget(new FileDropTarget(this));
}

void MainFrame::CreateControls() {
    wxXmlResource::Get()->LoadFrame(this, GetParent(), wxT("ID_MAIN_FRAME"));
    SetIcon(ICON);
    
    notebook = XRCCTRL(*this, "ID_NOTEBOOK", wxNotebook);
    notebook->Show(false);
    
    wxMenuBar &menubar = *GetMenuBar();
    
    games[0] = menubar.FindItem(XRCID("IDM_GAME_GAME1"));
    games[0]->Enable(false);
    
    games[1] = menubar.FindItem(XRCID("IDM_GAME_GAME2"));
    games[1]->Enable(false);
    
    games[2] = menubar.FindItem(XRCID("IDM_GAME_GAME3"));
    games[2]->Enable(false);
    
    fileSaveItem = menubar.FindItem(XRCID("IDM_FILE_SAVE"));
    fileSaveAsItem = menubar.FindItem(XRCID("IDM_FILE_SAVE_AS"));
    fileCloseItem = menubar.FindItem(XRCID("IDM_FILE_CLOSE"));
    
    setOpen(false);

    wxStringList letters("A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
                         "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V",
                         "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g",
                         "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r",
                         "s", "t", "u", "v", "w", "x", "y", "z", "!", "-", "_",
                         NULL);
    
    wxTextValidator herosNameValidator(wxFILTER_INCLUDE_CHAR_LIST);
    herosNameValidator.SetIncludeList(letters);
    
    herosNameText = XRCCTRL(*this, "ID_GENERAL_HEROSNAME", wxTextCtrl);
    herosNameText->SetMaxLength(5);
    herosNameText->SetValidator(herosNameValidator);
    
    memberClass[0] = XRCCTRL(*this, "ID_GENERAL_PARTY1", wxChoice);
    memberClass[1] = XRCCTRL(*this, "ID_GENERAL_PARTY2", wxChoice);
    memberClass[2] = XRCCTRL(*this, "ID_GENERAL_PARTY3", wxChoice);
    memberClass[3] = XRCCTRL(*this, "ID_GENERAL_PARTY4", wxChoice);
    
    honestySlider = XRCCTRL(*this, "ID_GENERAL_HONESTY", wxSlider);
    compassionSlider = XRCCTRL(*this, "ID_GENERAL_COMPASSION", wxSlider);
    valorSlider = XRCCTRL(*this, "ID_GENERAL_VALOR", wxSlider);
    justiceSlider = XRCCTRL(*this, "ID_GENERAL_JUSTICE", wxSlider);
    sacrificeSlider = XRCCTRL(*this, "ID_GENERAL_SACRIFICE", wxSlider);
    honorSlider = XRCCTRL(*this, "ID_GENERAL_HONOR", wxSlider);
    spiritualitySlider = XRCCTRL(*this, "ID_GENERAL_SPIRITUALITY", wxSlider);
    humilitySlider = XRCCTRL(*this, "ID_GENERAL_HUMILITY", wxSlider);
    
    lightSpellCheck = XRCCTRL(*this, "ID_GENERAL_LIGHT", wxCheckBox);
    missileSpellCheck = XRCCTRL(*this, "ID_GENERAL_MISSILE", wxCheckBox);
    awakenSpellCheck = XRCCTRL(*this, "ID_GENERAL_AWAKEN", wxCheckBox);
    cureSpellCheck = XRCCTRL(*this, "ID_GENERAL_CURE", wxCheckBox);
    windSpellCheck = XRCCTRL(*this, "ID_GENERAL_WIND", wxCheckBox);
    healSpellCheck = XRCCTRL(*this, "ID_GENERAL_HEAL", wxCheckBox);
    fireSpellCheck = XRCCTRL(*this, "ID_GENERAL_FIRE", wxCheckBox);
    exitSpellCheck = XRCCTRL(*this, "ID_GENERAL_EXIT", wxCheckBox);
    dispelSpellCheck = XRCCTRL(*this, "ID_GENERAL_DISPEL", wxCheckBox);
    viewSpellCheck = XRCCTRL(*this, "ID_GENERAL_VIEW", wxCheckBox);
    protectSpellCheck = XRCCTRL(*this, "ID_GENERAL_PROTECT", wxCheckBox);
    iceSpellCheck = XRCCTRL(*this, "ID_GENERAL_ICE", wxCheckBox);
    blinkSpellCheck = XRCCTRL(*this, "ID_GENERAL_BLINK", wxCheckBox);
    energySpellCheck = XRCCTRL(*this, "ID_GENERAL_ENERGY", wxCheckBox);
    quickSpellCheck = XRCCTRL(*this, "ID_GENERAL_QUICK", wxCheckBox);
    sleepSpellCheck = XRCCTRL(*this, "ID_GENERAL_SLEEP", wxCheckBox);
    reflectSpellCheck = XRCCTRL(*this, "ID_GENERAL_REFLECT", wxCheckBox);
    negateSpellCheck = XRCCTRL(*this, "ID_GENERAL_NEGATE", wxCheckBox);
    destroySpellCheck = XRCCTRL(*this, "ID_GENERAL_DESTROY", wxCheckBox);
    jinxSpellCheck = XRCCTRL(*this, "ID_GENERAL_JINX", wxCheckBox);
    squishSpellCheck = XRCCTRL(*this, "ID_GENERAL_SQUISH", wxCheckBox);
    gateSpellCheck = XRCCTRL(*this, "ID_GENERAL_GATE", wxCheckBox);
    tremorSpellCheck = XRCCTRL(*this, "ID_GENERAL_TREMOR", wxCheckBox);
    lifeSpellCheck = XRCCTRL(*this, "ID_GENERAL_LIFE", wxCheckBox);
    defeatSpellCheck = XRCCTRL(*this, "ID_GENERAL_DEFEAT", wxCheckBox);
    
    trammelChoice = XRCCTRL(*this, "ID_GENERAL_TRAMMEL", wxChoice);
    feluccaChoice = XRCCTRL(*this, "ID_GENERAL_FELUCCA", wxChoice);
    
    wxTextValidator numberValidator(wxFILTER_NUMERIC);
    goldText = XRCCTRL(*this, "ID_INVENTORY_GOLD", wxTextCtrl);
    goldText->SetValidator(numberValidator);
    goldText->SetMaxLength(4);
    
    ashSlider = XRCCTRL(*this, "ID_INVENTORY_ASH", wxSlider);
    ginsengSlider = XRCCTRL(*this, "ID_INVENTORY_GINSENG", wxSlider);
    garlicSlider = XRCCTRL(*this, "ID_INVENTORY_GARLIC", wxSlider);
    silkwebSlider = XRCCTRL(*this, "ID_INVENTORY_SILKWEB", wxSlider);
    mossSlider = XRCCTRL(*this, "ID_INVENTORY_MOSS", wxSlider);
    pearlSlider = XRCCTRL(*this, "ID_INVENTORY_PEARL", wxSlider);
    fungusSlider = XRCCTRL(*this, "ID_INVENTORY_FUNGUS", wxSlider);
    manrootSlider = XRCCTRL(*this, "ID_INVENTORY_MANROOT", wxSlider);
    
    honestyRuneCheck = XRCCTRL(*this, "ID_INVENTORY_HONESTY", wxCheckBox);
    compassionRuneCheck = XRCCTRL(*this, "ID_INVENTORY_COMPASSION", wxCheckBox);
    valorRuneCheck = XRCCTRL(*this, "ID_INVENTORY_VALOR", wxCheckBox);
    justiceRuneCheck = XRCCTRL(*this, "ID_INVENTORY_JUSTICE", wxCheckBox);
    sacrificeRuneCheck = XRCCTRL(*this, "ID_INVENTORY_SACRIFICE", wxCheckBox);
    honorRuneCheck = XRCCTRL(*this, "ID_INVENTORY_HONOR", wxCheckBox);
    spiritualityRuneCheck = XRCCTRL(*this, "ID_INVENTORY_SPIRITUALITY", wxCheckBox);
    humilityRuneCheck = XRCCTRL(*this, "ID_INVENTORY_HUMILITY", wxCheckBox);
    
    blueStoneCheck = XRCCTRL(*this, "ID_INVENTORY_BLUE", wxCheckBox);
    yellowStoneCheck = XRCCTRL(*this, "ID_INVENTORY_YELLOW", wxCheckBox);
    redStoneCheck = XRCCTRL(*this, "ID_INVENTORY_RED", wxCheckBox);
    greenStoneCheck = XRCCTRL(*this, "ID_INVENTORY_GREEN", wxCheckBox);
    orangeStoneCheck = XRCCTRL(*this, "ID_INVENTORY_ORANGE", wxCheckBox);
    purpleStoneCheck = XRCCTRL(*this, "ID_INVENTORY_PURPLE", wxCheckBox);
    whiteStoneCheck = XRCCTRL(*this, "ID_INVENTORY_WHITE", wxCheckBox);
    blackStoneCheck = XRCCTRL(*this, "ID_INVENTORY_BLACK", wxCheckBox);
    
    torchSlider = XRCCTRL(*this, "ID_INVENTORY_TORCH", wxSlider);
    gemSlider = XRCCTRL(*this, "ID_INVENTORY_GEM", wxSlider);
    oilSlider = XRCCTRL(*this, "ID_INVENTORY_OIL", wxSlider);
    
    keyCheck = XRCCTRL(*this, "ID_INVENTORY_KEY", wxCheckBox);
    sextantCheck = XRCCTRL(*this, "ID_INVENTORY_SEXTANT", wxCheckBox);
    scaleCheck = XRCCTRL(*this, "ID_INVENTORY_SCALE", wxCheckBox);
    fluteCheck = XRCCTRL(*this, "ID_INVENTORY_FLUTE", wxCheckBox);
    candleCheck = XRCCTRL(*this, "ID_INVENTORY_CANDLE", wxCheckBox);
    bookCheck = XRCCTRL(*this, "ID_INVENTORY_BOOK", wxCheckBox);
    bellCheck = XRCCTRL(*this, "ID_INVENTORY_BELL", wxCheckBox);
    hornCheck = XRCCTRL(*this, "ID_INVENTORY_HORN", wxCheckBox);
    skullCheck = XRCCTRL(*this, "ID_INVENTORY_SKULL", wxCheckBox);
    truthKeyCheck = XRCCTRL(*this, "ID_INVENTORY_TRUTHKEY", wxCheckBox);
    courageKeyCheck = XRCCTRL(*this, "ID_INVENTORY_COURAGEKEY", wxCheckBox);
    loveKeyCheck = XRCCTRL(*this, "ID_INVENTORY_LOVEKEY", wxCheckBox);
    wheelCheck = XRCCTRL(*this, "ID_INVENTORY_WHEEL", wxCheckBox);
    
    characterChoice = XRCCTRL(*this, "ID_CHARACTER_CHARACTER", wxChoice);
    
    wxStringList numbers("2", "3", "4", "5", "6", "7", "8", NULL);
    wxTextValidator levelValidator(wxFILTER_INCLUDE_CHAR_LIST);
    levelValidator.SetIncludeList(numbers);
    
    levelText = XRCCTRL(*this, "ID_CHARACTER_LEVEL", wxTextCtrl);
    levelText->SetValidator(levelValidator);
    levelText->SetMaxLength(1);
    
    experienceText = XRCCTRL(*this, "ID_CHARACTER_EXPERIENCE", wxTextCtrl);
    experienceText->SetValidator(numberValidator);
    experienceText->SetMaxLength(4);
    
    currentHPText = XRCCTRL(*this, "ID_CHARACTER_CURRENTHP", wxTextCtrl);
    currentHPText->SetValidator(numberValidator);
    currentHPText->SetMaxLength(3);
    
    currentMPText = XRCCTRL(*this, "ID_CHARACTER_CURRENTMP", wxTextCtrl);
    currentMPText->SetValidator(numberValidator);
    currentMPText->SetMaxLength(2);
    
    maxHPText = XRCCTRL(*this, "ID_CHARACTER_MAXHP", wxTextCtrl);
    maxHPText->SetValidator(numberValidator);
    maxHPText->SetMaxLength(3);
    
    maxMPText = XRCCTRL(*this, "ID_CHARACTER_MAXMP", wxTextCtrl);
    maxMPText->SetValidator(numberValidator);
    maxMPText->SetMaxLength(2);
    
    strengthText = XRCCTRL(*this, "ID_CHARACTER_STRENGTH", wxTextCtrl);
    strengthText->SetValidator(numberValidator);
    strengthText->SetMaxLength(2);
    
    intelligenceText = XRCCTRL(*this, "ID_CHARACTER_INTELLIGENCE", wxTextCtrl);
    intelligenceText->SetValidator(numberValidator);
    intelligenceText->SetMaxLength(2);
    
    dexterityText = XRCCTRL(*this, "ID_CHARACTER_DEXTERITY", wxTextCtrl);
    dexterityText->SetValidator(numberValidator);
    dexterityText->SetMaxLength(2);
    
    itemChoice[0] = XRCCTRL(*this, "ID_CHARACTER_FIRST", wxChoice);
    itemEquippedCheck[0] = XRCCTRL(*this, "ID_CHARACTER_FIRSTEQUIPPED", wxCheckBox);
    itemChoice[1] = XRCCTRL(*this, "ID_CHARACTER_SECOND", wxChoice);
    itemEquippedCheck[1] = XRCCTRL(*this, "ID_CHARACTER_SECONDEQUIPPED", wxCheckBox);
    itemChoice[2] = XRCCTRL(*this, "ID_CHARACTER_THIRD", wxChoice);
    itemEquippedCheck[2] = XRCCTRL(*this, "ID_CHARACTER_THIRDEQUIPPED", wxCheckBox);
    itemChoice[3] = XRCCTRL(*this, "ID_CHARACTER_FOURTH", wxChoice);
    itemEquippedCheck[3] = XRCCTRL(*this, "ID_CHARACTER_FOURTHEQUIPPED", wxCheckBox);
    itemChoice[4] = XRCCTRL(*this, "ID_CHARACTER_FIFTH", wxChoice);
    itemEquippedCheck[4] = XRCCTRL(*this, "ID_CHARACTER_FIFTHEQUIPPED", wxCheckBox);
    itemChoice[5] = XRCCTRL(*this, "ID_CHARACTER_SIXTH", wxChoice);
    itemEquippedCheck[5] = XRCCTRL(*this, "ID_CHARACTER_SIXTHEQUIPPED", wxCheckBox);
}

void MainFrame::setFeluccaOptions(int trammel) {
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

void MainFrame::loadStats(SaveSlot &slot, int character) {
    wxString str;
    
    int temp = currentSlot;
    currentSlot = -1;
    
    str.Printf("%d", slot.getLevel(character));
    levelText->SetValue(str);
    
    str.Printf("%d", slot.getExperience(character));
    experienceText->SetValue(str);
    
    str.Printf("%d", slot.getCurrentHP(character));
    currentHPText->SetValue(str);
    
    str.Printf("%d", slot.getCurrentMP(character));
    currentMPText->SetValue(str);
    
    str.Printf("%d", slot.getMaxHP(character));
    maxHPText->SetValue(str);
    
    str.Printf("%d", slot.getMaxMP(character));
    maxMPText->SetValue(str);
    
    str.Printf("%d", slot.getStrength(character));
    strengthText->SetValue(str);
    
    str.Printf("%d", slot.getIntelligence(character));
    intelligenceText->SetValue(str);
    
    str.Printf("%d", slot.getDexterity(character));
    dexterityText->SetValue(str);
    
    for (int index = 0; index < 6; index++) {
        int item = slot.getEquipment(character, index);
        
        itemChoice[index]->SetSelection(item & 0x7F);
        itemEquippedCheck[index]->SetValue(item & 0x80);
    }
    
    currentSlot = temp;
}

void MainFrame::loadGame(int game) {
    SaveSlot &slot = *saveslot[game];
    
    slot.modified = false;
    herosNameText->SetValue(slot.getHerosName());
    
    memberClass[0]->SetSelection(slot.getMember(0) - 1);
    memberClass[1]->SetSelection(slot.getMember(1));
    memberClass[2]->SetSelection(slot.getMember(2));
    memberClass[3]->SetSelection(slot.getMember(3));
    
    honestySlider->SetValue(slot.getVirtue(HONESTY));
    compassionSlider->SetValue(slot.getVirtue(COMPASSION));
    valorSlider->SetValue(slot.getVirtue(VALOR));
    justiceSlider->SetValue(slot.getVirtue(JUSTICE));
    sacrificeSlider->SetValue(slot.getVirtue(SACRIFICE));
    honorSlider->SetValue(slot.getVirtue(HONOR));
    spiritualitySlider->SetValue(slot.getVirtue(SPIRITUALITY));
    humilitySlider->SetValue(slot.getVirtue(HUMILITY));
    
    lightSpellCheck->SetValue(slot.hasMagic(LIGHT));
    missileSpellCheck->SetValue(slot.hasMagic(MISSILE));
    awakenSpellCheck->SetValue(slot.hasMagic(AWAKEN));
    cureSpellCheck->SetValue(slot.hasMagic(CURE));
    windSpellCheck->SetValue(slot.hasMagic(WIND));
    healSpellCheck->SetValue(slot.hasMagic(HEAL));
    fireSpellCheck->SetValue(slot.hasMagic(FIRE));
    exitSpellCheck->SetValue(slot.hasMagic(EXIT));
    dispelSpellCheck->SetValue(slot.hasMagic(DISPEL));
    viewSpellCheck->SetValue(slot.hasMagic(VIEW));
    protectSpellCheck->SetValue(slot.hasMagic(PROTECT));
    iceSpellCheck->SetValue(slot.hasMagic(ICE));
    blinkSpellCheck->SetValue(slot.hasMagic(BLINK));
    energySpellCheck->SetValue(slot.hasMagic(ENERGY));
    quickSpellCheck->SetValue(slot.hasMagic(QUICK));
    sleepSpellCheck->SetValue(slot.hasMagic(SLEEP));
    reflectSpellCheck->SetValue(slot.hasMagic(REFLECT));
    negateSpellCheck->SetValue(slot.hasMagic(NEGATE));
    destroySpellCheck->SetValue(slot.hasMagic(DESTROY));
    jinxSpellCheck->SetValue(slot.hasMagic(JINX));
    squishSpellCheck->SetValue(slot.hasMagic(SQUISH));
    gateSpellCheck->SetValue(slot.hasMagic(GATE));
    tremorSpellCheck->SetValue(slot.hasMagic(TREMOR));
    lifeSpellCheck->SetValue(slot.hasMagic(LIFE));
    defeatSpellCheck->SetValue(slot.hasMagic(DEFEAT));
    
    trammelChoice->SetSelection(slot.getPhase(TRAMMEL));
    setFeluccaOptions(slot.getPhase(TRAMMEL));
    feluccaChoice->SetSelection(slot.getPhase(FELUCCA));
    
    wxString gold;
    gold.Printf("%d", slot.getGold());
    goldText->SetValue(gold);
    
    ashSlider->SetValue(slot.getHerb(ASH));
    ginsengSlider->SetValue(slot.getHerb(GINSENG));
    garlicSlider->SetValue(slot.getHerb(GARLIC));
    silkwebSlider->SetValue(slot.getHerb(SILKWEB));
    mossSlider->SetValue(slot.getHerb(MOSS));
    pearlSlider->SetValue(slot.getHerb(PEARL));
    fungusSlider->SetValue(slot.getHerb(FUNGUS));
    manrootSlider->SetValue(slot.getHerb(MANROOT));
    
    honestyRuneCheck->SetValue(slot.hasRune(HONESTY));
    compassionRuneCheck->SetValue(slot.hasRune(COMPASSION));
    valorRuneCheck->SetValue(slot.hasRune(VALOR));
    justiceRuneCheck->SetValue(slot.hasRune(JUSTICE));
    sacrificeRuneCheck->SetValue(slot.hasRune(SACRIFICE));
    honorRuneCheck->SetValue(slot.hasRune(HONOR));
    spiritualityRuneCheck->SetValue(slot.hasRune(SPIRITUALITY));
    humilityRuneCheck->SetValue(slot.hasRune(HUMILITY));
    
    blueStoneCheck->SetValue(slot.hasStone(HONESTY));
    yellowStoneCheck->SetValue(slot.hasStone(COMPASSION));
    redStoneCheck->SetValue(slot.hasStone(VALOR));
    greenStoneCheck->SetValue(slot.hasStone(JUSTICE));
    orangeStoneCheck->SetValue(slot.hasStone(SACRIFICE));
    purpleStoneCheck->SetValue(slot.hasStone(HONOR));
    whiteStoneCheck->SetValue(slot.hasStone(SPIRITUALITY));
    blackStoneCheck->SetValue(slot.hasStone(HUMILITY));
    
    torchSlider->SetValue(slot.getTool(TORCH));
    gemSlider->SetValue(slot.getTool(GEM));
    oilSlider->SetValue(slot.getTool(OIL));
    
    keyCheck->SetValue(slot.getTool(KEY));
    sextantCheck->SetValue(slot.getTool(SEXTANT));
    scaleCheck->SetValue(slot.getTool(SCALE));
    fluteCheck->SetValue(slot.getTool(FLUTE));
    candleCheck->SetValue(slot.getTool(CANDLE));
    bookCheck->SetValue(slot.getTool(BOOK));
    bellCheck->SetValue(slot.getTool(BELL));
    hornCheck->SetValue(slot.getTool(HORN));
    skullCheck->SetValue(slot.getTool(SKULL));
    truthKeyCheck->SetValue(slot.getTool(TRUTHKEY));
    courageKeyCheck->SetValue(slot.getTool(COURAGEKEY));
    loveKeyCheck->SetValue(slot.getTool(LOVEKEY));
    wheelCheck->SetValue(slot.getTool(WHEEL));
    
    loadStats(slot, characterChoice->GetSelection());
    
    currentSlot = game;
    notebook->SetSelection(0);
    notebook->Show(true);
}

void MainFrame::load(wxString &filename) {
    if (isOpen()) {
        if (!close()) {
            return;
        }
    }
    
    char nvram[SAVE_SIZE];
    
    sram = new char[SRAM_SIZE];
    std::ifstream in(filename.mb_str(), std::ios::in | std::ios::binary);
    in.read(sram, SRAM_SIZE);
    in.close();
    
    wxString bakfile = filename + ".bak";
    std::ofstream out(bakfile.mb_str(), std::ios::out | std::ios::binary);
    out.write(sram, SRAM_SIZE);
    out.close();
    
    for (int slot = 0; slot < 3; slot++) {
        memcpy(nvram, (sram + SRAM_OFFSET + (slot * SAVE_SIZE)), SAVE_SIZE);
        saveslot[slot] = new SaveSlot((const unsigned char *)nvram);
        games[slot]->Enable(saveslot[slot]->isValid());
        
        if (saveslot[slot]->isValid()) {
            games[slot]->Enable(true);
        } else {
            games[0]->Enable(false);
        }
    }
    
    if (saveslot[0]->isValid()) {
        loadGame(0);
    } else if (saveslot[1]->isValid()) {
        loadGame(1);
    } else if (saveslot[2]->isValid()) {
        loadGame(2);
    } else {
        wxMessageBox(wxT("No Ultima: Quest of the Avatar games exist in the SRAM file you loaded."),
                     wxT("Error: No Games Found"), wxOK | wxICON_ERROR);
    }
    
    setOpen(true);
}

void MainFrame::fileLoad(wxCommandEvent &event) {
    static wxFileDialog *dlg = new wxFileDialog(this, 
        wxT("Choose a .SAV File"), "", "", 
        wxT("NES SRAM File (*.sav)|*.sav"), (wxOPEN | wxCHANGE_DIR));
        
    int value = dlg->ShowModal();
    
    if (value == wxID_OK) {
        sramFile = dlg->GetPath();
        load(sramFile);
    }
}

bool MainFrame::isValidParty() {
    char members = 0;
    bool end = false;
    
    for (int i = 0; i < 4; i++) {
        int member = memberClass[i]->GetSelection();
        
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

bool MainFrame::hasValidEquipment(int character) {
    bool bow = false;
    bool weapon = false;
    bool armor = false;
    
    SaveSlot &slot = *(saveslot[currentSlot]);
    
    for (int i = 0; i < 6; i++) {
        int item = slot.getEquipment(character, i);
        
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

bool MainFrame::save(wxString &filename) {
    if (!isValidParty()) {
        int choice = wxMessageBox(wxT("Duplicate or missing party members selected.\nContinue Saving?"),
                                  wxT("Warning: Invalid Party"),
                                  wxYES_NO | wxICON_QUESTION,
                                  this);
                                 
        if (choice != wxYES) {
            return false;
        }
    }
    
    for (int character = MAGE; character < SHEPHERD; character++) {
        if (!hasValidEquipment(character)) {
            int choice = wxMessageBox(CHARACTER_NAMES[character] + 
                                      wxT(" has more than one equipped item of the same type.\nContinue Saving?"),
                                      wxT("Warning: Invalid Equipment"),
                                      wxYES_NO | wxICON_QUESTION,
                                      this);
                                      
            if (choice != wxYES) {
                return false;
            }
        }
    }
    
    char *checksum;
    
    for (int offset = 0; offset < 3; offset++) {
        char *nvram = (char *)saveslot[offset]->nvram;
        char *save = (sram + SRAM_OFFSET + (offset * SAVE_SIZE));
        
        memcpy(save, nvram, SAVE_SIZE);
        
        for (int byte = 0; byte < 3; byte++) {
            char *checksum = (sram + SANITY_OFFSET + offset + (byte * 3));
            
            switch (byte) {
                case 0:
                    *checksum = nvram[0];
                    break;
                case 1:
                    *checksum = (nvram[0] ^ SANITY_XOR1);
                    break;
                case 2:
                    *checksum = (nvram[0] ^ SANITY_XOR2);
                    break;
            }
        }
    }
    
    std::ofstream out(filename.mb_str(), std::ios::binary | std::ios::out);
    out.write(sram, SRAM_SIZE);
    out.close();
    
    saveslot[0]->modified = false;
    saveslot[1]->modified = false;
    saveslot[2]->modified = false;
    
    return true;
}

void MainFrame::fileSave(wxCommandEvent &event) {
    save(sramFile);
}

void MainFrame::fileSaveAs(wxCommandEvent &event) {
    static wxFileDialog *dlg = new wxFileDialog(this, 
        wxT("Choose a .SAV File"), "", "", 
        wxT("NES SRAM File (*.sav)|*.sav"), (wxSAVE | wxCHANGE_DIR));
    
    int value = dlg->ShowModal();
    
    if (value == wxID_OK) {
        sramFile = dlg->GetPath();
        save(sramFile);
    }
}

void MainFrame::setOpen(bool open) {
    fileSaveItem->Enable(open);
    fileSaveAsItem->Enable(open);
    fileCloseItem->Enable(open);
    
    if (!open && (currentSlot != -1)) {
        currentSlot = -1;
        
        delete saveslot[0];
        delete saveslot[1];
        delete saveslot[2];
        delete sram;
    }
    
    this->open = open;
}

bool MainFrame::close() {
    if (saveslot[0]->isModified() || 
        saveslot[1]->isModified() || 
        saveslot[2]->isModified()) {
        int choice = wxMessageBox(wxT("Save Game File Before Closing?"),
                                  wxT("Warning: Unsaved Changed"),
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
    
    notebook->Show(false);
    
    games[0]->Check(true);
    games[0]->Enable(false);
    games[1]->Enable(false);
    games[2]->Enable(false);
    
    fileSaveItem->Enable(false);
    fileSaveAsItem->Enable(false);
    fileCloseItem->Enable(false);
    
    setOpen(false);
    
    return true;
}

void MainFrame::fileClose(wxCommandEvent &event) {
    close();
}

void MainFrame::fileExit(wxCommandEvent &event) {
    if (isOpen()) {
        if (close()) {
            Close(true);
        }
    } else {
        Close(true);
    }
}

void MainFrame::windowClosing(wxCloseEvent &event) {
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

void MainFrame::gameChange(wxCommandEvent &event) {
    int id = event.GetId();
    
    currentSlot = -1;
    
    if (id == XRCID("IDM_GAME_GAME1")) {
        loadGame(0);
    } else if (id == XRCID("IDM_GAME_GAME2")) {
        loadGame(1);
    } else if (id == XRCID("IDM_GAME_GAME3")) {
        loadGame(2);
    }
}

void MainFrame::helpAbout(wxCommandEvent &event) {
    wxMessageDialog dlg(this, *Hack4u::APP_NAME + wxT(' ') + 
                        *Hack4u::APP_VERSION + wxT('\n') +
                        *Hack4u::APP_COPYRIGHT + wxT('\n') +
                        *Hack4u::APP_URL, wxT("About ") + 
                        *Hack4u::APP_NAME + wxT("..."),
                        wxOK | wxICON_INFORMATION);
    dlg.ShowModal();
}

void MainFrame::herosNameChange(wxCommandEvent &event) {
    if (currentSlot == -1) {
        return;
    }
    
    wxString string = herosNameText->GetValue();
    saveslot[currentSlot]->setHerosName(string);
}

void MainFrame::memberClassChange(wxCommandEvent &event) {
    if (currentSlot == -1) {
        return;
    }
    
    wxChoice *ctrl = (wxChoice *)event.GetEventObject();
    int character = ctrl->GetSelection();   
    int member = 3;
    
    if (ctrl == memberClass[0]) {
        member = 0;
    } else if (ctrl == memberClass[1]) {
        member = 1;
    } else if (ctrl == memberClass[2]) {
        member = 2;
    }
    
    saveslot[currentSlot]->setMember(member, ((member == 0) ? 
                                              (character + 1) : character));
}

void MainFrame::virtueChange(wxScrollEvent &event) {
    if (currentSlot == -1) {
        return;
    }
    
    wxSlider *ctrl = (wxSlider *)event.GetEventObject();
    int virtue = HUMILITY;
    
    if (ctrl == honestySlider) {
        virtue = HONESTY;
    } else if (ctrl == compassionSlider) {
        virtue = COMPASSION;
    } else if (ctrl == valorSlider) {
        virtue = VALOR;
    } else if (ctrl == justiceSlider) {
        virtue = JUSTICE;
    } else if (ctrl == sacrificeSlider) {
        virtue = SACRIFICE;
    } else if (ctrl == honorSlider) {
        virtue = HONOR;
    } else if (ctrl == spiritualitySlider) {
        virtue = SPIRITUALITY;
    }
    
    saveslot[currentSlot]->setVirtue(virtue, ctrl->GetValue());
}

void MainFrame::magicChange(wxCommandEvent &event) {
    if (currentSlot == -1) {
        return;
    }
    
    wxCheckBox *ctrl = (wxCheckBox *)event.GetEventObject();
    int magic = DEFEAT;
    
    if (ctrl == lightSpellCheck) {
        magic = LIGHT;
    } else if (ctrl == missileSpellCheck) {
        magic = MISSILE;
    } else if (ctrl == awakenSpellCheck) {
        magic = AWAKEN;
    } else if (ctrl == cureSpellCheck) {
        magic = CURE;
    } else if (ctrl == windSpellCheck) {
        magic = WIND;
    } else if (ctrl == healSpellCheck) {
        magic = HEAL;
    } else if (ctrl == fireSpellCheck) {
        magic = FIRE;
    } else if (ctrl == exitSpellCheck) {
        magic = EXIT;
    } else if (ctrl == dispelSpellCheck) {
        magic = DISPEL;
    } else if (ctrl == viewSpellCheck) {
        magic = VIEW;
    } else if (ctrl == protectSpellCheck) {
        magic = PROTECT;
    } else if (ctrl == iceSpellCheck) {
        magic = ICE;
    } else if (ctrl == blinkSpellCheck) {
        magic = BLINK;
    } else if (ctrl == energySpellCheck) {
        magic = ENERGY;
    } else if (ctrl == quickSpellCheck) {
        magic = QUICK;
    } else if (ctrl == sleepSpellCheck) {
        magic = SLEEP;
    } else if (ctrl == reflectSpellCheck) {
        magic = REFLECT;
    } else if (ctrl == negateSpellCheck) {
        magic = NEGATE;
    } else if (ctrl == destroySpellCheck) {
        magic = DESTROY;
    } else if (ctrl == jinxSpellCheck) {
        magic = JINX;
    } else if (ctrl == squishSpellCheck) {
        magic = SQUISH;
    } else if (ctrl == gateSpellCheck) {
        magic = GATE;
    } else if (ctrl == tremorSpellCheck) {
        magic = TREMOR;
    } else if (ctrl == lifeSpellCheck) {
        magic = LIFE;
    }
    
    saveslot[currentSlot]->setMagic(magic, ctrl->IsChecked());
}

void MainFrame::phaseChange(wxCommandEvent &event) {
    if (currentSlot == -1) {
        return;
    }
    
    wxChoice *ctrl = (wxChoice *)event.GetEventObject();
    int trammel, felucca;
    
    if (ctrl == trammelChoice) {
        trammel = ctrl->GetSelection();
        setFeluccaOptions(trammel);
    } else {
        trammel = trammelChoice->GetSelection();
    }
    
    felucca = feluccaChoice->GetSelection();
    
    saveslot[currentSlot]->setPhase(trammel, felucca);
}

void MainFrame::goldChange(wxCommandEvent &event) {
    if (currentSlot == -1) {
        return;
    }
    
    saveslot[currentSlot]->setGold(atoi(goldText->GetValue()));
}

void MainFrame::herbChange(wxScrollEvent &event) {
    if (currentSlot == -1) {
        return;
    }
    
    wxSlider *ctrl = (wxSlider *)event.GetEventObject();
    int herb = MANROOT;
    
    if (ctrl == ashSlider) {
        herb = ASH;
    } else if (ctrl == ginsengSlider) {
        herb = GINSENG;
    } else if (ctrl == garlicSlider) {
        herb = GARLIC;
    } else if (ctrl == silkwebSlider) {
        herb = SILKWEB;
    } else if (ctrl == mossSlider) {
        herb = MOSS;
    } else if (ctrl == pearlSlider) {
        herb = PEARL;
    } else if (ctrl == fungusSlider) {
        herb = FUNGUS;
    }
    
    saveslot[currentSlot]->setHerb(herb, ctrl->GetValue());
}

void MainFrame::runeChange(wxCommandEvent &event) {
    if (currentSlot == -1) {
        return;
    }
    
    wxCheckBox *ctrl = (wxCheckBox *)event.GetEventObject();
    int rune = HUMILITY;
    
    if (ctrl == honestyRuneCheck) {
        rune = HONESTY;
    } else if (ctrl == compassionRuneCheck) {
        rune = COMPASSION;
    } else if (ctrl == valorRuneCheck) {
        rune = VALOR;
    } else if (ctrl == justiceRuneCheck) {
        rune = JUSTICE;
    } else if (ctrl == sacrificeRuneCheck) {
        rune = SACRIFICE;
    } else if (ctrl == honorRuneCheck) {
        rune = HONOR;
    } else if (ctrl == spiritualityRuneCheck) {
        rune = SPIRITUALITY;
    }
    
    saveslot[currentSlot]->setRune(rune, ctrl->IsChecked());
}

void MainFrame::stoneChange(wxCommandEvent &event) {
    if (currentSlot == -1) {
        return;
    }
    
    wxCheckBox *ctrl = (wxCheckBox *)event.GetEventObject();
    int stone = HUMILITY;
    
    if (ctrl == blueStoneCheck) {
        stone = HONESTY;
    } else if (ctrl == yellowStoneCheck) {
        stone = COMPASSION;
    } else if (ctrl == redStoneCheck) {
        stone = VALOR;
    } else if (ctrl == greenStoneCheck) {
        stone = JUSTICE;
    } else if (ctrl == orangeStoneCheck) {
        stone = SACRIFICE;
    } else if (ctrl == purpleStoneCheck) {
        stone = HONOR;
    } else if (ctrl == whiteStoneCheck) {
        stone = SPIRITUALITY;
    }
    
    saveslot[currentSlot]->setStone(stone, ctrl->IsChecked());
}

void MainFrame::toolQuantityChange(wxScrollEvent &event) {
    if (currentSlot == -1) {
        return;
    }
    
    wxSlider *ctrl = (wxSlider *)event.GetEventObject();
    int tool = OIL;
    
    if (ctrl == torchSlider) {
        tool = TORCH;
    } else if (ctrl == gemSlider) {
        tool = GEM;
    }
    
    saveslot[currentSlot]->setTool(tool, ctrl->GetValue());
}

void MainFrame::toolHaveChange(wxCommandEvent &event) {
    if (currentSlot == -1) {
        return;
    }
    
    wxCheckBox *ctrl = (wxCheckBox *)event.GetEventObject();
    int tool = WHEEL;
    
    if (ctrl == keyCheck) {
        tool = KEY;
    } else if (ctrl == sextantCheck) {
        tool = SEXTANT;
    } else if (ctrl == scaleCheck) {
        tool = SCALE;
    } else if (ctrl == fluteCheck) {
        tool = FLUTE;
    } else if (ctrl == candleCheck) {
        tool = CANDLE;
    } else if (ctrl == bookCheck) {
        tool = BOOK;
    } else if (ctrl == bellCheck) {
        tool = BELL;
    } else if (ctrl == hornCheck) {
        tool = HORN;
    } else if (ctrl == skullCheck) {
        tool = SKULL;
    } else if (ctrl == truthKeyCheck) {
        tool = TRUTHKEY;
    } else if (ctrl == courageKeyCheck) {
        tool = COURAGEKEY;
    } else if (ctrl == loveKeyCheck) {
        tool = LOVEKEY;
    }
    
    saveslot[currentSlot]->setTool(tool, (ctrl->IsChecked() ? 1 : 0));
}

void MainFrame::characterChange(wxCommandEvent &event) {
    if (currentSlot == -1) {
        return;
    }
    
    loadStats((*(saveslot[currentSlot])), characterChoice->GetSelection());
}

void MainFrame::statChange(wxCommandEvent &event) {
    if (currentSlot == -1) {
        return;
    }
    
    wxTextCtrl *ctrl = (wxTextCtrl *)event.GetEventObject();
    int character = characterChoice->GetSelection();
    
    if (ctrl == levelText) {
        saveslot[currentSlot]->setLevel(character, atoi(ctrl->GetValue()));
    } else if (ctrl == experienceText) {
        saveslot[currentSlot]->setExperience(character, atoi(ctrl->GetValue()));
    } else if (ctrl == currentHPText) {
        saveslot[currentSlot]->setCurrentHP(character, atoi(ctrl->GetValue()));
    } else if (ctrl == currentMPText) {
        saveslot[currentSlot]->setCurrentMP(character, atoi(ctrl->GetValue()));
    } else if (ctrl == maxHPText) {
        saveslot[currentSlot]->setMaxHP(character, atoi(ctrl->GetValue()));
    } else if (ctrl == maxMPText) {
        saveslot[currentSlot]->setMaxMP(character, atoi(ctrl->GetValue()));
    } else if (ctrl == strengthText) {
        saveslot[currentSlot]->setStrength(character, atoi(ctrl->GetValue()));
    } else if (ctrl == intelligenceText) {
        saveslot[currentSlot]->setIntelligence(character, atoi(ctrl->GetValue()));
    } else if (ctrl == dexterityText) {
        saveslot[currentSlot]->setDexterity(character, atoi(ctrl->GetValue()));
    }
}

void MainFrame::setEquipment(int slot) {
    int character = characterChoice->GetSelection();
    int item = itemChoice[slot]->GetSelection();
    
    if (itemEquippedCheck[slot]->IsChecked()) {
        // can't equip nothing
        if (item != 0) {
            item |= 0x80;
        }
    }
    
    saveslot[currentSlot]->setEquipment(character, slot, item);
}

void MainFrame::equipmentChange(wxCommandEvent &event) {
    if (currentSlot == -1) {
        return;
    }
    
    wxChoice *ctrl = (wxChoice *)event.GetEventObject();
    int slot;
    
    for (slot = 0; slot < 6; slot++) {
        if (ctrl == itemChoice[slot]) {
            break;
        }
    }
    
    setEquipment(slot);
}

void MainFrame::equippedChange(wxCommandEvent &event) {
    if (currentSlot == -1) {
        return;
    }
    
    wxCheckBox *ctrl = (wxCheckBox *)event.GetEventObject();
    int slot;
    
    for (slot = 0; slot < 6; slot++) {
        if (ctrl == itemEquippedCheck[slot]) {
            break;
        }
    }
    
    setEquipment(slot);
}

