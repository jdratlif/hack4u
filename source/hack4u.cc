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

// $Id: hack4u.cc,v 1.5 2004/11/28 21:42:45 technoplaza Exp $
 
#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif

#include "hack4u.hh"
#include "view/MainFrame.hh"

using namespace hack4u;

// static variable initialization
const wxString *Hack4u::APP_NAME = new wxString(wxT(PACKAGE_NAME));
const wxString *Hack4u::APP_VERSION = new wxString(wxT(PACKAGE_VERSION));
const wxString *Hack4u::APP_COPYRIGHT =
    new wxString(wxT("Copyright (C) 2004 emuWorks"));
const wxString *Hack4u::APP_URL =
    new wxString(wxT("http://games.technoplaza.net/"));

IMPLEMENT_APP(Hack4u)
IMPLEMENT_CLASS(Hack4u, wxApp)

bool Hack4u::OnInit() {
    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->Load(wxT("xrc/hack4u.xrc"));
    
    MainFrame *frame = new MainFrame;
    frame->SetTitle(*APP_NAME + wxT(' ') + *APP_VERSION);
    frame->Show(true);
    SetTopWindow(frame);
    
    return true;
}

