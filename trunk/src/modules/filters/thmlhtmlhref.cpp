/***************************************************************************
                     thmlhtmlhref.cpp  -  ThML to HTML filter with hrefs  
                             -------------------
    begin                    : 2001-09-03
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
#include <thmlhtmlhref.h>


ThMLHTMLHREF::ThMLHTMLHREF() {
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

	addTokenSubstitute("note place=\"foot\"", " <small>(");
	addTokenSubstitute("/note", ")</small> ");
}


bool ThMLHTMLHREF::handleToken(char **buf, const char *token, DualStringMap &userData) {
	unsigned long i;
	if (!substituteToken(buf, token)) {
	// manually process if it wasn't a simple substitution
		if (!strncmp(token, "sync type=\"Strongs\" value=\"", 27) && (token[27] == 'H' || token[27] == 'G' || token[27] == 'A')) {
			pushString(buf, "<a href=\"");
			for (i = 5; i < strlen(token)-1; i++)				
				if(token[i] != '\"') 			
					*(*buf)++ = token[i];
			*(*buf)++ = '\"';
			*(*buf)++ = '>';
			for (i = 28; i < strlen(token)-2; i++)				
				if(token[i] != '\"') 			
					*(*buf)++ = token[i];		
			pushString(buf, "</a>");
		}

		else if (!strncmp(token, "sync type=\"morph\" value=\"", 25)) {
			pushString(buf, "<a href=\"");
			for (i = 5; i < strlen(token)-1; i++)				
				if(token[i] != '\"') 			
					*(*buf)++ = token[i];
			*(*buf)++ = '\"';
			*(*buf)++ = '>';
			for (i = 28; i < strlen(token)-2; i++)				
				if(token[i] != '\"') 			
					*(*buf)++ = token[i];		
			pushString(buf, "</a>");
		}

		else if (!strncmp(token, "scripRef p", 10) || !strncmp(token, "scripRef v", 10)) {
			userData["inscriptRef"] = "true";
			pushString(buf, "<a href=\"");
			for (i = 9; i < strlen(token)-1; i++)				
				if(token[i] != '\"') 			
					*(*buf)++ = token[i];
			*(*buf)++ = '\"';
			*(*buf)++ = '>';
		} 

		// we're starting a scripRef like "<scripRef>John 3:16</scripRef>"
		else if (!strcmp(token, "scripRef")) {
			userData["inscriptRef"] = "false";
			// let's stop text from going to output
			userData["suspendTextPassThru"] = "true";
		}

		// we've ended a scripRef 
		else if (!strcmp(token, "/scripRef")) {
			if (userData["inscriptRef"] == "true") { // like  "<scripRef passage="John 3:16">John 3:16</scripRef>"
				userData["inscriptRef"] = "false";
				pushString(buf, "</a>");
			}
			
			else { // like "<scripRef>John 3:16</scripRef>"
				pushString(buf, "<a href=\"passage=");
				//char *strbuf = (char *)userData["lastTextNode"].c_str();
				pushString(buf, userData["lastTextNode"].c_str());
				*(*buf)++ = '\"';
				*(*buf)++ = '>';
				pushString(buf, userData["lastTextNode"].c_str());
				// let's let text resume to output again
				userData["suspendTextPassThru"] = "false";	
				pushString(buf, "</a>");
			}
		}
			
		else if (!strncmp(token, "div class=\"sechead\"", 19)) {
		        userData["SecHead"] = "true";
			pushString(buf, "<br /><b><i>");
		}
		else if (!strncmp(token, "/div", 4)) {
		        if (userData["SecHead"] == "true") {
			        pushString(buf, "</i></b><br />");
				userData["SecHead"] = "false";
			}
		}

		else if (!strncmp(token, "sync type=\"Strongs\" value=\"T", 28)) {
			pushString(buf, "<a href=\"");
			for (i = 5; i < strlen(token)-1; i++)				
				if(token[i] != '\"') 			
					*(*buf)++ = token[i];
			*(*buf)++ = '\"';
			*(*buf)++ = '>';
			for (i = 29; i < strlen(token)-2; i++)				
				if(token[i] != '\"') 			
					*(*buf)++ = token[i];		
			pushString(buf, "</a>");
		}

		else {
			*(*buf)++ = '<';
			for (i = 0; i < strlen(token); i++)
				*(*buf)++ = token[i];
				*(*buf)++ = '>';
			//return false;  // we still didn't handle token
		}
	}
	return true;
}

