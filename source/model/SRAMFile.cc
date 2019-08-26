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

// $Id: SRAMFile.cc,v 1.8 2008/12/16 22:12:52 jdratlif Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <fstream>

#include "model/SaveSlot.hh"
#include "model/SRAMFile.hh"

using namespace hack4u;

SRAMFile::SRAMFile(const wxString &filename) throw(InvalidSRAMException) {
    std::ifstream in(filename.mb_str(),
        std::ios_base::in | std::ios_base::binary);
        
    if (!in) {
        throw InvalidSRAMException(ISE_NOSUCHFILE);
    }
    
    in.read(sram, SRAM_SIZE);
    
    if (!in.good()) {
        in.close();
        
        throw InvalidSRAMException(ISE_IOERROR);
    }
    
    in.close();
    
    char *temp = new char[SAVE_SIZE];
    
    for (int slot = 0; slot < 3; ++slot) {
        std::memcpy(temp, (sram + SRAM_OFFSET + (slot * SAVE_SIZE)), SAVE_SIZE);
        saveslot[slot] = new SaveSlot(temp);
    }
    
    delete [] temp;
    
    // if all slots are invalid, the SRAM contains no valid data
    verifyChecksum();
    
    if (!(isValid(0) || isValid(1) || isValid(2))) {
        throw InvalidSRAMException(ISE_BADCHECKSUM);
    }
    
    // create backup file
    wxString bakfile = filename + wxT(".bak");
    std::ofstream out(bakfile.mb_str(),
        std::ios_base::out | std::ios_base::binary);
        
    if (out) {
        out.write(sram, SRAM_SIZE);
        out.close();
    }
}

SRAMFile::~SRAMFile() {
    for (int i = 0; i < 3; ++i) {
        delete saveslot[i];
    }
}

bool SRAMFile::isModified() const {
    return (saveslot[0]->isModified() ||
            saveslot[1]->isModified() ||
            saveslot[2]->isModified());
}

void SRAMFile::save(const wxString &filename) throw(FileIOException) {
    if (isModified()) {
        for (int slot = 0; slot < 3; ++slot) {
            char *nvram = reinterpret_cast<char *>(saveslot[slot]->nvram);
            char *ptr = (sram + SRAM_OFFSET + (slot * SAVE_SIZE));
        
            std::memcpy(ptr, nvram, SAVE_SIZE);
            
            if (isValid(slot)) {
                for (int i = 0; i < 3; ++i) {
                    char *checksum = (sram + SANITY_OFFSET + slot + (i * 3));
                    
                    if (i == 0) {
                        *checksum = nvram[0];
                    } else if (i == 1) {
                        *checksum = nvram[0] ^ SANITY_XOR1;
                    } else {
                        *checksum = nvram[0] ^ SANITY_XOR2;
                    }
                }
            }
        }
    }
    
    std::ofstream out(filename.mb_str(),
        std::ios_base::out | std::ios_base::binary);
        
    if (!out) {
        throw FileIOException(FIE_CANNOTOPEN);
    }
    
    out.write(sram, SRAM_SIZE);
    
    if (!out.good()) {
        out.close();
        throw FileIOException(FIE_IOERROR);
    }
    
    out.close();
    
    for (int i = 0; i < 3; ++i) {
        saveslot[i]->setModified(false);
    }
}

void SRAMFile::verifyChecksum() {
    for (int slot = 0; slot < 3; ++slot) {
        char byte1 = getSaveSlot(slot)->checksum();
        char byte2 = byte1 ^ SANITY_XOR1;
        char byte3 = byte1 ^ SANITY_XOR2;
        
        valid[slot] = ((byte1 == sram[SANITY_OFFSET + slot]) &&
                       (byte2 == sram[SANITY_OFFSET + slot + 3]) &&
                       (byte3 == sram[SANITY_OFFSET + slot + 6]) &&
                       (byte1 == sram[SRAM_OFFSET + (slot * SAVE_SIZE)]));
    }
}

