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

// $Id: hack4u.hh,v 1.5 2004/11/28 21:42:45 technoplaza Exp $
 
#ifndef _HACK4U_HH
#define _HACK4U_HH

#include <wx/xrc/xmlres.h>

namespace hack4u {
    class Hack4u : public wxApp {
    public:
        virtual bool OnInit();
        
        static const wxString *APP_NAME;
        static const wxString *APP_VERSION;
        static const wxString *APP_COPYRIGHT;
        static const wxString *APP_URL;
    private:
        DECLARE_CLASS(Hack4u)
    };
    
    DECLARE_APP(Hack4u)
};

#endif

