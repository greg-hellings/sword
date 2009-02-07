// Compression on variable granularity

#include <iostream>
#include <fstream>
#include <string>

#ifndef __GNUC__
#include <io.h>
#else
#include <unistd.h>
#endif

#include <ztext.h>
#include <zld.h>
#include <zcom.h>
#include <swmgr.h>
#include <lzsscomprs.h>
#include <zipcomprs.h>
#include <versekey.h>
#include <thmlosis.h>
#include <stdio.h>
#include <markupfiltmgr.h>
#include <algorithm>

#ifndef NO_SWORD_NAMESPACE
using namespace sword;
#endif
using std::endl;
using std::cerr;
using std::cout;


const char *convertToOSIS(const char *inRef, const SWKey *key) {
	static std::string outRef;

	outRef = "";

	VerseKey defLanguage;
	ListKey verses = defLanguage.ParseVerseList(inRef, (*key), true);
	const char *startFrag = inRef;
	for (int i = 0; i < verses.Count(); i++) {
		VerseKey *element = SWDYNAMIC_CAST(VerseKey, verses.GetElement(i));
		char buf[5120];
		char frag[5120];
		if (element) {
			memmove(frag, startFrag, ((const char *)element->userData - startFrag) + 1);
			frag[((const char *)element->userData - startFrag) + 1] = 0;
			startFrag = (const char *)element->userData + 1;
			sprintf(buf, "%s-%s", element->LowerBound().getOSISRef(), element->UpperBound().getOSISRef());
		}
		else {
			memmove(frag, startFrag, ((const char *)verses.GetElement(i)->userData - startFrag) + 1);
			frag[((const char *)verses.GetElement(i)->userData - startFrag) + 1] = 0;
			startFrag = (const char *)verses.GetElement(i)->userData + 1;
			sprintf(buf, "%s", VerseKey(*verses.GetElement(i)).getOSISRef());
		}
		outRef+=buf;
	}
	return outRef.c_str();
}

int main(int argc, char **argv)
{
        if (argc < 2) {
        	cerr << argv[0] << " - a tool to convert verse references from English to OSIS\n";
	        cerr << "usage: "<< argv[0] << " <verse ref>\n";
        	cerr << "\n\n";
	        exit(-1);
        }
        VerseKey verseKey;
        char * verseString = new char[1024];
        *verseString = 0;
        for (int i = 1; i < argc; i++) {
                strcat (verseString, argv[i]);
                strcat (verseString, " ");
        }
        *(verseString + strlen(verseString) - 1) = 0;
        std::cout << convertToOSIS(verseString, &verseKey) << endl;

	return 0;
}
