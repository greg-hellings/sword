/******************************************************************************
*  swbuf.cpp  - code for SWBuf used as a transport and utility for data buffers
*
* $Id: swbuf.cpp,v 1.19 2004/06/10 16:02:14 mgruner Exp $
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

#include <swbuf.h>

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

SWORD_NAMESPACE_START

char *SWBuf::nullStr = "";
char SWBuf::junkBuf[JUNKBUFSIZE];

/******************************************************************************
* SWBuf Constructor - Creates an empty SWBuf object or an SWBuf initialized
* 		to a value from a const char *
*
*/
SWBuf::SWBuf(const char *initVal, unsigned long initSize) {
	init(initSize);
	set(initVal);
}

/******************************************************************************
* SWBuf Constructor - Creates an SWBuf initialized
* 		to a value from another SWBuf
*
*/
SWBuf::SWBuf(const SWBuf &other, unsigned long initSize) {
	init(initSize);
	set(other);
}

/******************************************************************************
* SWBuf Constructor - Creates an SWBuf initialized
* 		to a value from a char
*
*/
SWBuf::SWBuf(char initVal, unsigned long initSize) {
	init(initSize);

	allocSize = 15;
	buf = (char *)calloc(allocSize, 1);
	*buf = initVal;
	end = buf+1;
	endAlloc = buf + allocSize-1;
}

/*
SWBuf::SWBuf(unsigned long initSize) {
	init(initSize);
	set((const char *)0);
}
*/


void SWBuf::init(unsigned long initSize) {
	fillByte = ' ';
	allocSize = 0;
	endAlloc = 0;
	buf = 0;
	end = 0;
	if (initSize)
		assureSize(initSize);
}

/******************************************************************************
* SWBuf Destructor - Cleans up instance of SWBuf
*/
SWBuf::~SWBuf() {
	if (buf)
		free(buf);
}

/******************************************************************************
* SWBuf::set - sets this buf to a new value
*/
void SWBuf::set(const char *newVal) {
	if (newVal) {
		unsigned long len = strlen(newVal) + 1;
		assureSize(len);
		memcpy(buf, newVal, len);
		end = buf + (len - 1);
	}
	else {
		assureSize(1);
		end = buf;
		*end = 0;
	}
}


/******************************************************************************
* SWBuf::set - sets this buf to a new value
*/
void SWBuf::set(const SWBuf &newVal) {
	unsigned long len = newVal.length() + 1;
	assureSize(len);
	memcpy(buf, newVal.c_str(), len);
	end = buf + (len-1);
}

/******************************************************************************
* SWBuf::setFormatted - sets this buf to a formatted string
* WARNING: This function can only write at most
* JUNKBUFSIZE to the string per call.
*/
void SWBuf::setFormatted(const char *format, ...) {
	va_list argptr;

	va_start(argptr, format);
	int len = vsprintf(junkBuf, format, argptr)+1;
	va_end(argptr);
	assureSize(len);
	va_start(argptr, format);
	end = vsprintf(buf, format, argptr) + buf;
	va_end(argptr);
}

/******************************************************************************
* SWBuf::append - appends a value to the current value of this SWBuf
*/
void SWBuf::append(const char *str, const long max) {
	if (!str) //A null string was passed
		return;
	//make sure we only copy strlen(str) bytes if max is larger than strlen(str) is
	unsigned long str_len = strlen( str );
	unsigned long len = (max > -1) ? ((max <= str_len) ? max : str_len) : str_len;
	assureMore(++len);
	memcpy(end, str, len-1);
	end += (len-1);
	*end = 0;
}

/******************************************************************************
* SWBuf::setSize - Size this buffer to a specific length
*/
void SWBuf::setSize(unsigned long len) {
	assureSize(len+1);
	if ((end - buf) < len)
		memset(end, fillByte, len - (end-buf));
	end = buf + len;
	*end = 0;
}

/******************************************************************************
* SWBuf::appendFormatted - appends formatted strings to the current value of this SWBuf
* WARNING: This function can only write at most
* JUNKBUFSIZE to the string per call.
*/
void SWBuf::appendFormatted(const char *format, ...) {
	va_list argptr;

	va_start(argptr, format);
	int len = vsprintf(junkBuf, format, argptr)+1;
	va_end(argptr);
	assureMore(len);
	va_start(argptr, format);
	end += vsprintf(end, format, argptr);
	va_end(argptr);
}

void SWBuf::insert(const unsigned long pos, const char* str, const signed long max) {
	if (!str) //A null string was passed
		return;

	const int len = (max > -1) ? max : strlen(str);

	if (!len || (pos > length())) //nothing to do, return
		return;
	
	// pos==length(), so we can call append in this case
	if (pos == length()) { //append is more efficient
		append(str, max);
		return;
	}
	
	assureMore( len );
	
	memmove(buf + pos + len, buf + pos, (end - buf) - pos); //make a gap of "len" bytes
	memcpy(buf+pos, str, len);
	
	end += len;
	*end = 0;
}

SWORD_NAMESPACE_END
