/******************************************************************************
 *
 * UTF8GreekAccents - SWFilter decendant to remove UTF-8 Greek accents
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <utf8greekaccents.h>


const char UTF8GreekAccents::on[] = "On";
const char UTF8GreekAccents::off[] = "Off";
const char UTF8GreekAccents::optName[] = "Greek Accents";
const char UTF8GreekAccents::optTip[] = "Toggles Greek Accents";

UTF8GreekAccents::UTF8GreekAccents() {
	option = true;
	options.push_back(on);
	options.push_back(off);
}

UTF8GreekAccents::~UTF8GreekAccents(){};

void UTF8GreekAccents::setOptionValue(const char *ival)
{
	option = (!stricmp(ival, on));
}

const char *UTF8GreekAccents::getOptionValue()
{
	return (option) ? on:off;
}

char UTF8GreekAccents::ProcessText(char *text, int maxlen, const SWKey *key, const SWModule *module)
{
	if (!option) {
    unsigned char *to, *from;

	to = (unsigned char*)text;
	for (from = (unsigned char*)text; *from; from++) {
	  //first just remove combining characters
	  if (*from == 0xE2 && *(from + 1) == 0x80 && *(from + 2) == 0x99)
	    from += 2;
	  else if (*from == 0xCC && *(from + 1)) {
	    if (*(from + 1) == 0x80 || *(from + 1) == 0x81 || *(from + 1) == 0x82 || *(from + 1) == 0x88 || *(from + 1) == 0x93 || *(from + 1) == 0x94)
	      from++;
	  }
	  else if (*from == 0xCD && *(from + 1) == 0xBA)
	    from++;
	  //now converted pre-composed characters to their alphabetic bases, discarding the accents

	  //Greek
	  //capital alpha
	  else if ((*from == 0xCE && *(from + 1) == 0x86)) {
	    *to++ = 0xCE;
	    *to++ = 0x91;
	    from++;
	  }
	  //capital epsilon
	  else if ((*from == 0xCE && *(from + 1) == 0x88)) {
	    *to++ = 0xCE;
	    *to++ = 0x95;
	    from++;
	  }
	  //capital eta
	  else if ((*from == 0xCE && *(from + 1) == 0x89)) {
	    *to++ = 0xCE;
	    *to++ = 0x97;
	    from++;
	  }
	  //capital iota
	  else if ((*from == 0xCE && (*(from + 1) == 0x8A || *(from + 1) == 0xAA))) {
	    *to++ = 0xCE;
	    *to++ = 0x99;
	    from++;
	  }
	  //capital omicron
	  else if ((*from == 0xCE && *(from + 1) == 0x8C)) {
	    *to++ = 0xCE;
	    *to++ = 0x9F;
	    from++;
	  }
	  //capital upsilon
	  else if ((*from == 0xCE && (*(from + 1) == 0x8E || *(from + 1) == 0xAB))) {
	    *to++ = 0xCE;
	    *to++ = 0xA5;
	    from++;
	  }
	  //capital omega
	  else if ((*from == 0xCE && *(from + 1) == 0x8F)) {
	    *to++ = 0xCE;
	    *to++ = 0xA9;
	    from++;
	  }

	  //alpha
	  else if ((*from == 0xCE && *(from + 1) == 0xAC)) {
	    *to++ = 0xCE;
	    *to++ = 0xB1;
	    from++;
	  }
	  //epsilon
	  else if ((*from == 0xCE && *(from + 1) == 0xAD)) {
	    *to++ = 0xCE;
	    *to++ = 0xB5;
	    from++;
	  }
	  //eta
	  else if ((*from == 0xCE && *(from + 1) == 0xAE)) {
	    *to++ = 0xCE;
	    *to++ = 0xB7;
	    from++;
	  }
	  //iota
	  else if ((*from == 0xCE && *(from + 1) == 0xAF) || (*from == 0xCF && *(from + 1) == 0x8A)) {
	    *to++ = 0xCE;
	    *to++ = 0xB9;
	    from++;
	  }
	  //omicron
	  else if ((*from == 0xCF && *(from + 1) == 0x8C)) {
	    *to++ = 0xCE;
	    *to++ = 0xBF;
	    from++;
	  }
	  //upsilon
	  else if ((*from == 0xCE && *(from + 1) == 0x88) || (*from == 0xCF && (*(from + 1) == 0x8B || *(from + 1) == 0x8D))) {
	    *to++ = 0xCF;
	    *to++ = 0x85;
	    from++;
	  }
	  //omega
	  else if ((*from == 0xCF && *(from + 1) == 0x8E)) {
	    *to++ = 0xCF;
	    *to++ = 0x89;
	    from++;
	  }

	  //Extended Greek
	  //capital alpha
	  else if (*from == 0xE1 && ((*(from + 1) == 0xBC || *(from + 1) == 0xBE) && *(from + 2) >= 0x88 && *(from + 2) <= 0x8F) || (*(from + 1) == 0xBE && *(from + 2) >= 0xB8 && *(from + 2) <= 0xBC)) {
	    *to++ = 0xCE;
	    *to++ = 0x91;
	    from+=2;
	  }
	  //capital epsilon
	  else if (*from == 0xE1 && ((*(from + 1) == 0xBC && *(from + 2) >= 0x98 && *(from + 2) <= 0x9D) || (*(from + 1) == 0xBF && (*(from + 2) == 0x88 || *(from + 2) == 0x89)))) {
	    *to++ = 0xCE;
	    *to++ = 0x95;
	    from+=2;
	  }
	  //capital eta
	  else if (*from == 0xE1 && ((*(from + 1) == 0xBC && *(from + 2) >= 0xA8 && *(from + 2) <= 0xAF) || (*(from + 1) == 0xBE && *(from + 2) >= 0x98 && *(from + 2) <= 0x9F) || (*(from + 1) == 0xBF && *(from + 2) >= 0x8A && *(from + 2) <= 0x8C))) {
	    *to++ = 0xCE;
	    *to++ = 0x97;
	    from+=2;
	  }
	  //capital iota
	  else if (*from == 0xE1 && ((*(from + 1) == 0xBC && *(from + 2) >= 0xB8 && *(from + 2) <= 0xBF) || (*(from + 1) == 0xBF && *(from + 2) >= 0x98 && *(from + 2) <= 0x9B))) {
	    *to++ = 0xCE;
	    *to++ = 0x99;
	    from+=2;
	  }
	  //capital omicron
	  else if (*from == 0xE1 && ((*(from + 1) == 0xBD && *(from + 2) >= 0x88 && *(from + 2) <= 0x8D) || (*(from + 1) == 0xBF && *(from + 2) == 0xB8 || *(from + 2) == 0xB9))) {
	    *to++ = 0xCE;
	    *to++ = 0x9F;
	    from+=2;
	  }
	  //capital upsilon
	  else if (*from == 0xE1 && ((*(from + 1) == 0xBD && *(from + 2) >= 0x99 && *(from + 2) <= 0x9F) || (*(from + 1) == 0xBF && *(from + 2) >= 0xA8 && *(from + 2) <= 0xAB))) {
	    *to++ = 0xCE;
	    *to++ = 0xA5;
	    from+=2;
	  }
	  //capital omega
	  else if (*from == 0xE1 && (((*(from + 1) == 0xBD || *(from + 1) == 0xBE) && *(from + 2) >= 0xA8 && *(from + 2) <= 0xAF) || (*(from + 1) == 0xBF && *(from + 2) >= 0xBA && *(from + 2) <= 0xBC))) {
	    *to++ = 0xCE;
	    *to++ = 0xA9;
	    from+=2;
	  }
	  //capital rho
	  else if (*from == 0xE1 && *(from + 1) == 0xBF && *(from + 2) == 0xAC) {
	    *to++ = 0xCE;
	    *to++ = 0xA1;
	    from+=2;
	  }

	  //alpha
	  else if (*from == 0xE1 && ((*(from + 1) == 0xBC || *(from + 1) == 0xBE) && *(from + 2) >= 0x80 && *(from + 2) <= 0x87) || (*(from + 1) == 0xBD && (*(from + 2) == 0xB0 || *(from + 2) == 0xB1)) || (*(from + 1) == 0xBE && *(from + 2) >= 0xB0 && *(from + 2) <= 0xB7)) {
	    *to++ = 0xCE;
	    *to++ = 0xB1;
	    from+=2;
	  }
	  //epsilon
	  else if (*from == 0xE1 && ((*(from + 1) == 0xBC && *(from + 2) >= 0x90 && *(from + 2) <= 0x95) || (*(from + 1) == 0xBD && (*(from + 2) == 0xB2 || *(from + 2) == 0xB3)))) {
	    *to++ = 0xCE;
	    *to++ = 0xB5;
	    from+=2;
	  }
	  //eta
	  else if (*from == 0xE1 && ((*(from + 1) == 0xBE && *(from + 2) >= 0x90 && *(from + 2) <= 0x97) || (*(from + 1) == 0xBC && *(from + 2) >= 0xA0 && *(from + 2) <= 0xA7) || (*(from + 1) == 0xBF && *(from + 2) >= 0x82 && *(from + 2) <= 0x87) || (*(from + 1) == 0xBD && (*(from + 2) == 0xB4 || *(from + 2) == 0xB5)))) {
	    *to++ = 0xCE;
	    *to++ = 0xB7;
	    from+=2;
	  }
	  //iota
	  else if (*from == 0xE1 && ((*(from + 1) == 0xBC && *(from + 2) >= 0xB0 && *(from + 2) <= 0xB7) || (*(from + 1) == 0xBD && (*(from + 2) == 0xB6 || *(from + 2) == 0xB7)) || (*(from + 1) == 0xBF && *(from + 2) >= 0x90 && *(from + 2) <= 0x97))) {
	    *to++ = 0xCE;
	    *to++ = 0xB9;
	    from+=2;
	  }
	  //omicron
	  else if (*from == 0xE1 && (*(from + 1) == 0xBD && ((*(from + 2) >= 0x80 && *(from + 2) <= 0x85) || (*(from + 2) == 0xB8 || *(from + 2) == 0xB9)))) {
	    *to++ = 0xCE;
	    *to++ = 0xBF;
	    from+=2;
	  }
	  //upsilon
	  else if (*from == 0xE1 && ((*(from + 1) == 0xBD && ((*(from + 2) >= 0x90 && *(from + 2) <= 0x97) || *(from + 2) == 0xBA || *(from + 2) == 0xBB)) || (*(from + 1) == 0xBF && ((*(from + 2) >= 0xA0 && *(from + 2) <= 0xA3) || *(from + 2) == 0xA6 || *(from + 2) == 0xA7)))) {
	    *to++ = 0xCF;
	    *to++ = 0x85;
	    from+=2;
	  }
	  //omega
	  else if (*from == 0xE1 && ((*(from + 1) == 0xBD && ((*(from + 2) >= 0xA0 && *(from + 2) <= 0xA7) || (*(from + 2) == 0xBC || *(from + 2) == 0xBD))) || (*(from + 1) == 0xBE && (*(from + 2) >= 0xA0 && *(from + 2) <= 0xA7)) || (*(from + 1) == 0xBF && *(from + 2) >= 0xB2 && *(from + 2) <= 0xB7))) {
	    *to++ = 0xCF;
	    *to++ = 0x89;
	    from+=2;
	  }
	  //rho
	  else if (*from == 0xE1 && *(from + 1) == 0xBF && (*(from + 2) == 0xA4 && *(from + 2) == 0xA5)) {
	    *to++ = 0xCF;
	    *to++ = 0x81;
	    from+=2;
	  }
	  else
	    *to++ = *from;
	}
	*to++ = 0;
	*to = 0;
     }
	return 0;
}





