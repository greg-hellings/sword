/***************************************************************************
                     thmlrtf.cpp  -  ThML to RTF filter
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
#include <thmlrtf.h>
#include <swmodule.h>

SWORD_NAMESPACE_START

ThMLRTF::ThMLRTF()
{
	setTokenStart("<");
	setTokenEnd(">");

	setEscapeStart("&");
	setEscapeEnd(";");

	setEscapeStringCaseSensitive(true);

	addEscapeStringSubstitute("nbsp", " ");
	addEscapeStringSubstitute("apos", "'");
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

	addTokenSubstitute("/note", ") }");

        addTokenSubstitute("br", "\\line ");
        addTokenSubstitute("br /", "\\line ");
        addTokenSubstitute("i", "{\\i1 ");
        addTokenSubstitute("/i", "}");
        addTokenSubstitute("b", "{\\b1 ");
        addTokenSubstitute("/b", "}");
        addTokenSubstitute("p", "\\par ");

        //we need uppercase forms for the moment to support a few early ThML modules that aren't XHTML compliant
        addTokenSubstitute("BR", "\\line ");
        addTokenSubstitute("I", "{\\i1 ");
        addTokenSubstitute("/I", "}");
        addTokenSubstitute("B", "{\\b1 ");
        addTokenSubstitute("/B", "}");
        addTokenSubstitute("P", "\\par ");
}

bool ThMLRTF::handleToken(SWBuf &buf, const char *token, DualStringMap &userData) {
	if (!substituteToken(buf, token)) {
	// manually process if it wasn't a simple substitution
		if (!strncmp(token, "sync type=\"Strongs\" value=\"", 27)) {
			if (token[27] == 'H' || token[27] == 'G' || token[27] == 'A') {
				buf += " {\\fs15 <";
				for (unsigned int i = 28; token[i] != '\"'; i++)
					buf += token[i];
				buf += ">}";
			}
			else if (token[27] == 'T') {
				buf += " {\\fs15 (";
				for (unsigned int i = 28; token[i] != '\"'; i++)
					buf += token[i];
				buf += ")}";
			}
		}
		else if (!strncmp(token, "sync type=\"morph\" ", 18)) {
			buf += " {\\fs15 (";
			for (const char *tok = token + 5; *tok; tok++) {
				if (!strncmp(tok, "value=\"", 7)) {
					tok += 7;
					for (;*tok != '\"'; tok++)
						buf += *tok;
					break;
				}
			}

			buf += ")}";
		}
		else if (!strncmp(token, "sync type=\"lemma\" value=\"", 25)) {
			buf += "{\\fs15 (";
			for (unsigned int i = 25; token[i] != '\"'; i++)
				buf += token[i];
			buf += ")}";
		}
		else if (!strncmp(token, "scripRef", 8)) {
//			buf += "{\\cf2 #";
			buf += "<a href=\"\">";
		}
		else if (!strncmp(token, "/scripRef", 9)) {
			buf += "</a>";
		}
		else if (!strncmp(token, "div", 3)) {
			buf += '{';
			if (!strncmp(token, "div class=\"title\"", 17)) {
				buf += "\\par\\i1\\b1 ";
				userData["sechead"] = "true";
			}
			else if (!strncmp(token, "div class=\"sechead\"", 19)) {
				buf += "\\par\\i1\\b1 ";
				userData["sechead"] = "true";
			}
		}
		else if (!strncmp(token, "/div", 4)) {
			if (userData["sechead"] == "true") {
				buf += "\\par ";
				userData["sechead"] = "false";
			}
			buf += '}';
		}
		else if (!strncmp(token, "note", 4)) {
			buf += " {\\i1\\fs15 (";
		}
		else if (!strncmp(token, "img ", 4)) {
			const char *src = strstr(token, "src");
			if (!src)		// assert we have a src attribute
				return false;

                        char* filepath = new char[strlen(module->getConfigEntry("AbsoluteDataPath")) + strlen(token)];
                        *filepath = 0;
                        strcpy(filepath, module->getConfigEntry("AbsoluteDataPath"));
                        unsigned long i = strlen(filepath);
                        const char *c;
			for (c = (src + 5); *c != '"'; c++) {
				filepath[i] = *c;
                                i++;
			}
                        filepath[i] = 0;

                        for (c = filepath + strlen(filepath); c > filepath && *c != '.'; c--);
                        c++;

                        char imgc;
                        FILE* imgfile;
/*
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
