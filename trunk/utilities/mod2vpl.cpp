#include <swmgr.h>
#include <versekey.h>
#include <iostream.h>

void cleanbuf(char *buf) {
	char *from = buf;
	char *to = buf;

	while (*from) {
		if ((*from != 10) && (*from != 13)) {
			*to++ = *from++;
		}
		else {
			from++;
		}
	}
	*to = 0;
}

int main(int argc, char **argv) {
	char *buffer = 0;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <Mod Name> [0|1 - prepend verse reference to each line]\n", argv[0]);
		exit(-1);
	}

	SWMgr mgr;

	ModMap::iterator it = mgr.Modules.find(argv[1]);
	if (it == mgr.Modules.end()) {
		fprintf(stderr, "error: %s: couldn't find module: %s \n", argv[0], argv[1]);
		exit(-2);
	}

	bool vref = false;
	if (argc > 2)
		vref = (argv[2][0] == '0') ? false : true;


	SWModule *mod = it->second;

	SWKey *key = (*mod);
	VerseKey *vkey = 0;
	try {
		vkey = dynamic_cast<VerseKey *>(key);
	}
	catch (...) {}

	if (!vkey) {
		fprintf(stderr, "error: %s: %s module is not keyed to verses \n", argv[0], argv[1]);
		exit(-3);
	}

	vkey->Headings(1);	// turn on mod/testmnt/book/chap headings

	(*mod) = TOP;

	while (!mod->Error()) {
		buffer = new char [ strlen ((const char *)(*mod)) + 1 ];
		strcpy(buffer, (const char *)(*mod));
		cleanbuf(buffer);
		if (vref) {
			if ((strlen(buffer) > 0) && (vref)) {
				cout << (const char *)(*vkey) << " ";
				cout << buffer << "\n";
			}
		}
		else cout << buffer << "\n";

		delete [] buffer;
		(*mod)++;
	}
}
