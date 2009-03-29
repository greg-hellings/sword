/******************************************************************************
 *  swversion.h   - definition of class SWVersion used to compare version info
 *
 * $Id: swversion.h,v 1.12 2003/07/12 21:22:41 dglassey Exp $
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

#ifndef SWORDVER
#define SWORDVER "1.5.6"
#endif

#ifndef SWVERSION_H
#define SWVERSION_H

#include <defs.h>
SWORD_NAMESPACE_START

/** A basic tool class to handle program version numbers.
*/
class SWVersion {
	public:
	/** The different version subnumbers.
	*/
	int major, minor, minor2, minor3;
	/**The constructor.
	* @param version Version string to be parsed.
	*/
	SWVersion(const char *version = "0.0");
	/** Compare 2 Versions with each other.
	* @param vi Version number to compare with.
	* @return >0:this>vi; 0:this==vi; <0:this<vi
	*/
	int compare(const SWVersion &vi) const;
	/** @return The parsed version number text.
	*/
	const char *getText() const;
	/** @return The parsed version number text.
	*/
	operator const char *() const { return getText(); }
	bool operator>(const SWVersion &vi) const {return (compare(vi) > 0);}
	bool operator<(const SWVersion &vi) const {return (compare(vi) < 0);}
	bool operator==(const SWVersion &vi) const {return (compare(vi) == 0);}

	/** Current sword library version.
	* Use this to check (e.g. at compile time) if the
	* version of the sword lib is recent enough for your program.
	*/
	static SWVersion currentVersion;
};

SWORD_NAMESPACE_END
#endif
