/******************************************************************************
 *
 * gbfplain -	SWFilter decendant to strip out all GBF tags or convert to
 *		ASCII rendered symbols.
 */


#include <stdlib.h>
#include <string.h>
#include <gbfplain.h>


GBFPlain::GBFPlain() {
}


char GBFPlain::ProcessText(char *text, int maxlen)
{
	char *to, *from, token[20], tokpos = 0;
	bool intoken = false;
	int len;

	len = strlen(text) + 1;						// shift string to right of buffer
	if (len < maxlen) {
		memmove(&text[maxlen - len], text, len);
		from = &text[maxlen - len];
	}
	else	from = text;							// -------------------------------
	
	for (to = text; *from; from++) {
		if (*from == '<') {
			intoken = true;
			tokpos = 0;
			memset(token, 0, 20);
			continue;
		}
		if (*from == '>') {
			intoken = false;
						// process desired tokens
			switch (*token) {
			case 'R':
				switch(token[1]) {
				case 'F':               // footnote begin
					*to++ = ' ';
					*to++ = '(';
					continue;
				case 'f':               // footnote end
					*to++ = ')';
					*to++ = ' ';
					continue;
				}
				break;
			case 'C':
				switch(token[1]) {
				case 'A':               // ASCII value
					*to++ = (char)atoi(&token[2]);
					continue;
				case 'G':
					*to++ = '>';
					continue;
/*								Bug in WEB
				case 'L':
					*to++ = '<';
					continue;
*/
				case 'L':	//        Bug in WEB.  Use above entry when fixed
				case 'N':               // new line
					*to++ = '\n';
					continue;
				case 'M':               // new paragraph
					*to++ = '\n';
					*to++ = '\n';
					continue;
				}
				break;
			}
			continue;
		}
		if (intoken)
			token[tokpos++] = *from;
		else	*to++ = *from;
	}
	*to = 0;
	return 0;
}
