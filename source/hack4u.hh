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

// $Id: hack4u.hh,v 1.7 2005/08/03 11:11:39 technoplaza Exp $
 
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

