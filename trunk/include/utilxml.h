/******************************************************************************
 *  utilxml.h   - definition of class that deal with xml constructs 
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

#ifndef UTILXML_H
#define UTILXML_H

#include <defs.h>
#include <swbuf.h>
#include <list>
#include <map>

SWORD_NAMESPACE_START

typedef std::map<SWBuf, SWBuf> StringPairMap;
typedef std::list<SWBuf> StringList;

/** Simple XML helper class.
*/
class SWDLLEXPORT XMLTag {
private:
	mutable char *buf;
	char *name;
	mutable bool parsed;
	mutable bool empty;
	mutable bool endTag;
	mutable StringPairMap attributes;
	mutable SWBuf junkBuf;
	
	void parse() const;
	const char *getPart(const char *buf, int partNum = 0, char partSplit = '|') const;
	static const char *nullstr;
	
public:
	XMLTag(const char *tagString = 0);
	~XMLTag();

	void setText(const char *tagString);
	inline const char *getName() const { return (name)?name:nullstr; }

	inline bool isEmpty() const {
		if (!parsed)
			parse();

		return empty;
	}
	inline void setEmpty(bool value) {
		if (!parsed)
			parse();
		empty = value;
		if (value)
			endTag = false;
	}

	inline bool isEndTag() const { return endTag; }

	const StringList getAttributeNames() const;
	int getAttributePartCount(const char *attribName, char partSplit = '|') const;
	const char *getAttribute(const char *attribName, int partNum = -1, char partSplit = '|') const;
	const char *setAttribute(const char *attribName, const char *attribValue);
	const char *toString() const;
	inline operator const char *() const { return toString(); }
	inline XMLTag & operator =(const char *tagString) { setText(tagString); return *this; }
	inline XMLTag & operator =(const XMLTag &other) { setText(other.toString()); return *this; }
};

SWORD_NAMESPACE_END
#endif

