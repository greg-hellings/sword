/******************************************************************************
 *  hrefcom.cpp - code for class 'HREFCom'- a module that produces HTML HREFs
 *			pointing to actual text desired.  Uses standard
 *			files:	ot and nt using indexs ??.bks ??.cps ??.vss
 */


#include <ctype.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef __GNUC__
#include <io.h>
#else
#include <unistd.h>
#endif

#include <string.h>
#include <utilfuns.h>
#include <rawverse.h>
#include <hrefcom.h>

SWORD_NAMESPACE_START

 /******************************************************************************
 * HREFCom Constructor - Initializes data for instance of HREFCom
 *
 * ENT:	iname - Internal name for module
 *	iprefix - string to prepend to each HREF (e.g. "file://mods/com/jfb/")
 *	idesc - Name to display to user for module
 *	idisp	 - Display object to use for displaying
 */

HREFCom::HREFCom(const char *ipath, const char *iprefix, const char *iname, const char *idesc, SWDisplay *idisp) : RawVerse(ipath), SWCom(iname, idesc, idisp)
{
	prefix   = 0;
	stdstr(&prefix, iprefix);
}


/******************************************************************************
 * HREFCom Destructor - Cleans up instance of HREFCom
 */

HREFCom::~HREFCom()
{
	if (prefix)
		delete [] prefix;
}


/******************************************************************************
 * HREFCom::operator char *	- Returns the correct verse when char * cast
 *					is requested
 *
 * RET: string buffer with verse
 */

SWBuf &HREFCom::getRawEntryBuf() {
	long  start;
	unsigned short size;
	VerseKey *key = 0;

#ifndef _WIN32_WCE
	try {
#endif
		key = SWDYNAMIC_CAST(VerseKey, this->key);
#ifndef _WIN32_WCE
	}
	catch ( ... ) {}
#endif
	if (!key)
		key = new VerseKey(this->key);

	findOffset(key->Testament(), key->Index(), &start, &size);
	entrySize = size;        // support getEntrySize call

	SWBuf tmpbuf;

	readText(key->Testament(), start, size, tmpbuf);
	entryBuf = prefix;
	entryBuf += tmpbuf.c_str();
	prepText(entryBuf);

	if (key != this->key)
		delete key;

	return entryBuf;
}

SWORD_NAMESPACE_END
