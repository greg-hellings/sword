/***************************************************************************
                          rwphtml.cpp  -  description
                             -------------------
    begin                : Thu Jun 24 1999
    copyright            : (C) 1999 by Torsten Uhlmann
    email                : TUhlmann@gmx.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <plainhtml.h>

SWORD_NAMESPACE_START

PLAINHTML::PLAINHTML()
{
}


char PLAINHTML::processText(SWBuf &text, const SWKey *key, const SWModule *module)
{
	int count = 0;

	SWBuf orig = text;
	const char *from = orig.c_str();
	for (text = ""; *from; from++) 
	{
		if ((*from == '\n') && (from[1] == '\n')) // two newlinea are a paragraph
		{
			text += "<P>";
			from++;
			continue;
		} else {
			if ((*from == '\n')) // && (from[1] != '\n')) // only one new line
			{
				text += "<BR>";
				continue;
			}
		}
		
		if (*from == '{') { //footnote start
			text += "<FONT COLOR=\"#80000\"><SMALL> (";
			continue;
		}
		else if (*from == '}') //footnote end
		{
			text += ") </SMALL></FONT>";
			continue;
		}
		else if ((*from == ' ') && (count > 5000))
		{
			text += "<WBR>";
			count = 0;
			continue;
		}

		text += *from;
		count++;
	}
	return 0;
}

SWORD_NAMESPACE_END
