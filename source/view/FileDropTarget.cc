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

// $Id: FileDropTarget.cc,v 1.2 2005/08/03 11:11:39 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "FileDropTarget.hh"

using namespace hack4u;

bool FileDropTarget::OnDropFiles(wxCoord, wxCoord, const wxArrayString &files) {
    int size = files.GetCount();

    if (size > 0) {
        wxString filename = files[0];

        #ifdef __WXGTK__
            filename.Replace("%20", " ");
        #endif

        owner->load(filename);
    }

    return true;
}

