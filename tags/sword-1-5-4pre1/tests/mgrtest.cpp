#include <swmgr.h>
#include <iostream>
#include <versekey.h>

int main(int argc, char **argv) {
	SWMgr::debug = true;
	SWMgr mymgr;
	char keypress[2];
	std::cerr << "\n\nprefixPath: " << mymgr.prefixPath;
	std::cerr << "\nconfigPath: " << mymgr.configPath << "\n\n";


	ModMap::iterator it;

	for (it = mymgr.Modules.begin(); it != mymgr.Modules.end(); it++) {
		std::cout << "[" << (*it).second->Name() << "] (Writable: " << (it->second->isWritable()?"Yes":"No") << ") [" << (*it).second->Description() << "]\n";
		std::cout << "AbsoluteDataPath = " << it->second->getConfigEntry("AbsoluteDataPath") << "\n";
		std::cout << "Has Feature HebrewDef = " << it->second->getConfig().has("Feature", "HebrewDef") << "\n";
		if ((!strcmp((*it).second->Type(), "Biblical Texts")) || (!strcmp((*it).second->Type(), "Commentaries"))) {
			it->second->setKey("James 1:19");
			std::cout << (const char *) *(*it).second << "\n\n";
		}
	}
	SWModule *mhc = mymgr.Modules["MHC"];
	if (mhc) {
		for (mhc->Key("Gen 1:1"); mhc->Key() < (VerseKey) "Gen 1:10"; (*mhc)++)
			std::cout << (const char *) *mhc << "\n";
	}
	cin >> keypress;
	return 0;
}
