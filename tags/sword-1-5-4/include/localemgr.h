/******************************************************************************
 *  localemgr.h   - definition of class LocaleMgr used to interact with
 *				registered locales for a sword installation
 *
 * $Id: localemgr.h,v 1.9 2002/06/19 09:24:44 scribe Exp $
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

#ifndef LOCALEMGR_H
#define LOCALEMGR_H

#include <string>
#include <map>
#include <list>
#include <swconfig.h>
#include <swlocale.h>

#include <defs.h>

using namespace std;

typedef map < string, SWLocale *, less < string > >LocaleMap;

/**
* The LocaleMgr class handles all the different locales of Sword.
* It provides functions to get a list of all available locales,
* to get the default locale name and to get it.
* The other functions are not interesting for frontend programmers.
*
* To get the default locale name use @see getDefaultLocaleName
* To set the default locale name use @see setDefaultLocaleName
* To get the locale for a language name use @see getLocale
* To get a list of availble locales use @see getAvailableLocales
*/
class SWDLLEXPORT LocaleMgr
{
private:
  void deleteLocales ();
  char *defaultLocaleName;

protected:
  LocaleMap locales;

public:
  /** Default constructor of  LocaleMgr
  * You do normally not need this constructor, use LocaleMgr::systemLocaleMgr instead.
  */
  LocaleMgr (const char *iConfigPath = 0);

  /**
  * Default destructor of LocaleMgr
  */
  virtual ~ LocaleMgr ();

  /** Get the locale connected with the name "name".
  *
  * @param name The name of the locale you want to have. For example use getLocale("de") to get the locale for the German language.
  * @return Returns the locale object if the locale with the name given as parameter was found. If it wasn't found return NULL.
  */
  virtual SWLocale *getLocale (const char *name);

  /** Get the list of available locales.
  *
  * @ret Returns a list of strings, which contains the names of the available locales.
  */
  virtual list < string > getAvailableLocales ();
  
  /** Returns translated text.
  * This function uses both parameters to return the translated version of the given text.
  *
  * @param The text to translate into the language given by the first parameter.
  * @param localeName The name of the locale Sword should use
  * @return Returns the translated text.
  */
  virtual const char *translate (const char *text, const char *localeName = 0);

  /** Get the default locale name. To set it use @see setDefaultLocaleName
  *
  * @ret Returns the default locale name
  */
  virtual const char *getDefaultLocaleName ();

  /** Set the new standard locale of Sword.
  *
  * @param name The name of the new default locale  
  */
  virtual void setDefaultLocaleName (const char *name);

  /** The LocaleMgr object used globally in the Sword world.
  * Do not create your own LocaleMgr, use this static object instead.
  */
  static LocaleMgr systemLocaleMgr;

  
  /** Augment this localmgr with all locale.conf files in a directory
  */
  virtual void loadConfigDir(const char *ipath);
  
};
#endif