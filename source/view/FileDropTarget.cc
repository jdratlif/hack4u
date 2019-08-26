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

// $Id: FileDropTarget.cc,v 1.7 2008/12/16 22:12:52 jdratlif Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "view/FileDropTarget.hh"
#include "view/MainFrame.hh"

using namespace hack4u;

bool FileDropTarget::OnDropFiles(wxCoord, wxCoord, const wxArrayString &files) {
    int size = files.GetCount();

    if (size > 0) {
        wxString filename = files[0];
        owner->load(filename);
    }

    return true;
}

