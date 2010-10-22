/******************************************************************************
 *  rawld.cpp - code for class 'RawLD'- a module that reads raw lexicon and
 *		dictionary files: *.dat *.idx
 *
 * Copyright 2009 CrossWire Bible Society (http://www.crosswire.org)
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

#include <fcntl.h>

#include <utilstr.h>
#include <zstr.h>
#include <zld.h>
#include <filemgr.h>

#include <stdio.h>

SWORD_NAMESPACE_START

 /******************************************************************************
 * RawLD Constructor - Initializes data for instance of RawLD
 *
 * ENT:	ipath	- path and filename of files (no extension)
 *		iname	- Internal name for module
 *		idesc	- Name to display to user for module
 *		idisp	- Display object to use for displaying
 */

zLD::zLD(const char *ipath, const char *iname, const char *idesc, long blockCount, SWCompress *icomp, SWDisplay *idisp, SWTextEncoding enc, SWTextDirection dir, SWTextMarkup mark, const char* ilang) : zStr(ipath, -1, blockCount, icomp), SWLD(iname, idesc, idisp, enc, dir, mark, ilang) {

}


/******************************************************************************
 * RawLD Destructor - Cleans up instance of RawLD
 */

zLD::~zLD() {
	flushCache();
}


bool zLD::isWritable() {
	return ((idxfd->getFd() > 0) && ((idxfd->mode & FileMgr::RDWR) == FileMgr::RDWR));
}


/******************************************************************************
 * zLD::getEntry	- Looks up entry from data file.  'Snaps' to closest
 *				entry and sets 'entrybuf'.
 *
 * ENT: away - number of entries offset from key (default = 0)
 *
 * RET: error status
 */

char zLD::getEntry(long away) {
	char *idxbuf = 0;
	char *ebuf = 0;
	char retval = 0;
	long index;
	unsigned long size;
	char *buf = new char [ strlen(*key) + 6 ];
	strcpy(buf, *key);

	strongsPad(buf);

	entryBuf = "";
	if (!(retval = findKeyIndex(buf, &index, away))) {
		getText(index, &idxbuf, &ebuf);
		size = strlen(ebuf) + 1;
		entryBuf = ebuf;

		rawFilter(entryBuf, key);

		entrySize = size;        // support getEntrySize call
		if (!key->Persist())			// If we have our own key
			*key = idxbuf;				// reset it to entry index buffer

		stdstr(&entkeytxt, idxbuf);	// set entry key text that module 'snapped' to.
		free(idxbuf);
		free(ebuf);
	}
		
	delete [] buf;
	return retval;
}


/******************************************************************************
 * zLD::getRawEntry	- Returns the correct entry when char * cast
 *							is requested
 *
 * RET: string buffer with entry
 */

SWBuf &zLD::getRawEntryBuf() {
	if (!getEntry() /*&& !isUnicode()*/) {
		prepText(entryBuf);
	}

	return entryBuf;
}


/******************************************************************************
 * zLD::increment	- Increments module key a number of entries
 *
 * ENT:	increment	- Number of entries to jump forward
 *
 * RET: *this
 */

void zLD::increment(int steps) {
	char tmperror;

	if (key->isTraversable()) {
		*key += steps;
		error = key->Error();
		steps = 0;
	}
	
	tmperror = (getEntry(steps)) ? KEYERR_OUTOFBOUNDS : 0;
	error = (error)?error:tmperror;
	*key = entkeytxt;
}


void zLD::setEntry(const char *inbuf, long len) {
	setText(*key, inbuf, len);
}


void zLD::linkEntry(const SWKey *inkey) {
	zStr::linkEntry(*key, *inkey);
}


/******************************************************************************
 * RawFiles::deleteEntry	- deletes this entry
 *
 * RET: *this
 */

void zLD::deleteEntry() {
	setText(*key, "");
}


long zLD::getEntryCount() const
{
	if (idxfd < 0) return 0;
	return idxfd->seek(0, SEEK_END) / IDXENTRYSIZE;
}


long zLD::getEntryForKey(const char* key) const
{
	long offset;
	char *buf = new char [ strlen(key) + 6 ];
	strcpy(buf, key);

	strongsPad(buf);
	
	findKeyIndex(buf, &offset);

	delete [] buf;

	return offset/IDXENTRYSIZE;
}


char *zLD::getKeyForEntry(long entry) const
{
	char *key = 0;
	getKeyFromIdxOffset(entry * IDXENTRYSIZE, &key);
	return key;
}


SWORD_NAMESPACE_END
