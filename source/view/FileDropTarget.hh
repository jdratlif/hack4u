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

// $Id: FileDropTarget.hh,v 1.7 2006/03/15 13:39:37 technoplaza Exp $

#ifndef _FILEDROPTARGET_HH
#define _FILEDROPTARGET_HH

#include <wx/dnd.h>

namespace hack4u {
    class MainFrame;
    
    /**
     * Class implementing a wxFileDropTarget for the MainFrame class.
     */
    class FileDropTarget : public wxFileDropTarget {
    private:
        MainFrame *owner;
        
    public:
        /**
         * Constructor for the FileDropTarget.
         * 
         * @param owner The MainFrame associated with this FileDropTarget.
         */
        FileDropTarget(MainFrame *owner);
        
        /**
         * Virtual method called when files are dropped on this target.
         *
         * @param x The x-coordinate of the drop.
         * @param y The y-coordinate of the drop.
         * @param files The files dropped on this target.
         */
        virtual bool OnDropFiles(wxCoord x, wxCoord y, 
                                 const wxArrayString &files);
    };
    
    inline FileDropTarget::FileDropTarget(MainFrame *owner) : owner(owner) {}
}

#endif

