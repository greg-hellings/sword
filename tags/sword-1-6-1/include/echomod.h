/******************************************************************************
 *  echomod.h  - code for class 'EchoMod' - a test module that just echo back
 *		 text of key.
 *
 * $Id$
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

#ifndef ECHOMOD_H
#define ECHOMOD_H

#include <swtext.h>
#include <defs.h>


SWORD_NAMESPACE_START

class SWDLLEXPORT EchoMod : public SWText
{
public:
	EchoMod();
	virtual ~EchoMod();
	virtual SWBuf &getRawEntryBuf();
};

SWORD_NAMESPACE_END
#endif
