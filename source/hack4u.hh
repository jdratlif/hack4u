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

// $Id: hack4u.hh,v 1.6 2004/12/05 02:59:28 technoplaza Exp $
 
#ifndef _HACK4U_HH
#define _HACK4U_HH

#include <wx/xrc/xmlres.h>

/**
 * Private hack4u namespace is used for all classs and members of this project.
 */
namespace hack4u {
    /**
     * The main class. Initializes the application and creates the view.
     */
    class Hack4u : public wxApp {
    public:
        /**
         * Called by wxWidgets to start initialization of the application.
         *
         * @return true if initialization should proceed; false otherwise.
         */
        virtual bool OnInit();
        
        /// The name of the application.
        static const wxString *APP_NAME;
        
        /// The version of the application.
        static const wxString *APP_VERSION;
        
        /// The copyright notice for the application.
        static const wxString *APP_COPYRIGHT;
        
        /// The website URL for this application.
        static const wxString *APP_URL;
    private:
        DECLARE_CLASS(Hack4u)
    };
    
    DECLARE_APP(Hack4u)
};

#endif

