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

// $Id: InvalidSRAMException.hh,v 1.3 2008/12/16 22:12:52 jdratlif Exp $

#ifndef HACK4U_INVALIDSRAMEXCEPTION_HH_
#define HACK4U_INVALIDSRAMEXCEPTION_HH_

#include <stdexcept>

namespace hack4u {
    enum InvalidSRAMError {
        ISE_NOSUCHFILE, ISE_IOERROR, ISE_BADCHECKSUM
    };
    
    class InvalidSRAMException : public std::runtime_error {
    private:
        enum InvalidSRAMError error;
        
    public:
        /**
         * Creates a new InvalidSRAMException.
         *
         * @param error The reason for the exception.
         */
        InvalidSRAMException(enum InvalidSRAMError error);
        
        /**
         * Gets the error code that triggered this exception.
         *
         * @return The error code.
         */
        enum InvalidSRAMError getError() const;
    };
    
    inline InvalidSRAMException::
        InvalidSRAMException(enum InvalidSRAMError error) :
        std::runtime_error("InvalidSRAMException"), error(error) {}
        
    inline enum InvalidSRAMError InvalidSRAMException::getError() const
        { return error; }
}

#endif

