/*
 *
 * $Id: gbfstrongs.h,v 1.9 2002/10/01 19:52:40 dglassey Exp $
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

#ifndef GBFSTRONGS_H
#define GBFSTRONGS_H

#include <swfilter.h>

#include <defs.h>

SWORD_NAMESPACE_START

  /** This Filter shows/hides strong's numbers in a GBF text
  */
class SWDLLEXPORT GBFStrongs:public SWFilter
{
  bool option;
  static const char on[];
  static const char off[];
  static const char optName[];
  static const char optTip[];
  OptionsList options;
public:
    GBFStrongs ();
    virtual ~ GBFStrongs ();
  virtual char ProcessText (char *text, int maxlen, const SWKey * key, const SWModule * = 0);
  virtual const char *getOptionName ()
  {
    return optName;
  }
  virtual const char *getOptionTip ()
  {
    return optTip;
  }
  virtual void setOptionValue (const char *ival);
  virtual const char *getOptionValue ();
  virtual OptionsList getOptionValues ()
  {
    return options;
  }
};

SWORD_NAMESPACE_END
#endif
