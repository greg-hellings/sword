/******************************************************************************
 *  swmodule.cpp -code for base class 'module'.  Module is the basis for all
 *		  types of modules (e.g. texts, commentaries, maps, lexicons,
 *		  etc.)
 */

#include <string.h>
#include <swmodule.h>
#include <utilfuns.h>
#include <regex.h>	// GNU
#include <swfilter.h>
#include <versekey.h>	// KLUDGE for Search
#ifndef _MSC_VER
#include <iostream>
#endif

SWORD_NAMESPACE_START

SWDisplay SWModule::rawdisp;
void SWModule::nullPercent(char percent, void *percentUserData) {}

/******************************************************************************
 * SWModule Constructor - Initializes data for instance of SWModule
 *
 * ENT:	imodname - Internal name for module
 *	imoddesc - Name to display to user for module
 *	idisp	 - Display object to use for displaying
 *	imodtype - Type of Module (All modules will be displayed with
 *			others of same type under their modtype heading
 *	unicode  - if this module is unicode
 */

SWModule::SWModule(const char *imodname, const char *imoddesc, SWDisplay *idisp, char *imodtype, SWTextEncoding encoding, SWTextDirection direction, SWTextMarkup markup, const char* imodlang) {
	key       = CreateKey();
	entrybuf  = new char [1];
	*entrybuf = 0;
	config    = &ownConfig;
	entrybufallocsize = 0;
	modname   = 0;
	error     = 0;
	moddesc   = 0;
	modtype   = 0;
	modlang   = 0;
	this->encoding = encoding;
	this->direction = direction;
	this->markup  = markup;
	entrySize= -1;
	disp     = (idisp) ? idisp : &rawdisp;
	stdstr(&modname, imodname);
	stdstr(&moddesc, imoddesc);
	stdstr(&modtype, imodtype);
	stdstr(&modlang, imodlang);
	stripFilters = new FilterList();
	rawFilters = new FilterList();
	renderFilters = new FilterList();
	optionFilters = new FilterList();
	encodingFilters = new FilterList();
	skipConsecutiveLinks = true;
	procEntAttr = true;
}


/******************************************************************************
 * SWModule Destructor - Cleans up instance of SWModule
 */

SWModule::~SWModule()
{
	if (entrybuf)
		delete [] entrybuf;
	if (modname)
		delete [] modname;
	if (moddesc)
		delete [] moddesc;
	if (modtype)
		delete [] modtype;
	if (modlang)
		delete [] modlang;

	if (key) {
		if (!key->Persist())
			delete key;
	}

	stripFilters->clear();
     rawFilters->clear();
     renderFilters->clear();
     optionFilters->clear();
     encodingFilters->clear();
	entryAttributes.clear();

     delete stripFilters;
     delete rawFilters;
     delete renderFilters;
     delete optionFilters;
     delete encodingFilters;
}


/******************************************************************************
 * SWModule::CreateKey - Allocates a key of specific type for module
 *
 * RET:	pointer to allocated key
 */

SWKey *SWModule::CreateKey()
{
	return new SWKey();
}


/******************************************************************************
 * SWModule::Error - Gets and clears error status
 *
 * RET:	error status
 */

char SWModule::Error()
{
	char retval = error;

	error = 0;
	return retval;
}


/******************************************************************************
 * SWModule::Name - Sets/gets module name
 *
 * ENT:	imodname - value which to set modname
 *		[0] - only get
 *
 * RET:	pointer to modname
 */

char *SWModule::Name(const char *imodname)
{
	return stdstr(&modname, imodname);
}


/******************************************************************************
 * SWModule::Description - Sets/gets module description
 *
 * ENT:	imoddesc - value which to set moddesc
 *		[0] - only get
 *
 * RET:	pointer to moddesc
 */

char *SWModule::Description(const char *imoddesc)
{
	return stdstr(&moddesc, imoddesc);
}


/******************************************************************************
 * SWModule::Type - Sets/gets module type
 *
 * ENT:	imodtype - value which to set modtype
 *		[0] - only get
 *
 * RET:	pointer to modtype
 */

char *SWModule::Type(const char *imodtype)
{
	return stdstr(&modtype, imodtype);
}

/******************************************************************************
 * SWModule::Direction - Sets/gets module direction
 *
 * ENT:	newdir - value which to set direction
 *		[-1] - only get
 *
 * RET:	char direction
 */
char SWModule::Direction(signed char newdir) {
        if (newdir != -1)
                direction = newdir;
        return direction;
}

/******************************************************************************
 * SWModule::Encoding - Sets/gets module encoding
 *
 * ENT:	newdir - value which to set direction
 *		[-1] - only get
 *
 * RET:	char encoding
 */
char SWModule::Encoding(signed char newenc) {
        if (newenc != -1)
                encoding = newenc;
        return encoding;
}

/******************************************************************************
 * SWModule::Markup - Sets/gets module markup
 *
 * ENT:	newdir - value which to set direction
 *		[-1] - only get
 *
 * RET:	char markup
 */
char SWModule::Markup(signed char newmark) {
        if (newmark != -1)
                markup = newmark;
        return markup;
}


/******************************************************************************
 * SWModule::Lang - Sets/gets module language
 *
 * ENT:	imodlang - value which to set modlang
 *		[0] - only get
 *
 * RET:	pointer to modname
 */

char *SWModule::Lang(const char *imodlang)
{
	return stdstr(&modlang, imodlang);
}


/******************************************************************************
 * SWModule::Disp - Sets/gets display driver
 *
 * ENT:	idisp - value which to set disp
 *		[0] - only get
 *
 * RET:	pointer to disp
 */

SWDisplay *SWModule::Disp(SWDisplay *idisp)
{
	if (idisp)
		disp = idisp;

	return disp;
}


/******************************************************************************
 * SWModule::Display - Calls this modules display object and passes itself
 *
 * RET:	error status
 */

char SWModule::Display()
{
	disp->Display(*this);
	return 0;
}


/******************************************************************************
 * SWModule::getKey - Gets the key from this module that points to the position
 *			record
 *
 * RET:	key object
 */

SWKey *SWModule::getKey() const {
	return key;
}


/******************************************************************************
 * SWModule::setKey - Sets a key to this module for position to a particular
 *			record
 *
 * ENT:	ikey - key with which to set this module
 *
 * RET:	error status
 */

char SWModule::setKey(const SWKey *ikey) {
	SWKey *oldKey = 0;

	if (key) {
		if (!key->Persist())	// if we have our own copy
			oldKey = key;
	}

	if (!ikey->Persist()) {		// if we are to keep our own copy
		 key = CreateKey();
		*key = *ikey;
	}
	else	 key = (SWKey *)ikey;		// if we are to just point to an external key

	if (oldKey)
		delete oldKey;

	return 0;
}


/******************************************************************************
 * SWModule::setPosition(SW_POSITION)	- Positions this modules to an entry
 *
 * ENT:	p	- position (e.g. TOP, BOTTOM)
 *
 * RET: *this
 */

void SWModule::setPosition(SW_POSITION p) {
	*key = p;
	char saveError = key->Error();

	switch (p) {
	case POS_TOP:
		(*this)++;
		(*this)--;
		break;

	case POS_BOTTOM:
		(*this)--;
		(*this)++;
		break;
	}

	error = saveError;
}


/******************************************************************************
 * SWModule::increment	- Increments module key a number of entries
 *
 * ENT:	increment	- Number of entries to jump forward
 *
 * RET: *this
 */

void SWModule::increment(int steps) {
	(*key) += steps;
	error = key->Error();
}


/******************************************************************************
 * SWModule::decrement	- Decrements module key a number of entries
 *
 * ENT:	decrement	- Number of entries to jump backward
 *
 * RET: *this
 */

void SWModule::decrement(int steps) {
	(*key) -= steps;
	error = key->Error();
}


/******************************************************************************
 * SWModule::Search 	- Searches a module for a string
 *
 * ENT:	istr		- string for which to search
 * 	searchType	- type of search to perform
 *				>=0 - regex
 *				-1  - phrase
 *				-2  - multiword
 * 	flags		- options flags for search
 *	justCheckIfSupported	- if set, don't search, only tell if this
 *							function supports requested search.
 *
 * RET: listkey set to verses that contain istr
 */

ListKey &SWModule::Search(const char *istr, int searchType, int flags, SWKey *scope, bool *justCheckIfSupported, void (*percent)(char, void *), void *percentUserData)
{
	SWKey *savekey = 0;
	SWKey *searchkey = 0;
	regex_t preg;
	SWKey textkey;
	char **words = 0;
	char *wordBuf = 0;
	int wordCount = 0;
	const char *sres;
	terminateSearch = false;
	char perc = 1;
	bool savePEA = isProcessEntryAttributes();

	processEntryAttributes(false);
	listkey.ClearList();

	if (!key->Persist()) {
		savekey = CreateKey();
		*savekey = *key;
	}
	else	savekey = key;

	searchkey = (scope)?scope->clone():(key->Persist())?key->clone():0;
	if (searchkey) {
		searchkey->Persist(1);
		setKey(*searchkey);
	}

	(*percent)(perc, percentUserData);
	// MAJOR KLUDGE: VerseKey::Index still return index within testament.
	// 	VerseKey::NewIndex should be moved to Index and Index should be some
	// 	VerseKey specific name
	VerseKey *vkcheck = 0;
#ifndef _WIN32_WCE
	try {
#endif
		vkcheck = SWDYNAMIC_CAST(VerseKey, key);
#ifndef _WIN32_WCE
	}
	catch (...) {}
#endif
	// end MAJOR KLUDGE

	*this = BOTTOM;
	// fix below when we find out the bug
	long highIndex = (vkcheck)?32300/*vkcheck->NewIndex()*/:key->Index();
	if (!highIndex)
		highIndex = 1;		// avoid division by zero errors.
	*this = TOP;
	if (searchType >= 0) {
		flags |=searchType|REG_NOSUB|REG_EXTENDED;
		regcomp(&preg, istr, flags);
	}

	(*percent)(++perc, percentUserData);
	if (searchType == -2) {
		wordBuf = (char *)calloc(sizeof(char), strlen(istr) + 1);
		strcpy(wordBuf, istr);
		words = (char **)calloc(sizeof(char *), 10);
		int allocWords = 10;
		words[wordCount] = strtok(wordBuf, " ");
		while (words[wordCount]) {
			wordCount++;
			if (wordCount == allocWords) {
				allocWords+=10;
				words = (char **)realloc(words, sizeof(char *)*allocWords);
			}
			words[wordCount] = strtok(NULL, " ");
		}
	}

	perc = 5;
	(*percent)(perc, percentUserData);

	while (!Error() && !terminateSearch) {

	
		long mindex = 0;
		if (vkcheck)
			mindex = vkcheck->NewIndex();
		else mindex = key->Index();
		float per = (float)mindex / highIndex;
		per *= 93;
		per += 5;
		char newperc = (char)per;
//		char newperc = (char)(5+(93*(((float)((vkcheck)?vkcheck->NewIndex():key->Index()))/highIndex)));
		if (newperc > perc) {
			perc = newperc;
			(*percent)(perc, percentUserData);
		}
		else if (newperc < perc) {
#ifndef _MSC_VER
			std::cerr << "Serious error: new percentage complete is less than previous value\n";
			std::cerr << "using vk? " << ((vkcheck)?"yes":"no") << "\n";
			std::cerr << "index: " << ((vkcheck)?vkcheck->NewIndex():key->Index()) << "\n";
			std::cerr << "highIndex: " << highIndex << "\n";
			std::cerr << "newperc ==" << (int)newperc << "%" << "is smaller than\n";
			std::cerr << "perc == "  << (int )perc << "% \n";
#endif
		}
		if (searchType >= 0) {
			if (!regexec(&preg,  StripText(), 0, 0, 0)) {
				textkey = KeyText();
				listkey << textkey;
			}
		}
		else {
			if (searchType == -1) {
				sres = ((flags & REG_ICASE) == REG_ICASE) ? stristr(StripText(), istr) : strstr(StripText(), istr);
				if (sres) {
						textkey = KeyText();
						listkey << textkey;
				}
			}
			if (searchType == -2) {
				int i;
				const char *stripBuf = StripText();
				for (i = 0; i < wordCount; i++) {
					sres = ((flags & REG_ICASE) == REG_ICASE) ? stristr(stripBuf, words[i]) : strstr(stripBuf, words[i]);
					if (!sres)
						break;
				}
				if (i == wordCount) {
					textkey = KeyText();
					listkey << textkey;
				}

			}
		}
		(*this)++;
	}
	if (searchType >= 0)
		regfree(&preg);

	if (searchType == -2) {
		free(words);
		free(wordBuf);
	}

	setKey(*savekey);

	if (!savekey->Persist())
		delete savekey;

	if (searchkey)
		delete searchkey;

	listkey = TOP;
	processEntryAttributes(savePEA);
	(*percent)(100, percentUserData);

	return listkey;
}


/******************************************************************************
 * SWModule::StripText() 	- calls all stripfilters on current text
 *
 * ENT:	buf	- buf to massage instead of this modules current text
 * 	len	- max len of buf
 *
 * RET: this module's text at specified key location massaged by Strip filters
 */

const char *SWModule::StripText(char *buf, int len)
{
	return RenderText(buf, len, false);
}


/******************************************************************************
 * SWModule::RenderText 	- calls all renderfilters on current text
 *
 * ENT:	buf	- buffer to Render instead of current module position
 *
 * RET: listkey set to verses that contain istr
 */

 const char *SWModule::RenderText(char *buf, int len, bool render) {
	entryAttributes.clear();
	char *tmpbuf = (buf) ? buf : getRawEntry();
	SWKey *key = 0;
	static char *null = "";

	if (tmpbuf) {
		unsigned long size = (len < 0) ? ((getEntrySize()<0) ? strlen(tmpbuf) : getEntrySize()) * FILTERPAD : len;
		if (size > 0) {
			key = (SWKey *)*this;

			optionFilter(tmpbuf, size, key);
	
			if (render) {
				renderFilter(tmpbuf, size, key);
				encodingFilter(tmpbuf, size, key);
			}
			else	stripFilter(tmpbuf, size, key);
		}
	}
	else {
		tmpbuf = null;
	}

	return tmpbuf;
}


/******************************************************************************
 * SWModule::RenderText 	- calls all renderfilters on current text
 *
 * ENT:	tmpKey	- key to use to grab text
 *
 * RET: this module's text at specified key location massaged by RenderFilers
 */

 const char *SWModule::RenderText(SWKey *tmpKey)
{
	SWKey *savekey;
	const char *retVal;

	if (!key->Persist()) {
		savekey = CreateKey();
		*savekey = *key;
	}
	else	savekey = key;

	setKey(*tmpKey);

	retVal = RenderText();

	setKey(*savekey);

	if (!savekey->Persist())
		delete savekey;

	return retVal;
}


/******************************************************************************
 * SWModule::StripText 	- calls all StripTextFilters on current text
 *
 * ENT:	tmpKey	- key to use to grab text
 *
 * RET: this module's text at specified key location massaged by Strip filters
 */

const char *SWModule::StripText(SWKey *tmpKey)
{
	SWKey *savekey;
	const char *retVal;

	if (!key->Persist()) {
		savekey = CreateKey();
		*savekey = *key;
	}
	else	savekey = key;

	setKey(*tmpKey);

	retVal = StripText();

	setKey(*savekey);

	if (!savekey->Persist())
		delete savekey;

	return retVal;
}


const char *SWModule::getConfigEntry(const char *key) const {
	ConfigEntMap::iterator it = config->find(key);
	return (it != config->end()) ? it->second.c_str() : 0;
}


void SWModule::setConfig(ConfigEntMap *config) {
	this->config = config;
}

SWORD_NAMESPACE_END