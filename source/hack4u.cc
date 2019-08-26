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

// $Id: hack4u.cc,v 1.13 2006/03/20 01:00:18 technoplaza Exp $
 
#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif

#include <wx/xrc/xmlres.h>

#include "hack4u.hh"
#include "view/MainFrame.hh"

// prototype for InitXmlResource function
void InitXmlResource();

using namespace hack4u;

// static variable initialization
const wxString *Hack4u::APP_NAME =
    new wxString(wxT("hack4u"));

const wxString *Hack4u::APP_VERSION =
    new wxString(wxT("1.2"));

const wxString *Hack4u::APP_COPYRIGHT =
    new wxString(wxT("Copyright (C) 2004-2006 emuWorks"));

const wxString *Hack4u::APP_URL =
    new wxString(wxT("http://games.technoplaza.net/"));

bool Hack4u::OnInit() {
    // initialize the XRC resources
    wxXmlResource::Get()->InitAllHandlers();
    InitXmlResource();
    
    (new MainFrame)->Show();
    
    return true;
}

IMPLEMENT_CLASS(Hack4u, wxApp)
IMPLEMENT_APP(Hack4u)

