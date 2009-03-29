/******************************************************************************
 *  rawld.cpp - code for class 'RawLD'- a module that reads raw lexicon and
 *				dictionary files: *.dat *.idx
 */


#include <ctype.h>
#include <stdio.h>
#include <fcntl.h>

#include <utilstr.h>
#include <zstr.h>
#include <zld.h>
#include <filemgr.h>

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

}


bool zLD::isWritable() {
	return ((idxfd->getFd() > 0) && ((idxfd->mode & FileMgr::RDWR) == FileMgr::RDWR));
}


/******************************************************************************
 * zLD::strongsPad	- Pads a key if it is 100% digits to 5 places
 *
 * ENT: buf -	buffer to check and pad
 */

void zLD::strongsPad(char *buf) {
	char *check;
	int size = 0;
	int len = strlen(buf);
	char subLet = 0;
	bool bang = false;
	if ((len < 8) && (len > 0)) {
		for (check = buf; *(check+1); check++) {
			if (!isdigit(*check))
				break;
			else size++;
		}

		if (size && ((size == (len-1)) || (size == (len-2)))) {
			if (*check == '!') {
				bang = true;
				check++;
			}
			if (isalpha(*check)) {
				subLet = toupper(*check);
				*(check-(bang?1:0)) = 0;
			}
			sprintf(buf, "%.5d", atoi(buf));
			if (subLet) {
				check = buf+(strlen(buf));
				if (bang) {
					*check++ = '!';
				}
				*check++ = subLet;
				*check = 0;
			}
		}
	}
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

SWORD_NAMESPACE_END