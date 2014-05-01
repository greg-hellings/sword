/******************************************************************************
 *
 *  swld.h -	code for base class 'SWLD'.  SWLD is the basis for all
 *		types of Lexicon and Dictionary modules (hence the 'LD').
 *
 * $Id$
 *
 * Copyright 1997-2013 CrossWire Bible Society (http://www.crosswire.org)
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

#ifndef SWLD_H
#define SWLD_H

#include <swmodule.h>

#include <defs.h>

SWORD_NAMESPACE_START

  /** the basis for all types of Lexicon and
  * Dictionary modules (hence the 'LD').
  */
class SWDLLEXPORT SWLD : public SWModule {
protected:
	mutable char *entkeytxt;
	bool strongsPadding;

public:

	/** Initializes data for instance of SWLD
	*/
	SWLD(const char *imodname = 0, const char *imoddesc = 0,
			SWDisplay * idisp = 0, SWTextEncoding encoding = ENC_UNKNOWN,
			SWTextDirection dir = DIRECTION_LTR,
			SWTextMarkup markup = FMT_UNKNOWN, const char* ilang = 0, bool strongsPadding = true);
	
	virtual ~SWLD();
	virtual SWKey *createKey() const;

	/** Sets/gets module KeyText, getting from saved text if key is persistent
	*
	* @param ikeytext value which to set keytext;
	*  [0] - only get
	* @return pointer to keytext
	*/
	virtual const char *getKeyText() const;
	virtual void setPosition(SW_POSITION pos);


	virtual long getEntryCount() const = 0;
	virtual long getEntryForKey(const char *key) const = 0;
	virtual char *getKeyForEntry(long entry) const = 0;
	
	virtual bool hasEntry(const SWKey *k) const;


	/** Pads a key if (it-1) is 100% digits to 5 places allows for final to be alpha, e.g. '123B'
	*
	* @param[in,out] buffer to check and pad
	*/
	static void strongsPad(char *buffer);

	// OPERATORS -----------------------------------------------------------------
	
	SWMODULE_OPERATORS

};

SWORD_NAMESPACE_END
#endif
