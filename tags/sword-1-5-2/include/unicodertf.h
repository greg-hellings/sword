/*
 *
 * $Id: unicodertf.h,v 1.2 2001/06/15 01:07:46 chrislit Exp $
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

#ifndef UNICODERTF_H
#define UNICODERTF_H

#include <swfilter.h>

#include <defs.h>

  /** This filter converts UTF-8 text into RTF Unicode tags
  */
class SWDLLEXPORT UnicodeRTF:public SWFilter {
public:
  UnicodeRTF();
  virtual char ProcessText (char *text, int maxlen, const SWKey *key);
};

#endif