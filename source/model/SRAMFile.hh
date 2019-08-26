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

// $Id: SRAMFile.hh,v 1.2 2006/03/17 07:57:59 technoplaza Exp $

#ifndef _SRAMFILE_HH_
#define _SRAMFILE_HH_

#include <wx/string.h>

#include "exceptions/FileIOException.hh"
#include "exceptions/InvalidSRAMException.hh"
#include "model/ModelConstants.hh"

namespace hack4u {
    class SaveSlot;
    
    class SRAMFile {
    private:
        SaveSlot *saveslot[3];
        char sram[SRAM_SIZE];
        bool valid[3];
        
        /**
         * Verifies the checksums of all three SaveSlots.
         */
        void verifyChecksum();
        
    public:
        /**
         * Creates a new SRAMFile from a SAV file.
         *
         * @param filename The filename to read the SRAM data from.
         *
         * @throw InvalidSRAMException if the file is not a valid SRAMFile.
         */
        SRAMFile(const wxString &filename) throw(InvalidSRAMException);
        
        /**
         * Destructor for an SRAMFile.
         */
        ~SRAMFile();
        
        /**
         * Gets one of the SaveSlots in this SRAMFile.
         *
         * @param game Which game's SaveSlot to get.
         *
         * @return The requested SaveSlot.
         */
        SaveSlot *getSaveSlot(int game);
        
        /**
         * Checks if this SRAMFile has been modified.
         *
         * @return true if modified; false otherwise.
         */
        bool isModified() const;
        
        /**
         * Queries the validity of one of the three SaveSlots.
         *
         * @param slot The slot to test.
         *
         * @return true if the SaveSlot is valid; false otherwise.
         */
        bool isValid(int slot) const;
        
        /**
         * Saves the SRAM data to disk.
         *
         * @param filename The filename to save to.
         *
         * @throw FileIOException if the data cannot be saved.
         */
        void save(const wxString &filename) throw(FileIOException);
    };
    
    inline SaveSlot *SRAMFile::getSaveSlot(int game) { return saveslot[game]; }
    inline bool SRAMFile::isValid(int slot) const { return valid[slot]; }
}

#endif

