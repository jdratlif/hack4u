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

// $Id: FileIOException.hh,v 1.1 2006/03/14 22:54:22 technoplaza Exp $

#ifndef _FILEIOEXCEPTION_HH_
#define _FILEIOEXCEPTION_HH_

#include <stdexcept>

namespace hack4u {
    /// error codes that cause FileIOExceptions to be thrown
    enum FileIOError {
        FIE_CANNOTOPEN, FIE_IOERROR
    };
    
    class FileIOException : public std::runtime_error {
    private:
        enum FileIOError error;
        
    public:
        /**
         * Creates a new FileIOException.
         *
         * @param error The reason for this FileIOException.
         */
        FileIOException(enum FileIOError error);
        
        /**
         * Gets the error code of this FileIOException.
         */
        enum FileIOError getError() const;
    };
    
    inline FileIOException::FileIOException(enum FileIOError error) :
        std::runtime_error("FileIOException"), error(error) {}
        
    inline enum FileIOError FileIOException::getError() const
        { return error; }
}

#endif

