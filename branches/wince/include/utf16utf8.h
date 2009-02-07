/*
 *
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

#ifndef UTF16UTF8_H
#define UTF16UTF8_H

#include <swfilter.h>

#include <defs.h>

SWORD_NAMESPACE_START

  /** This filter converts UTF-16 encoded text to UTF-8
  */
class SWDLLEXPORT UTF16UTF8:public SWFilter {
public:
  UTF16UTF8();
  virtual char ProcessText (char *text, int maxlen, const SWKey *key, const SWModule * = 0);
};

SWORD_NAMESPACE_END
#endif