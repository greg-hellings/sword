/******************************************************************************
 *
 * gbfheadings -	SWFilter descendant to hide or show headings
 *			in a GBF module.
 */


#include <stdlib.h>
#include <gbfheadings.h>
#ifndef __GNUC__
#else
#include <unixstr.h>
#endif

SWORD_NAMESPACE_START


const char oName[] = "Headings";
const char oTip[] = "Toggles Headings On and Off if they exist";

const SWBuf choices[3] = {"On", "Off", ""};
const StringList oValues(&choices[0], &choices[2]);

GBFHeadings::GBFHeadings() : SWOptionFilter(oName, oTip, &oValues) {
	setOptionValue("Off");
}


GBFHeadings::~GBFHeadings() {
}


char GBFHeadings::processText (SWBuf &text, const SWKey *key, const SWModule *module) {
	if (!option) {	// if we don't want headings
		char token[2048]; // cheese.  Fix.
		int tokpos = 0;
		bool intoken = false;
		int len;
		bool hide = false;

	const char *from;
	SWBuf orig = text;
	from = orig.c_str();
	for (text = ""; *from; from++) {
			if (*from == '<') {
				intoken = true;
				tokpos = 0;
//				memset(token, 0, 2048);
				token[0] = 0;
				token[1] = 0;
				token[2] = 0;
				continue;
			}
			if (*from == '>') {	// process tokens
				intoken = false;
				switch (*token) {
				case 'T':				// Reference
					switch(token[1]) {
					case 'S':               // Begin heading
						hide = true;
						break;
					case 's':               // end heading
						hide = false;
						break;
					}
					continue;	// skip token
				}
				// if not a heading token, keep token in text
				if (!hide) {
					text += '<';
					for (char *tok = token; *tok; tok++)
						text += *tok;
					text += '>';
				}
				continue;
			}
			if (intoken) {
				if (tokpos < 2045)
					token[tokpos++] = *from;
					token[tokpos+2] = 0;
			}
			else	{
				if (!hide) {
					text += *from;
				}
			}
		}
	}
	return 0;
}

SWORD_NAMESPACE_END
