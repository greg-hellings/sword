/******************************************************************************
 *  rawtext.h   - code for class 'RawText'- a module that reads raw text files:
 *		  ot and nt using indexs ??.bks ??.cps ??.vss
 *
 * $Id: rawgenbook.h,v 1.5 2002/10/01 19:52:40 dglassey Exp $
 *
 * Copyright 1998 CrossWire Bible Society (http://www.crosswire.org)
 *	CrossWire Bible Society
 *	P. O. Box 2528
 *	Tempe, AZ  85280-2528
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation version 2.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 */

#ifndef RAWGENBOOK_H
#define RAWGENBOOK_H

#include <swgenbook.h>
#include <filemgr.h>

#include <defs.h>

SWORD_NAMESPACE_START

class SWDLLEXPORT RawGenBook : public SWGenBook {
	char *entryBuf;
	char *path;
	FileDesc *bdtfd;

public:
  
    
	RawGenBook(const char *ipath, const char *iname = 0, const char *idesc = 0,
			SWDisplay * idisp = 0, SWTextEncoding encoding = ENC_UNKNOWN,
			SWTextDirection dir = DIRECTION_LTR,
			SWTextMarkup markup = FMT_UNKNOWN, const char* ilang = 0);
	virtual ~RawGenBook();
	virtual char *getRawEntry();
	// write interface ----------------------------
	virtual bool isWritable() {
		return ((bdtfd->getFd() > 0) && ((bdtfd->mode & O_RDWR) == O_RDWR));
	}
	static char createModule(const char *ipath);
	virtual void setEntry(const char *inbuf, long len = -1);	// Modify current module entry
	virtual void linkEntry(const SWKey * linkKey);	// Link current module entry to other module entry
	virtual void deleteEntry();	// Delete current module entry
	virtual SWKey *CreateKey();
	// end write interface ------------------------


	// OPERATORS -----------------------------------------------------------------
	
	SWMODULE_OPERATORS

};

SWORD_NAMESPACE_END
#endif
