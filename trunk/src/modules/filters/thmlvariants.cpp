/******************************************************************************
 *
 * thmlvariants -	SWFilter decendant to hide or show textual variants
 *			in a ThML module.
 */


#include <stdlib.h>
#include <string.h>
#include <thmlvariants.h>
#ifndef __GNUC__
#else
#include <unixstr.h>
#endif

SWORD_NAMESPACE_START

const char ThMLVariants::primary[] = "Primary Reading";
const char ThMLVariants::secondary[] = "Secondary Reading";
const char ThMLVariants::all[] = "All Readings";

const char ThMLVariants::optName[] = "Textual Variants";
const char ThMLVariants::optTip[] = "Switch between Textual Variants modes";


ThMLVariants::ThMLVariants() {
	option = false;
	options.push_back(primary);
	options.push_back(secondary);
	options.push_back(all);
}


ThMLVariants::~ThMLVariants() {
}

void ThMLVariants::setOptionValue(const char *ival)
{
	if (!stricmp(ival, primary)) option = 0;
        else if (!stricmp(ival, secondary)) option = 1;
        else option = 2;
}

const char *ThMLVariants::getOptionValue()
{
        if (option == 0) {
	        return primary;
	}
	else if (option == 1) {
	        return secondary;
	}
	else {
	        return all;
	}
}

char ThMLVariants::processText(SWBuf &text, const SWKey *key, const SWModule *module)
{
        if ( option == 0 || option == 1) { //we want primary or variant only
		bool intoken = false;
		bool hide = false;
		
		SWBuf token;
		SWBuf orig = text;
		const char *from = orig.c_str();

		//we use a fixed comparision string to make sure the loop is as fast as the original two blocks with almost the same code
		const char* variantCompareString = (option == 0) ? "div type=\"variant\" class=\"1\"" : "div type=\"variant\" class=\"2\"";
		
		for (text = ""; *from; from++) {
			if (*from == '<') {
				intoken = true;
				token = "";
				continue;
			}
			else if (*from == '>') {	// process tokens
				intoken = false;
				
				if ( !strncmp(token.c_str(), variantCompareString, 28)) { //only one of the variants, length of the two strings is 28 in both cases 
					hide = true;
                                  	continue;
				}
				else if (!strncmp(token.c_str(), "/div", 4)) {
					hide = false;
                                	continue;
				}

				// if not a footnote token, keep token in text
				if (!hide) {
					text += '<';
					text.append(token);
					text += '>';
				}
				continue;
			}
			if (intoken) {
				token += *from;
			}
			else if (!hide) {
				text += *from;
			}
		}

	}
	
	//the above code should work, it combines this part in it. (jansorg)
	
/*	else if (option == 1) { //we want variant only
		bool intoken = false;
		bool hide = false;

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
				if (!strncmp(token.c_str(), "div type=\"variant\" class=\"1\"", 28)) {
				  hide = true;
                                  continue;
				}
				else if (!strncmp(token.c_str(), "/div", 4)) {
				  hide = false;
                                  continue;
				}

				// if not a footnote token, keep token in text
				if (!hide) {
					text += '<';
					text.append( token );
					text += '>';
				}
				continue;
			}
			if (intoken) {
				token += *from;
			}
			else if (!hide) {
				text += *from;
			}
		}
	}
*/

	return 0;
}






SWORD_NAMESPACE_END
