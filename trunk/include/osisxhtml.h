/******************************************************************************
 *
 * osisxhtml.h
 *
 * Copyright 2011 CrossWire Bible Society (http://www.crosswire.org)
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

#ifndef OSISXHTML_H
#define OSISXHTML_H

#include <swbasicfilter.h>

SWORD_NAMESPACE_START

/** this filter converts OSIS text to classed XHTML
 */
class SWDLLEXPORT OSISXHTML : public SWBasicFilter {
private:
	bool morphFirst;
protected:
	// used by derived classes so we have it in the header
	class TagStacks;
	class SWDLLEXPORT MyUserData : public BasicFilterUserData {
	public:
		bool osisQToTick;
		bool inBold;	// TODO: obsolete. left for binary compat for 1.6.x
		bool inXRefNote;
		bool BiblicalText;
		int suspendLevel;
		SWBuf wordsOfChristStart;
		SWBuf wordsOfChristEnd;
                TagStacks *tagStacks;	// TODO: modified to wrap all TagStacks necessary for this filter until 1.7.x
//                TagStack *hiStack;	// TODO: commented out for binary compat for 1.6.x	 wrapped in tagStacks until 1.7.x
		SWBuf lastTransChange;
		SWBuf w;
		SWBuf fn;
		SWBuf version;
		MyUserData(const SWModule *module, const SWKey *key);
		~MyUserData();
	};
	virtual BasicFilterUserData *createUserData(const SWModule *module, const SWKey *key) {
		return new MyUserData(module, key);
	}
	virtual bool handleToken(SWBuf &buf, const char *token, BasicFilterUserData *userData);
public:
	OSISXHTML();
	void setMorphFirst(bool val = true) { morphFirst = val; }
	virtual const char *getHeader() const;
};

SWORD_NAMESPACE_END
#endif
