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

#include <swmgr.h>
#include <stdio.h>


int main(int argc, char **argv)
{
	int action = 0;

	if ((argc < 4) || (argc > 6)) {
		cerr << "usage: " << argv[0] << " <mod_name> <key> <key|buf|""-delete> [0(deflt) - normal; 1 - link]\n";
		exit(-1);
	}

	if (argc > 4)
		action = atoi(argv[4]);

	SWMgr mgr;

	ModMap::iterator it = mgr.Modules.find(argv[1]);
	if (it == mgr.Modules.end()) {
		fprintf(stderr, "error: %s: couldn't find module: %s \n", argv[0], argv[1]);
		exit(-2);
	}

	SWModule *module = it->second;
	module->SetKey(argv[2]);

	switch (action) {
	case 0:
		if (strlen(argv[3]))
			(*module) << argv[3];
		else module->deleteEntry();
		break;
	case 1:
		(*module) << (SWKey)argv[3];
		break;
	default:
		cerr << "Unknown action " << action << "\n";
		exit(-3);
	}
}
