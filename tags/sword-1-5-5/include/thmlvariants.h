/*
 *
 * Copyright 2001 CrossWire Bible Society (http://www.crosswire.org)
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

#ifndef THMLVARIANTS_H
#define THMLVARIANTS_H

#include <swfilter.h>
#include <swmodule.h>

#include <defs.h>

SWORD_NAMESPACE_START

  /** This Filter shows/hides textual variants
  */
class SWDLLEXPORT ThMLVariants : public SWFilter
{
  char option;

  static const char primary[];
  static const char secondary[];
  static const char all[];

  static const char optName[];
  static const char optTip[];
  OptionsList options;

 public:
  ThMLVariants ();
  virtual ~ ThMLVariants ();
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
