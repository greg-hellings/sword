/******************************************************************************
 *
 * thmllemma -	SWFilter descendant to hide or show lemmas
 *			in a ThML module.
 */


#include <stdlib.h>
#include <thmllemma.h>
#ifndef __GNUC__
#else
#include <unixstr.h>
#endif

SWORD_NAMESPACE_START

const char oName[] = "Lemmas";
const char oTip[] = "Toggles Lemmas On and Off if they exist";

const SWBuf choices[2] = {"On", "Off"};
const StringList oValues(&choices[0], &choices[1]);

ThMLLemma::ThMLLemma() : SWOptionFilter(oName, oTip, &oValues) {
	setOptionValue("Off");
}


ThMLLemma::~ThMLLemma() {
}


char ThMLLemma::processText(SWBuf &text, const SWKey *key, const SWModule *module) {
	if (!option) {	// if we don't want lemmas
		bool intoken = false;

		SWBuf token;
		SWBuf orig = text;
		const char *from = orig.c_str();
		for (text = ""; *from; from++) {
			if (*from == '<') {
				intoken = true;
                                token = "";
				continue;
			}
			else if (*from == '>') {	// process tokens
				intoken = false;
				if (!strnicmp(token.c_str(), "sync", 4) && strstr(token.c_str(), " type=\"lemma\"")) {	// Lemma
					continue;
				}
				
				// if not a lemma token, keep token in text
				text += '<';
                                text.append(token);
      				text += '>';
				continue;
			}
			
			if (intoken) {
				token += *from;
			}
			else {
                                text += *from;
       			}
		}
	}
	return 0;
}

SWORD_NAMESPACE_END
