/***************************************************************************
                     thmlhtml.cpp  -  ThML to HTML filter
                             -------------------
    begin                : 1999-10-27
    copyright            : 2001 by CrossWire Bible Society
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <thmlhtml.h>


ThMLHTML::ThMLHTML() {
	setTokenStart("<");
	setTokenEnd(">");
/*
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
*/
	setTokenCaseSensitive(true);

	addTokenSubstitute("/scripRef", " </a>");
	addTokenSubstitute("note", " <small>(");
	addTokenSubstitute("/note", ")</small> ");
}


bool ThMLHTML::handleToken(char **buf, const char *token, DualStringMap &userData) {
	if (!substituteToken(buf, token)) {
	// manually process if it wasn't a simple substitution
		if (!strncmp(token, "sync type=\"Strongs\" value=\"", 27)) {
                        if (token[27] == 'H' || token[27] == 'G' || token[27] == 'A') {
        			pushString(buf, "<small><em>");
	        		for (unsigned int i = 5; i < strlen(token); i++)
		        		if(token[i] != '\"')
			        		*(*buf)++ = token[i];
        			pushString(buf, "</em></small>");
                        }
                        else if (token[27] == 'T') {
        			pushString(buf, "<small><i>");
        			for (unsigned int i = 29; token[i] != '\"'; i++)
        				*(*buf)++ = token[i];
        			pushString(buf, "</i></small>");
                        }
		}
		else if (!strncmp(token, "sync type=\"morph\" value=\"", 25)) {
			pushString(buf, "<small><em>");
			for (unsigned int i = 25; token[i] != '\"'; i++)
				*(*buf)++ = token[i];
			pushString(buf, "</em></small>");
		}
		else if (!strncmp(token, "sync type=\"lemma\" value=\"", 25)) {
			pushString(buf, "<small><em>(");
			for (unsigned int i = 25; token[i] != '\"'; i++)
				*(*buf)++ = token[i];
			pushString(buf, ")</em></small>");
		}
		else if (!strncmp(token, "scripRef", 8)) {
			pushString(buf, "<a href=\"");
			for (unsigned int i = 9; i < strlen(token); i++)
				if(token[i] != '\"')
					*(*buf)++ = token[i];
			*(*buf)++ = '\"';
			*(*buf)++ = '>';
		}
                else if(!strncmp(token, "note", 4)) {
                        pushString(buf, "<small>(");
                }

		else {
			return false;  // we still didn't handle token
		}
	}
	return true;
}

