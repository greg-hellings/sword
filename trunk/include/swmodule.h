/******************************************************************************
 *  swmodule.h  - code for base class 'module'.  Module is the basis for all
 *		  types of modules (e.g. texts, commentaries, maps, lexicons,
 *		  etc.)
 *
 * $Id: swmodule.h,v 1.8 2000/08/19 03:36:46 scribe Exp $
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

#ifndef SWMODULE_H
#define SWMODULE_H

#include <swdisp.h>
#include <swkey.h>
#include <listkey.h>
#include <swfilter.h>
#include <list>

using namespace std;

typedef list<SWFilter *> FilterList;

class SWModule {
protected:
	char error;
	SWKey *key;
	ListKey listkey;
	char *modname;
	char *moddesc;
	char *modtype;
	SWDisplay *disp;
	static SWDisplay rawdisp;
	char *entrybuf;
	FilterList stripfilters;	// executed to remove all markup (for searches)
	FilterList rawfilters;	// executed immediately upon fileread
	FilterList renderfilters;// executed to format for display
	FilterList optionfilters;// executed to change markup to user prefs
	bool render;

public:
	static void nullPercent(char percent, void *userData);
	bool terminateSearch;	// for ending a search from another thread
	SWModule(const char *imodname = 0, const char *imoddesc = 0, SWDisplay *idisp = 0, char *imodtype = 0);
	virtual ~SWModule();
	virtual char Error();
	virtual char SetKey(const SWKey &ikey);
	virtual SWKey &Key() const { return *key; }
	virtual char Key(const SWKey &ikey) { return SetKey(ikey); }
	virtual const char *KeyText(char *imodtype = 0);
	virtual char Display();
	virtual SWDisplay *Disp(SWDisplay *idisp = 0);
	virtual char *Name(char *imodname = 0);
	virtual char *Description(char *imoddesc = 0);
	virtual char *Type(char *imodtype = 0);

	// search methods
	virtual ListKey &Search(const char *istr, int searchType = 0, int flags = 0, SWKey *scope = 0, bool *justCheckIfSupported = 0, void (*percent)(char, void *) = &nullPercent, void *percentUserData = 0);
	virtual char createSearchFramework() { return 0; } // special search framework
	virtual bool hasSearchFramework() { return false; } // special search framework
	virtual bool isSearchOptimallySupported(const char *istr, int searchType, int flags, SWKey *scope) {
		bool retVal = false;
		Search(istr, searchType, flags, scope, &retVal);
		return retVal;
	}

	virtual SWKey *CreateKey();

	virtual operator char*() = 0;
	virtual operator SWKey&() { return *key; }
	virtual operator SWKey*() { return key; }

	virtual SWModule &operator <<(const char *) { return *this; }  // Modify current module entry
	virtual SWModule &operator <<(const SWKey *) { return *this; } // Link current module entry to other module entry
	virtual void Delete() {} // Delete current module entry

	virtual SWModule &operator -=(int decrement);
	virtual SWModule &operator +=(int increment);
	virtual SWModule &operator ++(int) { return *this += 1; }
	virtual SWModule &operator --(int) { return *this -= 1; }
	virtual SWModule &operator =(POSITION);
	virtual SWModule &AddRenderFilter(SWFilter *newfilter) { renderfilters.push_back(newfilter); return *this;}
	virtual SWModule &AddStripFilter(SWFilter *newfilter) { stripfilters.push_back(newfilter); return *this;}
	virtual SWModule &AddRawFilter(SWFilter *newfilter) { rawfilters.push_back(newfilter); return *this;}
	virtual SWModule &AddOptionFilter(SWFilter *newfilter) { optionfilters.push_back(newfilter); return *this;}
	virtual const char *StripText(char *text = 0, int len = -1);
	virtual const char *RenderText(char *text = 0, int len = -1);
	virtual const char *StripText(SWKey *ikey);
	virtual const char *RenderText(SWKey *ikey);
	
};


#endif
