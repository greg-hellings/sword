// Include only if your UNIX compiler does not include stricmp but does include strcasecmp
/*
 *
 * $Id: unixstr.h,v 1.4 2003/06/27 01:41:07 scribe Exp $
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

#ifndef UNIXSTR_H
#define UNIXSTR_H
#include <defs.h>

SWORD_NAMESPACE_START
int stricmp (const char *s1, const char *s2);
SWORD_NAMESPACE_END

#endif