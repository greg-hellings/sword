/***************************************************************************
                     ThMLWEBIF.cpp  -  ThML to HTML filter with hrefs
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
#include <thmlwebif.h>
#include <swmodule.h>
#include <utilweb.h>
#include <utilxml.h>

SWORD_NAMESPACE_START

ThMLWEBIF::ThMLWEBIF() : baseURL(""), passageStudyURL(baseURL + "passagestudy.jsp") {
  //all's done in ThMLHTMLHREF
}

bool ThMLWEBIF::handleToken(SWBuf &buf, const char *token, BasicFilterUserData *userData) {
	const char *tok;

	if (!substituteToken(buf, token)) { // manually process if it wasn't a simple substitution
		MyUserData *u = (MyUserData *)userData;
		XMLTag tag(token);
		SWBuf url;
		if (!strcmp(tag.getName(), "sync")) {
			const char* value = tag.getAttribute("value");
			url = value;

			if(tag.getAttribute("type") && !strcmp(tag.getAttribute("type"), "morph")){
				buf += "<small><em> (";
			}
			else {
				if (value) {
					value++; //skip leading G, H or T
					//url = value;
				}

				buf += "<small><em> &lt;";
			}

			buf.appendFormatted("<a href=\"%s?showStrong=%s\">", passageStudyURL.c_str(), encodeURL(url).c_str() );
			buf += value;
			buf += "</a>";

			if (tag.getAttribute("type") && !strcmp(tag.getAttribute("type"), "morph")) {
				buf += ") </em></small>";
			}
			else {
				buf += "&gt; </em></small>";
			}
		}
		else if (!strcmp(tag.getName(), "scripRef")) {
			if (tag.isEndTag()) {
				if (u->inscriptRef) { // like  "<scripRef passage="John 3:16">John 3:16</scripRef>"
					u->inscriptRef = false;
					buf += "</a>";
				}
				else { // end of scripRef like "<scripRef>John 3:16</scripRef>"
					url = u->lastTextNode;
					buf.appendFormatted("<a href=\"%s?key=%s\">", passageStudyURL.c_str(), encodeURL(url).c_str());
					buf += u->lastTextNode.c_str();
					buf += "</a>";

					// let's let text resume to output again
					u->suspendTextPassThru = false;
				}
			}
			else if (tag.getAttribute("passage")) { //passage given
				u->inscriptRef = true;

				buf.appendFormatted("<a href=\"%s?key=%s\">", passageStudyURL.c_str(), encodeURL(tag.getAttribute("passage")).c_str());
			}
			else { //no passage given
				u->inscriptRef = false;
				// let's stop text from going to output
				u->suspendTextPassThru = true;
			}
		}
		else {
			return ThMLHTMLHREF::handleToken(buf,token,userData);
		}
	}
	return true;
}


SWORD_NAMESPACE_END
