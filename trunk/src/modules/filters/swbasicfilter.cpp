/******************************************************************************
 *  swbasicfilter.h	- definition of class SWBasicFilter.  An SWFilter
 *  				impl that provides some basic methods that
 *  				many filters will need and can use as a starting
 *  				point. 
 *
 * $Id: swbasicfilter.cpp,v 1.3 2001/09/02 09:10:14 scribe Exp $
 *
 * Copyright 2001 CrossWire Bible Society (http://www.crosswire.org)
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

#include <stdlib.h>
#include <string.h>
#include <swbasicfilter.h>


SWBasicFilter::SWBasicFilter() {
	tokenStart = 0;
	tokenEnd = 0;
	escStart = 0;
	escEnd = 0;
	escStringCaseSensitive = false;
	tokenCaseSensitive = false;
	passThruUnknownToken = false;
	passThruUnknownEsc = false;
	init();
}


void SWBasicFilter::setPassThruUnknownToken(bool val) {
	passThruUnknownToken = val;
}


void SWBasicFilter::setPassThruUnknownEscapeString(bool val) {
	passThruUnknownEsc = val;
}


void SWBasicFilter::setTokenCaseSensitive(bool val) {
	tokenCaseSensitive = val;
}


void SWBasicFilter::setEscapeStringCaseSensitive(bool val) {
	escStringCaseSensitive = val;
}


SWBasicFilter::~SWBasicFilter() {
	if (tokenStart)
		delete [] tokenStart;

	if (tokenEnd)
		delete [] tokenEnd;

	if (escStart)
		delete [] escStart;

	if (escEnd)
		delete [] escEnd;
}


void SWBasicFilter::addTokenSubstitute(const char *findString, const char *replaceString) {
	char *buf = 0;

	if (!tokenCaseSensitive) {
		stdstr(&buf, findString);
		toupperstr(buf);
		tokenSubMap.insert(DualStringMap::value_type(buf, replaceString));
		delete [] buf;
	}
	else tokenSubMap.insert(DualStringMap::value_type(findString, replaceString));
}


void SWBasicFilter::addEscapeStringSubstitute(const char *findString, const char *replaceString) {
	char *buf = 0;

	if (!escStringCaseSensitive) {
		stdstr(&buf, findString);
		toupperstr(buf);
		escSubMap.insert(DualStringMap::value_type(buf, replaceString));
		delete [] buf;
	}
	else escSubMap.insert(DualStringMap::value_type(findString, replaceString));
}


void SWBasicFilter::init() {
	setTokenStart("<");
	setTokenEnd(">");
	setEscapeStart("&");
	setEscapeEnd(";");

	setEscapeStringCaseSensitive(true);

	addEscapeStringSubstitute("nbsp", " ");
	addEscapeStringSubstitute("quot", "\"");
	addEscapeStringSubstitute("amp", "&");
	addEscapeStringSubstitute("lt", "<");
	addEscapeStringSubstitute("gt", ">");
	addEscapeStringSubstitute("brvbar", "|");
	addEscapeStringSubstitute("sect", "�");
	addEscapeStringSubstitute("copy", "�");
	addEscapeStringSubstitute("laquo", "�");
	addEscapeStringSubstitute("reg", "�");
	addEscapeStringSubstitute("acute", "�");
	addEscapeStringSubstitute("para", "�");
	addEscapeStringSubstitute("raquo", "�");

	addEscapeStringSubstitute("Aacute", "�");
	addEscapeStringSubstitute("Agrave", "�");
	addEscapeStringSubstitute("Acirc", "�");
	addEscapeStringSubstitute("Auml", "�");
	addEscapeStringSubstitute("Atilde", "�");
	addEscapeStringSubstitute("Aring", "�");
	addEscapeStringSubstitute("aacute", "�");
	addEscapeStringSubstitute("agrave", "�");
	addEscapeStringSubstitute("acirc", "�");
	addEscapeStringSubstitute("auml", "�");
	addEscapeStringSubstitute("atilde", "�");
	addEscapeStringSubstitute("aring", "�");
	addEscapeStringSubstitute("Eacute", "�");
	addEscapeStringSubstitute("Egrave", "�");
	addEscapeStringSubstitute("Ecirc", "�");
	addEscapeStringSubstitute("Euml", "�");
	addEscapeStringSubstitute("eacute", "�");
	addEscapeStringSubstitute("egrave", "�");
	addEscapeStringSubstitute("ecirc", "�");
	addEscapeStringSubstitute("euml", "�");
	addEscapeStringSubstitute("Iacute", "�");
	addEscapeStringSubstitute("Igrave", "�");
	addEscapeStringSubstitute("Icirc", "�");
	addEscapeStringSubstitute("Iuml", "�");
	addEscapeStringSubstitute("iacute", "�");
	addEscapeStringSubstitute("igrave", "�");
	addEscapeStringSubstitute("icirc", "�");
	addEscapeStringSubstitute("iuml", "�");
	addEscapeStringSubstitute("Oacute", "�");
	addEscapeStringSubstitute("Ograve", "�");
	addEscapeStringSubstitute("Ocirc", "�");
	addEscapeStringSubstitute("Ouml", "�");
	addEscapeStringSubstitute("Otilde", "�");
	addEscapeStringSubstitute("oacute", "�");
	addEscapeStringSubstitute("ograve", "�");
	addEscapeStringSubstitute("ocirc", "�");
	addEscapeStringSubstitute("ouml", "�");
	addEscapeStringSubstitute("otilde", "�");
	addEscapeStringSubstitute("Uacute", "�");
	addEscapeStringSubstitute("Ugrave", "�");
	addEscapeStringSubstitute("Ucirc", "�");
	addEscapeStringSubstitute("Uuml", "�");
	addEscapeStringSubstitute("uacute", "�");
	addEscapeStringSubstitute("ugrave", "�");
	addEscapeStringSubstitute("ucirc", "�");
	addEscapeStringSubstitute("uuml", "�");
	addEscapeStringSubstitute("Yacute", "�");
	addEscapeStringSubstitute("yacute", "�");
	addEscapeStringSubstitute("yuml", "�");

	addEscapeStringSubstitute("deg", "�");
	addEscapeStringSubstitute("plusmn", "�");
	addEscapeStringSubstitute("sup2", "�");
	addEscapeStringSubstitute("sup3", "�");
	addEscapeStringSubstitute("sup1", "�");
	addEscapeStringSubstitute("nbsp", "�");
	addEscapeStringSubstitute("pound", "�");
	addEscapeStringSubstitute("cent", "�");
	addEscapeStringSubstitute("frac14", "�");
	addEscapeStringSubstitute("frac12", "�");
	addEscapeStringSubstitute("frac34", "�");
	addEscapeStringSubstitute("iquest", "�");
	addEscapeStringSubstitute("iexcl", "�");
	addEscapeStringSubstitute("ETH", "�");
	addEscapeStringSubstitute("eth", "�");
	addEscapeStringSubstitute("THORN", "�");
	addEscapeStringSubstitute("thorn", "�");
	addEscapeStringSubstitute("AElig", "�");
	addEscapeStringSubstitute("aelig", "�");
	addEscapeStringSubstitute("Oslash", "�");
	addEscapeStringSubstitute("curren", "�");
	addEscapeStringSubstitute("Ccedil", "�");
	addEscapeStringSubstitute("ccedil", "�");
	addEscapeStringSubstitute("szlig", "�");
	addEscapeStringSubstitute("Ntilde", "�");
	addEscapeStringSubstitute("ntilde", "�");
	addEscapeStringSubstitute("yen", "�");
	addEscapeStringSubstitute("not", "�");
	addEscapeStringSubstitute("ordf", "�");
	addEscapeStringSubstitute("uml", "�");
	addEscapeStringSubstitute("shy", "�");
	addEscapeStringSubstitute("macr", "�");
	
	setTokenCaseSensitive(true);

	addTokenSubstitute("/scripRef", " </A>");	  
	addTokenSubstitute("note place=\"foot\"", " <SMALL>(");
	addTokenSubstitute("/note", ")</SMALL> ");
	addTokenSubstitute("foreign lang=\"el\"", "<FONT FACE=\"SIL Galatia\">");
	addTokenSubstitute("foreign lang=\"he\"", "<FONT FACE=\"SIL Ezra\">");
	addTokenSubstitute("/foreign", "</FONT>");

}


void SWBasicFilter::pushString(char **buf, const char *fragToPush) {
	while (*fragToPush) {
		**buf = *fragToPush;
		(*buf)++;
	}
}


bool SWBasicFilter::substituteToken(char **buf, const char *token) {
	DualStringMap::iterator it;
	it = tokenSubMap.find(token);
	if (it != tokenSubMap.end()) {
		pushString(buf, it->second.c_str());
		return true;
	}
	return false;
}


bool SWBasicFilter::substituteEscapeString(char **buf, const char *escString) {
	DualStringMap::iterator it;
	it = escSubMap.find(escString);
	if (it != escSubMap.end()) {
		pushString(buf, it->second.c_str());
		return true;
	}
	return false;
}


bool SWBasicFilter::handleToken(char **buf, const char *token) {
	if (!substituteToken(buf, token)) {
	// manually process if it wasn't a simple substitution
		if (!strncmp(token, "sync type=\"Strongs\" value=\"", 27) && (token[27] == 'H' || token[27] == 'G' || token[27] == 'A')) {
			pushString(buf, "<SMALL><EM>");
			for (unsigned int i = 28; token[i] != '\"'; i++)
				**buf++ = token[i];
			pushString(buf, "</EM></SMALL>");
		}

		else if (!strncmp(token, "sync type=\"Morph\" value=\"", 25)) {
			pushString(buf, "<SMALL><EM>");
			for (unsigned int i = 25; token[i] != '\"'; i++)
				**buf++ = token[i];
			pushString(buf, "</EM></SMALL>");
		}

		else if (!strncmp(token, "scripRef version", 16)) {
			pushString(buf, "<A HREF=\"");
			for (unsigned int i = 32; token[i] != '\"'; i++)
				**buf++ = token[i];
			**buf++ = '\"';
			**buf++ = '>';
		} 

		else if (!strncmp(token, "sync type=\"Strongs\" value=\"T", 28)) {
			pushString(buf, "<SMALL><I>");
			for (unsigned int i = 29; token[i] != '\"'; i++)
				**buf++ = token[i];
			pushString(buf, "</I></SMALL>");
		}

		else {
			return false;  // we still didn't handle token
		}
	}
	return true;
}


bool SWBasicFilter::handleEscapeString(char **buf, const char *escString) {
	return substituteEscapeString(buf, escString);
}


void SWBasicFilter::setEscapeStart(const char *escStart) {
	stdstr(&(this->escStart), escStart);
}


void SWBasicFilter::setEscapeEnd(const char *escEnd) {
	stdstr(&(this->escEnd), escEnd);
}


void SWBasicFilter::setTokenStart(const char *tokenStart) {
	stdstr(&(this->tokenStart), tokenStart);
}


void SWBasicFilter::setTokenEnd(const char *tokenEnd) {
	stdstr(&(this->tokenEnd), tokenEnd);
}


char SWBasicFilter::ProcessText(char *text, int maxlen) {
	char *to, *from, token[2048];
	int tokpos = 0;
	bool intoken 	= false;
	int len;
	bool inEsc = false;
	char escStartLen = strlen(escStart);
	char escEndLen   = strlen(escEnd);
	char escStartPos = 0, escEndPos = 0;
	char tokenStartLen = strlen(tokenStart);
	char tokenEndLen   = strlen(tokenEnd);
	char tokenStartPos = 0, tokenEndPos = 0;

	len = strlen(text) + 1;		// shift string to right of buffer
	if (len < maxlen) {
		memmove(&text[maxlen - len], text, len);
		from = &text[maxlen - len];
	}
	else	from = text;			// -------------------------------


	for (to = text; *from; from++) {
		if (*from == tokenStart[tokenStartPos]) {
			if (tokenStartPos == (tokenStartLen - 1)) {
				intoken = true;
				tokpos = 0;
				memset(token, 0, 2048);
				inEsc = false;
			}
			else tokenStartPos++;
			continue;
		}

		if (*from == escStart[escStartPos]) {
			if (escStartPos == (escStartLen - 1)) {
				intoken = true;
				tokpos = 0;
				memset(token, 0, 2048);
				inEsc = true;
			}
			else escStartPos++;
			continue;
		}

		if (inEsc) {
			if (*from == escEnd[escEndPos]) {
				if (escEndPos == (escEndLen - 1)) {
					intoken = false;
					if ((!handleEscapeString(&to, token)) && (passThruUnknownEsc)) {
						pushString(&to, escStart);
						pushString(&to, token);
						pushString(&to, escEnd);
					}
					escEndPos = escStartPos = tokenEndPos = tokenStartPos = 0;
					continue;
				}
			}
		}

		if (!inEsc) {
			if (*from == tokenEnd[tokenEndPos]) {
				if (tokenEndPos == (tokenEndLen - 1)) {
					intoken = false;
					if ((!handleToken(&to, token)) && (passThruUnknownToken)) {
						pushString(&to, tokenStart);
						pushString(&to, token);
						pushString(&to, tokenEnd);
					}
					escEndPos = escStartPos = tokenEndPos = tokenStartPos = 0;
					continue;
				}
			}
		}

		if (intoken) {
			if (tokpos < 2047)
				token[tokpos++] = *from;
		}
		else	*to++ = *from;
	}
	*to++ = 0;
	*to = 0;
	return 0;
}

