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

// $Id: hack4u.cc,v 1.8 2005/08/03 11:11:39 technoplaza Exp $
 
#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif

#include <iostream>
#include <sys/stat.h>

#include "hack4u.hh"
#include "view/MainFrame.hh"

using namespace hack4u;

// static variable initialization
const wxString *Hack4u::APP_NAME =
    new wxString(wxT(PACKAGE_NAME));

const wxString *Hack4u::APP_VERSION =
    new wxString(wxT(PACKAGE_VERSION));

const wxString *Hack4u::APP_COPYRIGHT =
    new wxString(wxT("Copyright (C) 2004-2005 emuWorks"));

const wxString *Hack4u::APP_URL =
    new wxString(wxT("http://games.technoplaza.net/"));

IMPLEMENT_APP(Hack4u)
IMPLEMENT_CLASS(Hack4u, wxApp)

bool Hack4u::OnInit() {
    wxString *xrcfile;
    
    if (argc == 2) {
        xrcfile = new wxString(argv[1]);
    } else {
        xrcfile = new wxString(XRC_FILE);
    }
    
    struct stat xrcstats;
    
    if (stat(xrcfile->mb_str(), &xrcstats) != 0) {
        std::cerr << "error: unable to locate XRC file " << 
            xrcfile->mb_str() << std::endl;
        return false;
    }
    
    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->Load(*xrcfile);
    
    MainFrame *frame = new MainFrame;
    frame->SetTitle(*APP_NAME + wxT(' ') + *APP_VERSION);
    frame->Show(true);
    SetTopWindow(frame);
    
    return true;
}

