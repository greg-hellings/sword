/******************************************************************************
 *
 * thmlstrongs -	SWFilter descendant to hide or show strongs number
 *			in a ThML module.
 */


#include <stdlib.h>
#include <stdio.h>
#include <thmlstrongs.h>
#include <swmodule.h>
#ifndef __GNUC__
#else
#include <unixstr.h>
#endif
#include <ctype.h>

SWORD_NAMESPACE_START

const char oName[] = "Strong's Numbers";
const char oTip[] = "Toggles Strong's Numbers On and Off if they exist";

const SWBuf choices[3] = {"On", "Off", ""};
const StringList oValues(&choices[0], &choices[2]);

ThMLStrongs::ThMLStrongs() : SWOptionFilter(oName, oTip, &oValues) {
	setOptionValue("Off");
}


ThMLStrongs::~ThMLStrongs() {
}


char ThMLStrongs::processText(SWBuf &text, const SWKey *key, const SWModule *module) {
	char token[2048]; // cheese.  Fix.
	const char *from;
	int tokpos = 0;
	bool intoken = false;
	int len;
	bool lastspace = false;
	int word = 1;
	char val[128];
	char wordstr[5];
	char *valto;
	char *ch;
	unsigned int textStart = 0, textEnd = 0;
	SWBuf tmp;
	bool newText = false;

		SWBuf orig = text;
		from = orig.c_str();

		for (text = ""; *from; from++) {
		if (*from == '<') {
			intoken = true;
			tokpos = 0;
			token[0] = 0;
			token[1] = 0;
			token[2] = 0;
			textEnd = text.length();
			continue;
		}
		if (*from == '>') {	// process tokens
			intoken = false;
			if (!strnicmp(token, "sync type=\"Strongs\" ", 20)) {	// Strongs
				if (module->isProcessEntryAttributes()) {
					valto = val;
					for (unsigned int i = 27; token[i] != '\"' && i < 150; i++)
						*valto++ = token[i];
					*valto = 0;
					if (atoi((!isdigit(*val))?val+1:val) < 5627) {
						// normal strongs number
						sprintf(wordstr, "%03d", word++);
						module->getEntryAttributes()["Word"][wordstr]["Strongs"] = val;
						tmp = "";
						tmp.append(text.c_str()+textStart, (int)(textEnd - textStart));
						module->getEntryAttributes()["Word"][wordstr]["Text"] = tmp;
						newText = true;
					}
					else {
						// verb morph
						sprintf(wordstr, "%03d", word-1);
						module->getEntryAttributes()["Word"][wordstr]["Morph"] = val;
					}
				}

				if (!option) {	// if we don't want strongs
					if ((from[1] == ' ') || (from[1] == ',') || (from[1] == ';') || (from[1] == '.') || (from[1] == '?') || (from[1] == '!') || (from[1] == ')') || (from[1] == '\'') || (from[1] == '\"')) {
						if (lastspace)
							text--;
					}
					if (newText) {textStart = text.length(); newText = false; }
					continue;
				}
			}
			if (module->isProcessEntryAttributes()) {
				if (!strncmp(token, "sync type=\"morph\"", 17)) {
					for (ch = token+17; *ch; ch++) {
						if (!strncmp(ch, "class=\"", 7)) {
							valto = val;
							for (unsigned int i = 7; ch[i] != '\"' && i < 127; i++)
								*valto++ = ch[i];
							*valto = 0;
							sprintf(wordstr, "%03d", word-1);
							module->getEntryAttributes()["Word"][wordstr]["MorphClass"] = val;
						}
						if (!strncmp(ch, "value=\"", 7)) {
							valto = val;
							for (unsigned int i = 7; ch[i] != '\"' && i < 127; i++)
								*valto++ = ch[i];
							*valto = 0;
							sprintf(wordstr, "%03d", word-1);
							module->getEntryAttributes()["Word"][wordstr]["Morph"] = val;
						}
					}
				}
			}
			// if not a strongs token, keep token in text
			text += '<';
			text += token;
			text += '>';
			if (newText) {textStart = text.length(); newText = false; }
			continue;
		}
		if (intoken) {
			if (tokpos < 2045)
				token[tokpos++] = *from;
				token[tokpos+2] = 0;
		}
		else	{
			text += *from;
			lastspace = (*from == ' ');
		}
	}
	return 0;
}

SWORD_NAMESPACE_END