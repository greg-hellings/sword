/***************************************************************************
                     osisrtf.cpp  -  OSIS to RTF filter
                             -------------------
    begin                : 2003-02-15
    copyright            : 2003 by CrossWire Bible Society
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
#include <osisrtf.h>
#include <utilxml.h>
#include <versekey.h>
#include <swmodule.h>

SWORD_NAMESPACE_START


OSISRTF::MyUserData::MyUserData(const SWModule *module, const SWKey *key) : BasicFilterUserData(module, key) {
	osisQToTick = ((!module->getConfigEntry("OSISqToTick")) || (strcmp(module->getConfigEntry("OSISqToTick"), "false")));
}


OSISRTF::OSISRTF() {
	setTokenStart("<");
	setTokenEnd(">");
  
	setEscapeStart("&");
	setEscapeEnd(";");
  
	setEscapeStringCaseSensitive(true);

	addEscapeStringSubstitute("amp", "&");
	addEscapeStringSubstitute("apos", "'");
	addEscapeStringSubstitute("lt", "<");
	addEscapeStringSubstitute("gt", ">");
	addEscapeStringSubstitute("quot", "\"");
        addTokenSubstitute("lg", "{\\par}");
        addTokenSubstitute("/lg", "{\\par}");
	setTokenCaseSensitive(true);
}


bool OSISRTF::handleToken(SWBuf &buf, const char *token, BasicFilterUserData *userData) {
  // manually process if it wasn't a simple substitution
	if (!substituteToken(buf, token)) {
		MyUserData *u = (MyUserData *)userData;
		XMLTag tag(token);

		// <w> tag
		if (!strcmp(tag.getName(), "w")) {

			// start <w> tag
			if ((!tag.isEmpty()) && (!tag.isEndTag())) {
				buf += "{";
				u->w = token;
			}

			// end or empty <w> tag
			else {
				bool endTag = tag.isEndTag();
				SWBuf lastText;
				bool show = true;	// to handle unplaced article in kjv2003-- temporary till combined

				if (endTag) {
					tag = u->w.c_str();
					lastText = u->lastTextNode.c_str();
				}
				else lastText = "stuff";

				const char *attrib;
				const char *val;
				if (attrib = tag.getAttribute("xlit")) {
					val = strchr(attrib, ':');
					val = (val) ? (val + 1) : attrib;
					buf.appendFormatted(" {\\fs15 <%s>}", val);
				}
				if (attrib = tag.getAttribute("gloss")) {
					val = strchr(attrib, ':');
					val = (val) ? (val + 1) : attrib;
					buf.appendFormatted(" {\\fs15 <%s>}", val);
				}
				if (attrib = tag.getAttribute("lemma")) {
					int count = tag.getAttributePartCount("lemma");
					int i = (count > 1) ? 0 : -1;		// -1 for whole value cuz it's faster, but does the same thing as 0
					do {
						attrib = tag.getAttribute("lemma", i);
						if (i < 0) i = 0;	// to handle our -1 condition
						val = strchr(attrib, ':');
						val = (val) ? (val + 1) : attrib;
						if ((strchr("GH", *val)) && (isdigit(val[1])))
							val++;
						if ((!strcmp(val, "3588")) && (lastText.length() < 1))
							show = false;
						else	buf.appendFormatted(" {\\cf3 \\sub <%s>}", val);
					} while (++i < count);
				}
				if ((attrib = tag.getAttribute("morph")) && (show)) {
					SWBuf savelemma = tag.getAttribute("savlm");
					if ((strstr(savelemma.c_str(), "3588")) && (lastText.length() < 1))
						show = false;
					if (show) {
						int count = tag.getAttributePartCount("morph");
						int i = (count > 1) ? 0 : -1;		// -1 for whole value cuz it's faster, but does the same thing as 0
						do {
							attrib = tag.getAttribute("morph", i);
							if (i < 0) i = 0;	// to handle our -1 condition
							val = strchr(attrib, ':');
							val = (val) ? (val + 1) : attrib;
							if ((*val == 'T') && (strchr("GH", val[1])) && (isdigit(val[2])))
								val+=2;
							buf.appendFormatted(" {\\cf4 \\sub (%s)}", val);
						} while (++i < count);
					}
				}
				if (attrib = tag.getAttribute("POS")) {
					val = strchr(attrib, ':');
					val = (val) ? (val + 1) : attrib;
					buf.appendFormatted(" {\\fs15 <%s>}", val);
				}

				if (endTag)
					buf += "}";
			}
		}

		// <note> tag
		else if (!strcmp(tag.getName(), "note")) {
			if (!tag.isEndTag()) {
				if (!tag.isEmpty()) {
					SWBuf type = tag.getAttribute("type");

					if (type != "strongsMarkup") {	// leave strong's markup notes out, in the future we'll probably have different option filters to turn different note types on or off
						SWBuf footnoteNumber = tag.getAttribute("swordFootnote");
						VerseKey *vkey;
						// see if we have a VerseKey * or descendant
						try {
							vkey = SWDYNAMIC_CAST(VerseKey, u->key);
						}
						catch ( ... ) {	}
						if (vkey) {
							buf.appendFormatted("{\\super <a href=\"\">*%c%i.%s</a>} ", ((tag.getAttribute("type") && ((!strcmp(tag.getAttribute("type"), "crossReference")) || (!strcmp(tag.getAttribute("type"), "x-cross-ref")))) ? 'x':'n'), vkey->Verse(), footnoteNumber.c_str());
						}
					}
					u->suspendTextPassThru = true;
				}
			}
			if (tag.isEndTag()) {
				u->suspendTextPassThru = false;
			}
		}

		// <p> paragraph tag
		else if (!strcmp(tag.getName(), "p")) {
			if ((!tag.isEndTag()) && (!tag.isEmpty())) {	// non-empty start tag
				buf += "{\\par ";
			}
			else if (tag.isEndTag()) {	// end tag
				buf += "\\par}";
				userData->supressAdjacentWhitespace = true;
			}
			else {					// empty paragraph break marker
				buf += "{\\par\\par}";
				userData->supressAdjacentWhitespace = true;
			}
		}

		// <reference> tag
		else if (!strcmp(tag.getName(), "reference")) {
			if ((!tag.isEndTag()) && (!tag.isEmpty())) {
				buf += "{<a href=\"\">";
			}
			else if (tag.isEndTag()) {
				buf += "</a>}";
			}
		}

		// <l> poetry
		else if (!strcmp(tag.getName(), "l")) {
			if ((!tag.isEndTag()) && (!tag.isEmpty())) {
				buf += "{";
			}
			else if (tag.isEndTag()) {
				buf += "\\par}";
			}
			else if (tag.getAttribute("sID")) {	// empty line marker
				buf += "{\\par}";
			}
		}

                // <milestone type="line"/>
                else if ((!strcmp(tag.getName(), "milestone")) && (tag.getAttribute("type")) && (!strcmp(tag.getAttribute("type"), "line"))) {
        		buf += "{\\par}";
			userData->supressAdjacentWhitespace = true;
                }

		// <title>
		else if (!strcmp(tag.getName(), "title")) {
			if ((!tag.isEndTag()) && (!tag.isEmpty())) {
				buf += "{\\par\\i1\\b1 ";
			}
			else if (tag.isEndTag()) {
				buf += "\\par}";
			}
		}

		// <hi>
		else if (!strcmp(tag.getName(), "hi")) {
			SWBuf type = tag.getAttribute("type");
			if ((!tag.isEndTag()) && (!tag.isEmpty())) {
				if (type == "b" || type == "x-b")
					buf += "{\\b1 ";
				else	// all other types
					buf += "{\\i1 ";
			}
			else if (tag.isEndTag()) {
				buf += "}";
			}
		}

		// <q> quote
		else if (!strcmp(tag.getName(), "q")) {
			SWBuf type = tag.getAttribute("type");
			SWBuf who = tag.getAttribute("who");
			const char *lev = tag.getAttribute("level");
			int level = (lev) ? atoi(lev) : 1;

			if ((!tag.isEndTag()) && (!tag.isEmpty())) {
				buf += "{";

				//alternate " and '
				if (u->osisQToTick)
					buf += (level % 2) ? '\"' : '\'';

				if (who == "Jesus")
					buf += "\\cf6 ";
			}
			else if (tag.isEndTag()) {
				//alternate " and '
				if (u->osisQToTick)
					buf += (level % 2) ? '\"' : '\'';
				buf += "}";
			}
			else {	// empty quote marker
				//alternate " and '
				if (u->osisQToTick)
					buf += (level % 2) ? '\"' : '\'';
			}
		}

		// <transChange>
		else if (!strcmp(tag.getName(), "transChange")) {
			SWBuf type = tag.getAttribute("type");

			if ((!tag.isEndTag()) && (!tag.isEmpty())) {

// just do all transChange tags this way for now
//				if (type == "supplied")
					buf += "{\\i1 ";
			}
			else if (tag.isEndTag()) {
				buf += "}";
			}
		}

		else if (!strcmp(tag.getName(), "figure")) {
			const char *src = tag.getAttribute("src");
			if (!src)		// assert we have a src attribute
				return false;

			char* filepath = new char[strlen(u->module->getConfigEntry("AbsoluteDataPath")) + strlen(token)];
			*filepath = 0;
			strcpy(filepath, userData->module->getConfigEntry("AbsoluteDataPath"));
			strcat(filepath, src);

// we do this because BibleCS looks for this EXACT format for an image tag
			buf+="<figure src=\"";
			buf+=filepath;
			buf+="\" />";
/*
			char imgc;
			for (c = filepath + strlen(filepath); c > filepath && *c != '.'; c--);
			c++;
			FILE* imgfile;
				    if (stricmp(c, "jpg") || stricmp(c, "jpeg")) {
						  imgfile = fopen(filepath, "r");
						  if (imgfile != NULL) {
								buf += "{\\nonshppict {\\pict\\jpegblip ";
								while (feof(imgfile) != EOF) {
									   buf.appendFormatted("%2x", fgetc(imgfile));
								}
								fclose(imgfile);
								buf += "}}";
						  }
				    }
				    else if (stricmp(c, "png")) {
						  buf += "{\\*\\shppict {\\pict\\pngblip ";

						  buf += "}}";
				    }
*/
			delete [] filepath;
		}
		else {
			return false;  // we still didn't handle token
		}
	}
	return true;
}


SWORD_NAMESPACE_END

