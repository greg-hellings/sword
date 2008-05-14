/***************************************************************************
                          gbfcgi.cpp  -   GBF to Diatheke/CGI format
                             -------------------
    begin                    : 2001-11-12
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
#include "gbfcgi.h"

GBFCGI::GBFCGI() {
	setTokenStart("<");
	setTokenEnd(">");
	
	setTokenCaseSensitive(true);

	addTokenSubstitute("Rf", ")</small></font>");
	addTokenSubstitute("FI", "<i>"); // italics begin
	addTokenSubstitute("Fi", "</i>");
	addTokenSubstitute("FB", "<n>"); // bold begin
	addTokenSubstitute("Fb", "</n>");
	addTokenSubstitute("FR", "<font color=\"#FF0000\">"); // words of Jesus begin
	addTokenSubstitute("Fr", "</font>");
	addTokenSubstitute("FU", "<u>"); // underline begin
	addTokenSubstitute("Fu", "</u>");
	addTokenSubstitute("FO", "<cite>"); //  Old Testament quote begin
	addTokenSubstitute("Fo", "</cite>");
	addTokenSubstitute("FS", "<sup>"); // Superscript begin// Subscript begin
	addTokenSubstitute("Fs", "</sup>");
	addTokenSubstitute("FV", "<sub>"); // Subscript begin
	addTokenSubstitute("Fv", "</sub>");
	addTokenSubstitute("TT", "<big>"); // Book title begin
	addTokenSubstitute("Tt", "</big>");
	addTokenSubstitute("PP", "<cite>"); //  poetry  begin
	addTokenSubstitute("Pp", "</cite>");
	addTokenSubstitute("Fn", "</font>"); //  font  end
	addTokenSubstitute("CL", "<br />"); //  new line
	addTokenSubstitute("CM", "<br />"); //  paragraph
	addTokenSubstitute("CG", "&gt;"); //  ???
	addTokenSubstitute("CT", "&lt;"); // ???
	addTokenSubstitute("JR", "<div align=\"right\">"); // right align begin
	addTokenSubstitute("JC", "<div align=\"center\">"); // center align begin
	addTokenSubstitute("JL", "</div>"); // align end
	
}


bool GBFCGI::handleToken(char **buf, const char *token, DualStringMap &userData) {
	unsigned long i;
	if (!substituteToken(buf, token)) {
		if (!strncmp(token, "WG", 2) || !strncmp(token, "WH", 2)) { // strong's numbers
			pushString(buf, " <small><em>&lt;<a href=\"!DIATHEKE_URL!");
			if (token[1] == 'H') {
			  pushString(buf, "BDB");
			}
			else if (token[1] == 'G') {
			  pushString(buf, "Thayer");
			}
			pushString(buf, "=on&verse=");
			for (i = 2; i < strlen(token); i++)
			  *(*buf)++ = token[i];
			*(*buf)++ = '\"';
			*(*buf)++ = '>';
			for (i = 2; i < strlen(token); i++)
			  *(*buf)++ = token[i];
			pushString(buf, "</a>&gt;</em></small>");
		}

		else if (!strncmp(token, "WTG", 3) || !strncmp(token, "WTH", 3)) { // strong's numbers tense
			pushString(buf, " <small><em>&lt;<a href=\"!DIATHEKE_URL!");
			if (token[2] == 'H') {
			  pushString(buf, "BDB");
			}
			else if (token[2] == 'G') {
			  pushString(buf, "Thayer");
			}
			pushString(buf, "=on&verse=");
			for (i = 3; i < strlen(token); i++)
			  *(*buf)++ = token[i];
			*(*buf)++ = '\"';
			*(*buf)++ = '>';
			for (i = 3; i < strlen(token); i++)
			  *(*buf)++ = token[i];
			pushString(buf, "</a>&gt;</em></small>");
		}

		else if (!strncmp(token, "WT", 2)) { // morph tags
			pushString(buf, " <small><em>(<a href=\"!DIATHEKE_URL!Packard=on&verse=");
			for (i = 1; i < strlen(token); i++)
			  *(*buf)++ = token[i];
			*(*buf)++ = '\"';
			*(*buf)++ = '>';
			for (i = 1; i < strlen(token); i++)
			  *(*buf)++ = token[i];		
			pushString(buf, "</a>)</em></small>");
		}

		else if (!strncmp(token, "RB", 2)) {
			pushString(buf, "<i>");
			userData["hasFootnotePreTag"] = "true";
		}

		else if (!strncmp(token, "RF", 2)) {
			if(userData["hasFootnotePreTag"] == "true") {
				userData["hasFootnotePreTag"] = "false";
				pushString(buf, "</i> ");
			}
			pushString(buf, "<font color=\"#800000\"><small> (");
		}

		else if (!strncmp(token, "FN", 2)) {
			pushString(buf, "<font face=\"");
			for (i = 2; i < strlen(token); i++)		       
			  *(*buf)++ = token[i];
			*(*buf)++ = '\"';
			*(*buf)++ = '>';
		}

		else if (!strncmp(token, "CA", 2)) {	// ASCII value
			*(*buf)++ = (char)atoi(&token[2]);
		}
		
		else {
			return false;
		}
	}
	return true;
}