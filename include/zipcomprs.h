/******************************************************************************
 *  swcomprs.h   - definition of Class SWCompress used for data compression
 *
 * $Id: zipcomprs.h,v 1.2 2001/02/08 09:20:48 chrislit Exp $
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

#ifndef ZIPCOMPRS_H
#define ZIPCOMPRS_H

#include <swcomprs.h>

#include <defs.h>

class SWDLLEXPORT ZipCompress : public SWCompress {
protected:
public:
	ZipCompress();
	virtual ~ZipCompress();
	virtual void Encode(void);
	virtual void Decode(void);
};

#endif
