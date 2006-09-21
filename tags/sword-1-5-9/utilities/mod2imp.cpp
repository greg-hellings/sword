// Compression on variable granularity

#include <fcntl.h>
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
#include <stdio.h>

#ifndef NO_SWORD_NAMESPACE
using sword::SWModule;
using sword::SWMgr;
using sword::ModMap;
using sword::SWKey;
using sword::VerseKey;
using sword::SW_POSITION;
#endif


void errorOutHelp(char *appName) {
	std::cerr << appName << " - a tool to output a Sword module in SWORD's 'imp' import format\n";
	std::cerr << "usage: "<< appName << " <modname> \n";
	std::cerr << "\n\n";
	exit(-1);
}


int main(int argc, char **argv)
{
	SWModule *inModule = 0;
	
	if ((argc != 2)) {
		errorOutHelp(argv[0]);
	}

	if ((!strcmp(argv[1], "-h")) || (!strcmp(argv[1], "--help")) || (!strcmp(argv[1], "/?")) || (!strcmp(argv[1], "-?")) || (!strcmp(argv[1], "-help"))) {
		errorOutHelp(argv[0]);
	}

	SWMgr mgr;

	ModMap::iterator it = mgr.Modules.find(argv[1]);
	if (it == mgr.Modules.end()) {
		fprintf(stderr, "error: %s: couldn't find module: %s \n", argv[0], argv[1]);
		exit(-2);
	}

	inModule = it->second;

	SWKey *key = (SWKey *)*inModule;
	VerseKey *vkey = SWDYNAMIC_CAST(VerseKey, key);

	if (vkey)
		vkey->Headings(1);

	for ((*inModule) = TOP; !inModule->Error(); (*inModule)++) {
		std::cout << "$$$" << inModule->KeyText() << std::endl;
		std::cout << inModule->getRawEntry() << std::endl;
	}
	return 0;
}

