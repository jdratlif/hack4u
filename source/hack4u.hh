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

// $Id: hack4u.hh,v 1.11 2008/12/16 22:12:52 jdratlif Exp $
 
#ifndef HACK4U_HACK4U_HH_
#define HACK4U_HACK4U_HH_

/**
 * Private hack4u namespace is used for all classs and members of this project.
 */
namespace hack4u {
    /**
     * The main class. Initializes the application and creates the view.
     */
    class Hack4u : public wxApp {
        DECLARE_CLASS(Hack4u)
        
    public:
        /// The name of the application.
        static const wxString *APP_NAME;
        
        /// The version of the application.
        static const wxString *APP_VERSION;
        
        /// The copyright notice for the application.
        static const wxString *APP_COPYRIGHT;
        
        /// The website URL for this application.
        static const wxString *APP_URL;
    
        /**
         * Called by wxWidgets to start initialization of the application.
         *
         * @return true if initialization should proceed; false otherwise.
         */
        virtual bool OnInit();
    };
    
    DECLARE_APP(Hack4u)
};

#endif

