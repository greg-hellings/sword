/******************************************************************************
 *
 * gbfrtf -	SWFilter decendant to convert all GBF tags to RTF tags
 */


#include <stdlib.h>
#include <string.h>
#include <gbfrtf.h>


GBFRTF::GBFRTF() {
}


char GBFRTF::ProcessText(char *text, int maxlen)
{
	char *to, *from, token[2048];
	int tokpos = 0;
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
			memset(token, 0, 2048);
			continue;
		}
		if (*from == '>') {
			intoken = false;
						// process desired tokens
			switch (*token) {
			case 'W':	// Strongs
				switch(token[1]) {
				case 'G':               // Greek
				case 'H':               // Hebrew
					*to++ = '{';
					*to++ = '\\';
					*to++ = 'f';
					*to++ = 's';
					*to++ = '1';
					*to++ = '5';
					*to++ = ' ';
					*to++ = '<';
					for (unsigned int i = 2; i < strlen(token); i++)
						*to++ = token[i];
					*to++ = '>';
					*to++ = '}';
					continue;

				case 'T':               // Tense
					*to++ = '{';
					*to++ = '\\';
					*to++ = 'f';
					*to++ = 's';
					*to++ = '1';
					*to++ = '5';
					*to++ = ' ';
					*to++ = '(';
					for (unsigned int i = 3; i < strlen(token); i++)
						*to++ = token[i];
					*to++ = ')';
					*to++ = '}';
					continue;
				}
				break;
			case 'R':
				switch(token[1]) {
				case 'F':               // footnote begin
					*to++ = '{';
					*to++ = '\\';
					*to++ = 'i';
					*to++ = '1';
					*to++ = ' ';
					*to++ = '\\';
					*to++ = 'f';
					*to++ = 's';
					*to++ = '1';
					*to++ = '5';
					*to++ = ' ';
					*to++ = '(';
					continue;
				case 'f':               // footnote end
					*to++ = ')';
					*to++ = ' ';
					*to++ = '}';
					continue;
				}
				break;
			case 'F':			// font tags
				switch(token[1]) {
				case 'I':		// italic start
					*to++ = '\\';
					*to++ = 'i';
					*to++ = '1';
					*to++ = ' ';
					continue;
				case 'i':		// italic end
					*to++ = '\\';
					*to++ = 'i';
					*to++ = '0';
					*to++ = ' ';
					continue;
				case 'B':		// bold start
					*to++ = '\\';
					*to++ = 'b';
					*to++ = '1';
					*to++ = ' ';
					continue;
				case 'b':		// bold end
					*to++ = '\\';
					*to++ = 'b';
					*to++ = '0';
					*to++ = ' ';
					continue;
				}
				break;
			case 'C':			// special character tags
				switch(token[1]) {
				case 'A':               // ASCII value
					*to++ = (char)atoi(&token[2]);
					continue;
				case 'G':
					*to++ = '>';
					continue;
				case 'L':               // line break
					*to++ = '\\';
					*to++ = 'l';
					*to++ = 'i';
					*to++ = 'n';
					*to++ = 'e';
					*to++ = ' ';
					continue;
				case 'M':               // new paragraph
					*to++ = '\\';
					*to++ = 'p';
					*to++ = 'a';
					*to++ = 'r';
					*to++ = ' ';
					continue;
				case 'T':
					*to++ = '<';
				}
				break;
			}
			continue;
		}
		if (intoken) {
			if (tokpos < 2047)
				token[tokpos++] = *from;
		}
		else	*to++ = *from;
	}
	*to = 0;
	return 0;
}
