/******************************************************************************
 *
 * UTF8Latin1 -	SWFilter decendant to convert UTF-8 to Latin-1
 *
 */

#include <stdlib.h>
#include <stdio.h>

#include <utf8latin1.h>

SWORD_NAMESPACE_START

UTF8Latin1::UTF8Latin1(char rchar) : replacementChar(rchar) {
}


char UTF8Latin1::processText(SWBuf &text, const SWKey *key, const SWModule *module)
{
  unsigned char *from;

  int len;
  unsigned long uchar;
  unsigned char significantFirstBits, subsequent;
  
  if ((unsigned long)key < 2) {// hack, we're en(1)/de(0)ciphering
	return -1;
  }
  len = strlen(text.c_str()) + 1;						// shift string to right of buffer

  SWBuf orig = text;
  from = (unsigned char*)orig.c_str();

  
  // -------------------------------
  
  for (text = ""; *from; from++) {
    uchar = 0;
    if ((*from & 128) != 128) {
      //          	if (*from != ' ')
      uchar = *from;
    }
    else if ((*from & 128) && ((*from & 64) != 64)) {
      // error, do nothing
      continue;
    }
    else {
      *from <<= 1;
      for (subsequent = 1; (*from & 128); subsequent++) {
	*from <<= 1;
	from[subsequent] &= 63;
	uchar <<= 6;
	uchar |= from[subsequent];
      }
      subsequent--;
      *from <<=1;
      significantFirstBits = 8 - (2+subsequent);
      
      uchar |= (((short)*from) << (((6*subsequent)+significantFirstBits)-8));
      from += subsequent;
    }

    if (uchar < 0xff) {
        text += (unsigned char)uchar;
    }
    else {
        text += replacementChar;
    }
  }
  return 0;
}

SWORD_NAMESPACE_END

