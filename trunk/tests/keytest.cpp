#include <stdio.h>
#include <iostream>
#include <versekey.h>
#include <rawtext.h>
#include <rawcom.h>
#include <echomod.h>
#include <stdlib.h>

#include <localemgr.h>

#ifndef NO_SWORD_NAMESPACE
using namespace sword;
#endif

int main(int argc, char **argv)
{
	int loop;
	int max;

	if (argc > 1)
		LocaleMgr::systemLocaleMgr().setDefaultLocaleName(argv[1]);

	VerseKey	bla;
	long index;


	if (argc < 2) 
		bla = "James    1:19";
	else	bla = argv[1];

	std::cout << "\n loop++; (.Index(Index()+1))\n";

	max = (argc < 3) ? 10 : atoi(argv[2]);

	for (loop = 0; loop < max; loop++, bla++) {
		index = bla.Index();
		std::cout << (const char *)bla << "(" << index << ")";
		bla.Index(index+1);
		std::cout << "-> " << (const char *)bla << "\n";
	}

	std::cout << "-----------------\n";
	std::cout << "\n loop--; (.Index(Index()-1))\n";
	if (argc < 2) 
		bla = "James    1:19";
	else	bla = argv[1];

	for (loop = max; loop; loop--, bla--) {
		index = bla.Index();
		std::cout << (const char *)bla << "(" << index << ")";
		bla.Index(index-1);
		std::cout << "-> " << (const char *)bla << "\n";
	}

	std::cout << "-----------------\n";
	std::cout << "--------- No Headings --------\n";

	if (argc < 2) 
		bla = "Matthew  1:5";
	else	bla = argv[1];

	for (loop = max; loop; loop--, bla--) {
		index = bla.Index();
		std::cout << (const char *)bla << "(" << index << ")\n";
	}

	std::cout << "-----------------\n";

	if (argc < 2) 
		bla = "Genesis  1:5";
	else	bla = argv[1];

	for (loop = max; loop; loop--, bla--) {
		index = bla.Index();
		std::cout << (const char *)bla << "(" << index << ")\n";
	}

	std::cout << "-----------------\n";

	if (argc < 2) 
		bla = "Malachi  4:2";
	else	bla = argv[1];

	for (loop = max; loop; loop--, bla++) {
		index = bla.Index();
		std::cout << (const char *)bla << "(" << index << ")\n";
	}

	std::cout << "-----------------\n";

	if (argc < 2) 
		bla = "Revelation of John  22:17";
	else	bla = argv[1];

	for (loop = max; loop; loop--, bla++) {
		index = bla.Index();
		std::cout << (const char *)bla << "(" << index << ")\n";
	}


	std::cout << "-----------------\n";
	std::cout << "-------- Headings ---------\n";

	bla.Headings(1);

	if (argc < 2) 
		bla = "Matthew  1:5";
	else	bla = argv[1];

	for (loop = max; loop; loop--, bla--) {
		index = bla.Index();
		std::cout << (const char *)bla << "(" << index << ")\n";
	}

	std::cout << "-----------------\n";

	if (argc < 2) 
		bla = "Genesis  1:5";
	else	bla = argv[1];

	for (loop = max; loop; loop--, bla--) {
		index = bla.Index();
		std::cout << (const char *)bla << "(" << index << ")\n";
	}

	std::cout << "-----------------\n";

	if (argc < 2) 
		bla = "Malachi  4:2";
	else	bla = argv[1];

	for (loop = max; loop; loop--, bla++) {
		index = bla.Index();
		std::cout << (const char *)bla << "(" << index << ")\n";
	}

	std::cout << "-----------------\n";

	if (argc < 2) 
		bla = "Revelation of John  22:17";
	else	bla = argv[1];

	for (loop = max; loop; loop--, bla++) {
		index = bla.Index();
		std::cout << (const char *)bla << "(" << index << ")\n";
	}

	std::cout << "\n\n";

	std::cout << "-------- Error Check ------------\n\n";
	bla = "Revelation of John 23:19";
	std::cout << "bla = \"Revelation of John 23:19\"\n";
	std::cout << "(const char *)bla = " << (const char *)bla << "\n";
	std::cout << "bla.Error() = " << (int)bla.Error() << " \n";
	std::cout << "bla++ \n";
	bla++;
	std::cout << "bla.Error() = " << (int)bla.Error() << " \n";

	bla.Headings(0);
	for (bla = BOTTOM; !bla.Error(); bla.Book(bla.Book()-1))
		std::cout << (const char *)bla << "\n";
	bla.Testament(1);
	bla = BOTTOM;
	std::cout << bla.Index() << "\n";
	std::cout << bla.NewIndex() << "\n";
	std::cout << bla << "\n";
	bla.Testament(2);
	bla = BOTTOM;
	std::cout << bla.Index() << "\n";
	std::cout << bla.NewIndex() << "\n";
	std::cout << bla << "\n";
	return 0;
}
