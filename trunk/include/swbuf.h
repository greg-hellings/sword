/******************************************************************************
*  swbuf.h  - code for SWBuf used as a transport and utility for data buffers
*
* $Id: swbuf.h,v 1.29 2004/02/29 23:26:17 joachim Exp $
*
* Copyright 2003 CrossWire Bible Society (http://www.crosswire.org)
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

#ifndef SWBUF_H
#define SWBUF_H

#include <defs.h>
#include <stdlib.h>
#include <string.h>

SWORD_NAMESPACE_START


#define JUNKBUFSIZE 8191

/**
* This class is used as a transport and utility for data buffers.
*/
class SWDLLEXPORT SWBuf {
	char *buf;
	char *end;
	char *endAlloc;
	char fillByte;
	unsigned long allocSize;
	static char *nullStr;
	static char junkBuf[JUNKBUFSIZE];

	inline void assureMore(signed long pastEnd) {
		if (endAlloc-end < pastEnd) {
			long newsize = (end-buf)+pastEnd;
			allocSize = newsize + 16;
			long size = (end - buf);
			buf = (char *)((buf) ? realloc(buf, allocSize) : malloc(allocSize));
			end = (buf + size);
			*end = 0;
			endAlloc = buf + allocSize-1;
		}
	}
	inline void assureSize(unsigned long newsize) {
		if (newsize > allocSize) {
			allocSize = newsize + 16;
			long size = (end - buf);
			buf = (char *)((buf) ? realloc(buf, allocSize) : malloc(allocSize));
			end = (buf + size);
			*end = 0;
			endAlloc = buf + allocSize-1;
		}
	}

	void init(unsigned long initSize);

public:
	/**
	* SWBuf Constructor - Creates an empty SWBuf object or an SWBuf initialized
 	* 		to a value from a const char *
 	*
 	*/
	SWBuf(const char *initVal = 0, unsigned long initSize = 0);
//	SWBuf(unsigned long initSize);

	/**
	* SWBuf Constructor - Creates an SWBuf initialized
	* 		to a value from a char
	*
	*/
	SWBuf(char initVal, unsigned long initSize = 0);

	/**
	* SWBuf Constructor - Creates an SWBuf initialized
	* 		to a value from another SWBuf
	*
	*/
	SWBuf(const SWBuf &other, unsigned long initSize = 0);

	inline void setFillByte(char ch) { fillByte = ch; }
	inline char getFillByte() { return fillByte; }

  /**
	* SWBuf Destructor - Cleans up instance of SWBuf
 	*/
	virtual ~SWBuf();

	/**
	* @return a pointer to the buffer content (null-terminated string)
	*/
	inline const char *c_str() const{ return buf; }

	/**
	*	@param pos The position of the requested character.
	* @return The character at the specified position
	*/
	inline char &charAt(unsigned long pos) { return ((pos <= (unsigned long)(end - buf)) ? buf[pos] : nullStr[0]); }
//	inline char &charAt(unsigned int pos) { return ((buf+pos)<=end) ? buf[pos] : nullStr[0]; }

	/** 
	* size() and length() return only the number of characters of the string.
	* Add one for the following null and one for each char to be appended!
	*/
	inline unsigned long size() const { return length(); }

	/**
	* size() and length() return only the number of characters of the string.
	* Add one for the following null and one for each char to be appended!
	*/
	inline unsigned long length() const { return end - buf; }

	/**
 	* SWBuf::set - sets this buf to a new value.
	* If the allocated memory is bigger than the new string, it will NOT be resized.
	* @param newVal the value to set this buffer to. 
 	*/
	void set(const char *newVal);

	/**
 	* SWBuf::set - sets this buf to a new value
	* If the allocated memory is bigger than the new string, it will NOT be resized.
	* @param newVal the value to set this buffer to. 
 	*/
	void set(const SWBuf &newVal);

	/**
 	* SWBuf::setSize - Size this buffer to a specific length.
	* @param len The new size of the buffer. One byte for the null will be added.
 	*/
	void setSize(unsigned long len);
	inline void resize(unsigned long len) { setSize(len); }

	/**
 	* SWBuf::append - appends a value to the current value of this SWBuf.
	* If the allocated memory is not enough, it will be resized accordingly.
	* @param str Append this.
	* @param max Append only max chars.
 	*/
	void append(const char *str, long max = -1);

	/**
	* SWBuf::append - appends a value to the current value of this SWBuf
	* If the allocated memory is not enough, it will be resized accordingly.
	* @param str Append this.
	* @param max Append only max chars.
	*/
	inline void append(const SWBuf &str, long max = -1) { append(str.c_str(), max); }

	/**
	* SWBuf::append - appends a value to the current value of this SWBuf
	* If the allocated memory is not enough, it will be resized accordingly.
	* @param ch Append this.
	*/
	inline void append(char ch) {
		assureMore(1);
		*end++ = ch;
		*end = 0;
	}

	/**
	* SWBuf::appendFormatted - appends formatted strings to the current value of this SWBuf
	* WARNING: This function can only write at most
	* JUNKBUFSIZE to the string per call.
	* @param format The format string. Same syntax as printf, for example.
	* @param ... Add all arguments here.
 	*/
	void appendFormatted(const char *format, ...);
	
	/** 
	* SWBuf::insert - inserts the given string at position into this string
	* @param pos The position where to insert. pos=0 inserts at the beginning, pos=1 after the first char, etc. Using pos=length() is the same as calling append(s)
	*/
	void insert(const unsigned long pos, const char* str, const signed long max = -1 );
	void insert(const unsigned long pos, const SWBuf &str, const signed long max = -1 ) {
		insert(pos, str.c_str(), max);
	};
	void insert(const unsigned long pos, const char c) {
		insert(pos, SWBuf(c));
	}
	
	inline char *getRawData() { return buf; }	// be careful!  Probably setSize needs to be called in conjunction before and maybe after

	inline operator const char *() const { return c_str(); }
	inline char &operator[](unsigned long pos) { return charAt(pos); }
	inline char &operator[](long pos) { return charAt((unsigned long)pos); }
	inline char &operator[](unsigned int pos) { return charAt((unsigned long)pos); }
	inline char &operator[](int pos) { return charAt((unsigned long)pos); }
	inline SWBuf &operator =(const char *newVal) { set(newVal); return *this; }
	inline SWBuf &operator =(const SWBuf &other) { set(other); return *this; }
	inline SWBuf &operator +=(const char *str) { append(str); return *this; }
	inline SWBuf &operator +=(char ch) { append(ch); return *this; }
	inline SWBuf &operator -=(unsigned long len) { setSize(length()-len); return *this; }
	inline SWBuf &operator --(int) { operator -=(1); return *this; }

	inline SWBuf &operator <<(int n) { n = (n<length())?n:(length()-1); memmove(buf, buf+n, length()-n); (*this)-=n; return *this; }
	inline SWBuf operator +(const SWBuf &other) const {
		SWBuf retVal = buf;
		retVal += other;
		return retVal;
	}
	inline SWBuf operator +(char ch) const { return (*this) + SWBuf(ch); }

	inline int compare(const SWBuf &other) const { return strcmp(c_str(), other.c_str()); }
	inline bool operator ==(const SWBuf &other) const { return !compare(other); }
	inline bool operator !=(const SWBuf &other) const { return compare(other); }
	inline bool operator > (const SWBuf &other) const { return compare(other) > 0; }
	inline bool operator < (const SWBuf &other) const { return compare(other) < 0; }
	inline bool operator <=(const SWBuf &other) const { return compare(other) <= 0; }
	inline bool operator >=(const SWBuf &other) const { return compare(other) >= 0; }

	inline bool operator ==(const char *other) const { return !compare(other); }
	inline bool operator !=(const char *other) const { return compare(other); }
	inline bool operator > (const char *other) const { return compare(other) > 0; }
	inline bool operator < (const char *other) const { return compare(other) < 0; }
	inline bool operator <=(const char *other) const { return compare(other) <= 0; }
	inline bool operator >=(const char *other) const { return compare(other) >= 0; }
};



SWORD_NAMESPACE_END
#endif
