/******************************************************************************
 *
 * Latin1UTF8 -	SWFilter decendant to convert a Latin-1 character to UTF-8
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <latin1utf8.h>
#include <swmodule.h>

Latin1UTF8::Latin1UTF8() {
}


char Latin1UTF8::ProcessText(char *text, int maxlen, const SWKey *key, const SWModule *module)
{
    unsigned char *to, *from;
	int len;
	 if ((unsigned long)key < 2)	// hack, we're en(1)/de(0)ciphering
		return -1;
        len = strlen(text) + 1;
	if (len == maxlen + 1)
        	maxlen = (maxlen + 1) * FILTERPAD;
        // shift string to right of buffer
	if (len < maxlen) {
	  memmove(&text[maxlen - len], text, len);
	  from = (unsigned char*)&text[maxlen - len];
	}
	else	
	  from = (unsigned char*)text;							// -------------------------------



	for (to = (unsigned char*)text; *from; from++) {
	  if (*from < 0x80) {
	    *to++ = *from;
	  }
	  else if (*from < 0xc0) {
                switch(*from) {
        	case 0x80: // '�'
	        	*to++ = 0xe2; // '�'
		        *to++ = 0x82; // '�'
        		*to++ = 0xac; // '�'
	        	break;
        	case 0x82: // '�'
	        	*to++ = 0xe2; // '�'
		        *to++ = 0x80; // '�'
        		*to++ = 0x9a; // '�'
	        	break;
        	case 0x83: // '�'
	        	*to++ = 0xc6; // '�'
		        *to++ = 0x92; // '�'
        		break;
	        case 0x84: // '�'
		        *to++ = 0xe2; // '�'
        		*to++ = 0x80; // '�'
	        	*to++ = 0x9e; // '�'
		        break;
        	case 0x85: // '�'
	        	*to++ = 0xe2; // '�'
		        *to++ = 0x80; // '�'
        		*to++ = 0xa6; // '�'
	        	break;
        	case 0x86: // '�'
        		*to++ = 0xe2; // '�'
	        	*to++ = 0x80; // '�'
		        *to++ = 0xa0; // '�'
        		break;
	        case 0x87: // '�'
		        *to++ = 0xe2; // '�'
        		*to++ = 0x80; // '�'
	        	*to++ = 0xa1; // '�'
		        break;
        	case 0x88: // '�'
	        	*to++ = 0xcb; // '�'
		        *to++ = 0x86; // '�'
        		break;
	        case 0x89: // '�'
		        *to++ = 0xe2; // '�'
        		*to++ = 0x80; // '�'
	        	*to++ = 0xb0; // '�'
		        break;
        	case 0x8A: // '�'
	        	*to++ = 0xc5; // '�'
		        *to++ = 0xa0; // '�'
        		break;
	        case 0x8B: // '�'
		        *to++ = 0xe2; // '�'
        		*to++ = 0x80; // '�'
	        	*to++ = 0xb9; // '�'
		        break;
        	case 0x8C: // '�'
	        	*to++ = 0xc5; // '�'
		        *to++ = 0x92; // '�'
        		break;
	        case 0x8E: // '�'
		        *to++ = 0xc5; // '�'
        		*to++ = 0xbd; // '�'
	        	break;
        	case 0x91: // '�'
        		*to++ = 0xe2; // '�'
	        	*to++ = 0x80; // '�'
		        *to++ = 0x98; // '�'
        		break;
	        case 0x92: // '�'
		        *to++ = 0xe2; // '�'
        		*to++ = 0x80; // '�'
	        	*to++ = 0x99; // '�'
		        break;
        	case 0x93: // '�'
	        	*to++ = 0xe2; // '�'
		        *to++ = 0x80; // '�'
        		*to++ = 0x9c; // '�'
	        	break;
        	case 0x94: // '�'
	        	*to++ = 0xe2; // '�'
		        *to++ = 0x80; // '�'
        		*to++ = 0x9d; // '�'
	        	break;
        	case 0x95: // '�'
	        	*to++ = 0xe2; // '�'
		        *to++ = 0x80; // '�'
        		*to++ = 0xa2; // '�'
	        	break;
        	case 0x96: // '�'
	        	*to++ = 0xe2; // '�'
		        *to++ = 0x80; // '�'
        		*to++ = 0x93; // '�'
	        	break;
        	case 0x97: // '�'
	        	*to++ = 0xe2; // '�'
		        *to++ = 0x80; // '�'
        		*to++ = 0x94; // '�'
	        	break;
        	case 0x98: // '�'
	        	*to++ = 0xcb; // '�'
		        *to++ = 0x9c; // '�'
        		break;
	        case 0x99: // '�'
		        *to++ = 0xe2; // '�'
        		*to++ = 0x84; // '�'
	        	*to++ = 0xa2; // '�'
		        break;
        	case 0x9A: // '�'
	        	*to++ = 0xc5; // '�'
		        *to++ = 0xa1; // '�'
        		break;
	        case 0x9B: // '�'
		        *to++ = 0xe2; // '�'
        		*to++ = 0x80; // '�'
	        	*to++ = 0xba; // '�'
		        break;
        	case 0x9C: // '�'
	        	*to++ = 0xc5; // '�'
		        *to++ = 0x93; // '�'
        		break;
	        case 0x9E: // '�'
		        *to++ = 0xc5; // '�'
        		*to++ = 0xbe; // '�'
	        	break;
        	case 0x9F: // '�'
	        	*to++ = 0xc5; // '�'
		        *to++ = 0xb8; // '�'
        		break;
                default:
                        *to++ = 0xC2;
                        *to++ = *from;
                }
	  }
	  else {
	    *to++ = 0xC3;
	    *to++ = (*from - 0x40);
	  }
	}
	*to++ = 0;
	*to = 0;
	return 0;
}
