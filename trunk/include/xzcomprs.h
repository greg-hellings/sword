/******************************************************************************
 *
 *  xzcomprs.h -	XzCompress, a driver class that provides xz (LZMA2)
 *			compression
 *
 * $Id$
 *
 * Copyright 2000-2014 CrossWire Bible Society (http://www.crosswire.org)
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

#ifndef XZCOMPRS_H
#define XZCOMPRS_H

#include <stdint.h>

#include <swcomprs.h>

#include <defs.h>

SWORD_NAMESPACE_START

class SWDLLEXPORT XzCompress : public SWCompress {

protected:
public:
	XzCompress();
	virtual ~XzCompress();

	virtual void Encode(void);
	virtual void Decode(void);
	virtual void setLevel(int l);
private:
	uint64_t memlimit; // memory usage limit during decompression
};

SWORD_NAMESPACE_END
#endif
