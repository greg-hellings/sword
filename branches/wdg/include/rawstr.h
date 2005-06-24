/*****************************************************************************
 * rawstr.h   - code for class 'RawStr'- a module that reads raw text
 *			files:  ot and nt using indexs ??.bks ??.cps ??.vss
 *			and provides lookup and parsing functions based on
 *			class StrKey
 *
 * $Id$
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

#ifndef RAWSTR_H
#define RAWSTR_H

#include <defs.h>
#include <filemgr.h>
#include <swbuf.h>

SWORD_NAMESPACE_START

class SWDLLEXPORT RawStr {
	static int instance;		// number of instantiated RawStr objects or derivitives
	char *path;
	long lastoff;

protected:
	FileDesc *idxfd;
	FileDesc *datfd;
	void doSetText(const char *key, const char *buf, long len = -1);
	void doLinkEntry(const char *destkey, const char *srckey);
public:
	static void prepText(SWBuf &buf);
	static char nl;
	RawStr(const char *ipath, int fileMode = -1);
	virtual ~RawStr();
	void getIDXBuf(long ioffset, char **buf);
	void getIDXBufDat(long ioffset, char **buf);
	signed char findOffset(const char *key, long *start, unsigned short *size, long away = 0, long *idxoff = 0);
	void readText(long start, unsigned short *size, char **idxbuf, SWBuf &buf);
	static signed char createModule(const char *path);
};

SWORD_NAMESPACE_END
#endif
