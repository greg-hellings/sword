/******************************************************************************
 *
 * osisruby          -	SWFilter descendant to hide or show ruby
 *			in a OSIS module.
 */


#include <stdlib.h>
#include <osisruby.h>
#include <utilxml.h>

SWORD_NAMESPACE_START

const char oName[] = "Ruby";
const char oTip[] = "Toggles Ruby On and Off if they exist";

const SWBuf choices[3] = {"Off", "On", ""};
const StringList oValues(&choices[0], &choices[2]);

OSISRuby::OSISRuby() : SWOptionFilter(oName, oTip, &oValues) {
	setOptionValue("Off");
}


OSISRuby::~OSISRuby() {
}


char OSISRuby::processText(SWBuf &text, const SWKey *key, const SWModule *module) {
	SWBuf token;
	bool intoken = false;
	bool lastspace = false;

	const SWBuf orig = text;
	const char * from = orig.c_str();

	if (!option) {
		for (text = ""; *from; ++from) {
			if (*from == '<') {
				intoken = true;
				token = "";
				continue;
			}
			if (*from == '>') {	// process tokens
				intoken = false;
				if (token.startsWith("w ")) {	// Word
					XMLTag wtag(token);
					int count = wtag.getAttributePartCount("gloss", ' ');
					for (int i = 0; i < count; i++) {
						SWBuf a = wtag.getAttribute("gloss", i, ' ');
					}
					token = wtag;
					token.trim();
					// drop <>
					token << 1;
					token--;
				}
				
				// keep token in text
				text.append('<');
				text.append(token);
				text.append('>');
				
				continue;
			}
			if (intoken) {
				token += *from;
			}
			else	{
				text.append(*from);
				lastspace = (*from == ' ');
			}
		}
	}
	return 0;
}

SWORD_NAMESPACE_END