/******************************************************************************
 *
 *  utf8arabicpoints.h -	SWFilter descendant to remove UTF-8 Arabic
 *				vowel points
 *
 * $Id$
 *
 * Copyright 2009-2013 CrossWire Bible Society (http://www.crosswire.org)
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

#ifndef UTF8ARABICPOINTS_H
#define UTF8ARABICPOINTS_H

#include <swoptfilter.h>

SWORD_NAMESPACE_START

/** This Filter shows/hides Arabic vowel points in UTF8 text
 */
class SWDLLEXPORT UTF8ArabicPoints : public SWOptionFilter {
public:
	UTF8ArabicPoints();
	virtual ~UTF8ArabicPoints();
	virtual char processText(SWBuf &text, const SWKey *key = 0, const SWModule *module = 0);
private:
	static char* UTF8ArabicPoints::next_mark(const char* from, int* mark_size);
};

SWORD_NAMESPACE_END
#endif
