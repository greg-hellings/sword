/******************************************************************************
 *
 * utf8html -	SWFilter decendant to convert a UTF-8 stream to HTML escapes
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <utf8html.h>

SWORD_NAMESPACE_START

UTF8HTML::UTF8HTML() {
}


char UTF8HTML::processText(SWBuf &text, const SWKey *key, const SWModule *module)
{
	unsigned char *from;
	int len;
        char digit[10];
        unsigned long ch;
	 if ((unsigned long)key < 2)	// hack, we're en(1)/de(0)ciphering
		return -1;

	len = strlenw(text.c_str()) + 2;						// shift string to right of buffer

	SWBuf orig = text;
  	from = (unsigned char *)orig.c_str();

	// -------------------------------
	for (text = ""; *from; from++) {
	  ch = 0;
          if ((*from & 128) != 128) {
//          	if (*from != ' ')
	       text += *from;
               continue;
          }
          if ((*from & 128) && ((*from & 64) != 64)) {
	    // error
               *from = 'x';
               continue;
          }
          *from <<= 1;
          int subsequent;
          for (subsequent = 1; (*from & 128); subsequent++) {
          	*from <<= 1;
               from[subsequent] &= 63;
               ch <<= 6;
               ch |= from[subsequent];
          }
          subsequent--;
          *from <<=1;
          char significantFirstBits = 8 - (2+subsequent);
          
          ch |= (((short)*from) << (((6*subsequent)+significantFirstBits)-8));
          from += subsequent;
          text += '&';
          text += '#';
	  sprintf(digit, "%d", ch);
		for (char *dig = digit; *dig; dig++)
			text += *dig;
		text += ';';
	}
	return 0;
}

SWORD_NAMESPACE_END
