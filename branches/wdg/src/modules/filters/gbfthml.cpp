/***************************************************************************
                     gbfthml.cpp  -  GBF to ThML filter
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
#include <gbfthml.h>

SWORD_NAMESPACE_START

GBFThML::GBFThML()
{
}


char GBFThML::processText(SWBuf &text, const SWKey *key, const SWModule *module) {
	const char *from;
	char token[2048];
	int tokpos = 0;
	bool intoken 	= false;
	int len;
	const char *tok;

	SWBuf orig = text;
	from = orig.c_str();

	for (text = ""; *from; from++) {
		if (*from == '<') {
			intoken = true;
			tokpos = 0;
			token[0] = 0;
			token[1] = 0;
			token[2] = 0;
			continue;
		}
		if (*from == '>')
		{
			intoken = false;
			// process desired tokens
			switch (*token) {
			case 'W':	// Strongs
			  switch(token[1]) {
			  case 'G':
			  case 'H':			    
			    text += "<sync type=\"Strongs\" value=\"";
			    for (tok = token + 1; *tok; tok++)
				 text += *tok;
			    text += "\" />";
			    continue;
			    
			  case 'T':               // Tense
			    text += "<sync type=\"Morph\" value=\"";
			    for (tok = token + 2; *tok; tok++)
				 text += *tok;
			    text += "\" />";
			    continue;
				}
			  break;
			case 'R':
			  switch(token[1])
			    {
			    case 'X':
				 text += "<a href=\"";
				 for (tok = token + 3; *tok; tok++) {
				if(*tok != '<' && *tok+1 != 'R' && *tok+2 != 'x') {
				  text += *tok;
				}
				else {
				  break;
				}
				 }
				 text += "\">";
				 continue;
			    case 'x':
				 text += "</a>";
				 continue;
			    case 'F':               // footnote begin
				 text += "<note>";
				 continue;
			    case 'f':               // footnote end
				 text += "</note>";
				 continue;
			    }
			  break;
			case 'F':			// font tags
			  switch(token[1])
			    {
			    case 'N':
				 text += "<font face=\"";
				 for (tok = token + 2; *tok; tok++)
					text += *tok;
				text += "\">";
				 continue;
			    case 'n':
				 text += "</font>";
				 continue;
			    case 'I':		// italic start
				 text += "<i>";
				 continue;
			    case 'i':		// italic end
				 text += "</i>";
				 continue;
			    case 'B':		// bold start
				 text += "<b>";
				 continue;
			    case 'b':		// bold end
				 text += "</b>";
				 continue;

			    case 'R':		// words of Jesus begin
				 text += "<font color=\"#ff0000\">";
				 continue;
			    case 'r':		// words of Jesus end
				 text += "</font>";
				 continue;
			    case 'U':		// Underline start
				 text += "<u>";
				 continue;
			    case 'u':		// Underline end
				 text += "</u>";
				 continue;
			    case 'O':		// Old Testament quote begin
				 text += "<cite>";
				 continue;
			    case 'o':		// Old Testament quote end
				 text += "</cite>";
				 continue;
			    case 'S':		// Superscript begin
				 text += "<sup>";
				 continue;
			    case 's':		// Superscript end
				 text += "</sup>";
				 continue;
			    case 'V':		// Subscript begin
				 text += "<sub>";
				 continue;
			    case 'v':		// Subscript end
				 text += "</sub>";
				 continue;
			    }
			  break;
			case 'C':			// special character tags
			  switch(token[1])
				{
				case 'A':               // ASCII value
				  text += (char)atoi(&token[2]);
				  continue;
				case 'G':
				  //*to++ = ' ';
				  continue;
				case 'L':               // line break
				 text += "<br /> ";
				  continue;
				case 'M':               // new paragraph
				 text += "<p />";
				  continue;
				case 'T':
				  //*to++ = ' ';
				  continue;
				}
			  break;
			case 'T':			// title formatting
			  switch(token[1])
			    {
			    case 'T':               // Book title begin
				 text += "<big>";
				 continue;
			    case 't':
				 text += "</big>";
				 continue;
			    case 'S':
				 text += "<div class=\"sechead\">";
				 continue;
			    case 's':
				 text += "</div>";
				 continue;
			    }
			  break;

			case 'P':			// special formatting
			  switch(token[1]) {
			    case 'P':               // Poetry begin
				 text += "<verse>";
				 continue;
			    case 'p':
				 text += "</verse>";
				 continue;
			    }
			  break;
			}
			continue;
		}
		if (intoken) {
			if (tokpos < 2045)
				token[tokpos++] = *from;
				token[tokpos+2] = 0;
		}
		else	text += *from;
	}
	return 0;
}



SWORD_NAMESPACE_END