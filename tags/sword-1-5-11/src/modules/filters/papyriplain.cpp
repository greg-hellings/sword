/******************************************************************************
 *
 * papyriplain -	SWFilter descendant to strip out all Papyri tags
 */


#include <stdlib.h>
#include <papyriplain.h>

SWORD_NAMESPACE_START

PapyriPlain::PapyriPlain() {
}


char PapyriPlain::processText (SWBuf &text, const SWKey *key, const SWModule *module)
{
	SWBuf orig = text;
	const char *from = orig.c_str();
	
	for (text = ""; *from; ++from) {

		// remove hyphen and whitespace if that is all that separates words
		// also be sure we're not a double hyphen '--'
		if ((*from == '-') && (text.length() > 0) && (text[text.length()-1] != '-')) {
			char remove = 0;
			const char *c;
			for (c = from+1; *c; c++) {
				if ((*c == 10) || (*c == 13)) {
					remove = 1;
				}
				if (!strchr(" \t\n", *c)) {
					if (remove) remove++;
					break;
				}
			}
			if (remove > 1) {
				from = c-1;
				continue;
			}
		}

		// remove all newlines
		if ((*from == 10) || (*from == 13)) {
			if ((text.length()>1) && (text[text.length()-2] != ' ') && (*(from+1) != ' '))
				text.append(' ');
			continue;
		}

				
		// strip odd characters
		switch (*from) {
		case '(':
		case ')':
		case '[':
		case ']':
		case '{':
		case '}':
		case '<':
		case '>':
			continue;
		}

		// if we've made it this far
		text.append(*from);

	}
	return 0;
}

SWORD_NAMESPACE_END