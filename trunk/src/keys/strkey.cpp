/******************************************************************************
 *  StrKey.cpp - code for class 'StrKey'- a standard string key class (used
 *				for modules that index on single strings (eg. cities,
 *				names, words, etc.)
 */

#include <swmacs.h>
#include <utilfuns.h>
#include <strkey.h>
#include <string.h>
#include <stdio.h>


static const char *classes[] = {"StrKey", "SWKey", "SWObjects"};
SWClass StrKey::classdef(classes);

/******************************************************************************
 * StrKey Constructor - initializes instance of StrKey
 *
 * ENT:	ikey - text key (word, city, name, etc.)
 */

StrKey::StrKey(const char *ikey) : SWKey(ikey)
{
	init();
}


void StrKey::init() {
	myclass = &classdef;
}


/******************************************************************************
 * StrKey Destructor - cleans up instance of StrKey
 *
 * ENT:	ikey - text key
 */

StrKey::~StrKey()
{
}
