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

#ifndef SCSUUTF8_H
#define SCSUUTF8_H

#include <swfilter.h>

#include <defs.h>

  /** This filter converts SCSU compressed (encoded) text to UTF-8
  */
class SWDLLEXPORT SCSUUTF8:public SWFilter {
 private:
  unsigned char* UTF8Output(unsigned long, unsigned char* text);
  
  unsigned long c, d;
  

 public:
  SCSUUTF8();
  virtual char ProcessText (char *text, int maxlen, const SWKey *key, const SWModule * = 0);
};

#endif
