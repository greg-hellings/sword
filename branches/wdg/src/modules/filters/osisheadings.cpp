/******************************************************************************
 *
 *osisheadings -	SWFilter descendant to hide or show headings
 *			in an OSIS module.
 */


#include <stdlib.h>
#include <osisheadings.h>
#include <swmodule.h>
#include <utilxml.h>
#include <utilstr.h>

SWORD_NAMESPACE_START

const char oName[] = "Headings";
const char oTip[] = "Toggles Headings On and Off if they exist";

const SWBuf choices[3] = {"Off", "On", ""};
const StringList oValues(&choices[0], &choices[2]);

OSISHeadings::OSISHeadings() : SWOptionFilter(oName, oTip, &oValues) {
	setOptionValue("Off");
}


OSISHeadings::~OSISHeadings() {
}


char OSISHeadings::processText(SWBuf &text, const SWKey *key, const SWModule *module) {
	SWBuf token;
	bool intoken    = false;
	bool hide       = false;
	bool preverse   = false;
	SWBuf header;
	int headerNum   = 0;
	int pvHeaderNum = 0;
	char buf[254];
	XMLTag startTag;

	SWBuf orig = text;
	const char *from = orig.c_str();
	
	XMLTag tag;

	for (text = ""; *from; ++from) {
		if (*from == '<') {
			intoken = true;
			token = "";
			
			continue;
		}
		if (*from == '>') {	// process tokens
			intoken = false;

			if (!strncmp(token.c_str(), "title", 5) || !strncmp(token.c_str(), "/title", 6)) {
				tag = token;
				
				if (!tag.isEndTag()) { //start tag
					if (!tag.isEmpty()) {
						startTag = tag;
					}
				}
				
				if (tag.getAttribute("subtype") && !stricmp(tag.getAttribute("subtype"), "x-preverse")) {
					hide = true;
					preverse = true;
					header = "";
					continue;
				}
				if (!tag.isEndTag()) { //start tag
					hide = true;
					header = "";
					if (option) {	// we want the tag in the text
						text.append('<');
						text.append(token);
						text.append('>');
					}
					continue;
				}
				if (hide && tag.isEndTag()) {
					if (module->isProcessEntryAttributes() && (option || (!preverse))) {
						if (preverse) {
							sprintf(buf, "%i", pvHeaderNum++);
							module->getEntryAttributes()["Heading"]["Preverse"][buf] = header;
						}
						else {
							sprintf(buf, "%i", headerNum++);
							module->getEntryAttributes()["Heading"]["Interverse"][buf] = header;
							if (option) {	// we want the tag in the text
								text.append(header);
							}
						}
						
						StringList attributes = startTag.getAttributeNames();
						for (StringList::const_iterator it = attributes.begin(); it != attributes.end(); it++) {
							module->getEntryAttributes()["Heading"][buf][it->c_str()] = startTag.getAttribute(it->c_str());
						}
					}
					
					hide = false;
					if (!option || preverse) {	// we don't want the tag in the text anymore
						preverse = false;
						continue;
					}
					preverse = false;
				}
			}

			// if not a heading token, keep token in text
			if (!hide) {
				text.append('<');
				text.append(token);
				text.append('>');
			}
			continue;
		}
		if (intoken) { //copy token
			token.append(*from);
		}
		else if (!hide) { //copy text which is not inside a token
			text.append(*from);
		}
		else header.append(*from);
	}
	return 0;
}

SWORD_NAMESPACE_END
