/******************************************************************************
 *
 * gbffootnotes -	SWFilter decendant to hide or show footnotes
 *			in a GBF module.
 */


#include <stdlib.h>
#include <string.h>
#include <gbffootnotes.h>
#ifndef __GNUC__
#else
#include <unixstr.h>
#endif


const char GBFFootnotes::on[] = "On";
const char GBFFootnotes::off[] = "Off";
const char GBFFootnotes::optName[] = "Footnotes";


GBFFootnotes::GBFFootnotes() {
	option = false;
	options.push_back(on);
	options.push_back(off);
}


GBFFootnotes::~GBFFootnotes() {
}

void GBFFootnotes::setOptionValue(const char *ival)
{
	option = (!stricmp(ival, on));
}

const char *GBFFootnotes::getOptionValue()
{
	return (option) ? on:off;
}

char GBFFootnotes::ProcessText(char *text, int maxlen)
{
	if (!option) {	// if we don't want footnotes
		char *to, *from, token[2048]; // cheese.  Fix.
		char tokpos = 0;
		bool intoken = false;
		int len;
		bool lastspace = false;
		bool hide = false;

		len = strlen(text) + 1;	// shift string to right of buffer
		if (len < maxlen) {
			memmove(&text[maxlen - len], text, len);
			from = &text[maxlen - len];
		}
		else	from = text;	// -------------------------------

		for (to = text; *from; from++) {
			if (*from == '<') {
				intoken = true;
				tokpos = 0;
				memset(token, 0, 20);
				continue;
			}
			if (*from == '>') {	// process tokens
				intoken = false;
				if (*token == 'R') {	// Reference
					switch(token[1]) {
					case 'F':               // Begin footnote
						hide = true;
						break;
					case 'f':               // end footnote
						hide = false;
						break;
					}
					continue;	// skip token
				}
				// if not a footnote token, keep token in text
				if (!hide) {
					*to++ = '<';
					for (unsigned int i = 0; i < strlen(token); i++)
						*to++ = token[i];
					*to++ = '>';
				}
				continue;
			}
			if (intoken)
				token[tokpos++] = *from;
			else	{
				if (!hide) {
					*to++ = *from;
					lastspace = (*from == ' ');
				}
			}
		}
		*to = 0;
	}
	return 0;
}
