#include <ctype.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#ifndef __GNUC__
#include <io.h>
#else
#include <unistd.h>
#endif

#include <swcrypt.h>
#include <versekey.h>
#include <rawverse.h>


main(int argc, char **argv)
{
	SWCrypt *zobj;
	VerseKey key;
	RawVerse *rawdrv;
	int ofd[2], oxfd[2];
	long offset, loffset = 0, lzoffset = 0;
	unsigned short size, lsize = 0, lzsize;
	char *tmpbuf;
	
	if (argc != 3) {
		fprintf(stderr, "usage: %s <datapath> \"<key>\"\n", argv[0]);
		exit(1);
	}

	rawdrv = new RawVerse(argv[1]);
	zobj = new SWCrypt((unsigned char *)argv[2]);

#ifndef O_BINARY
#define O_BINARY 0
#endif

	tmpbuf = new char [ strlen(argv[1]) + 11 ];
	sprintf(tmpbuf, "%sot.zzz", argv[1]);
	ofd[0] = open(tmpbuf, O_WRONLY|O_BINARY|O_CREAT);
	sprintf(tmpbuf, "%sot.zzz.vss", argv[1]);
	oxfd[0] = open(tmpbuf, O_WRONLY|O_BINARY|O_CREAT);
	sprintf(tmpbuf, "%snt.zzz", argv[1]);
	ofd[1] = open(tmpbuf, O_WRONLY|O_BINARY|O_CREAT);
	sprintf(tmpbuf, "%snt.zzz.vss", argv[1]);
	oxfd[1] = open(tmpbuf, O_WRONLY|O_BINARY|O_CREAT);

	delete [] tmpbuf;

	printf("\n");
	write(oxfd[0], &lzoffset, 4);
	write(oxfd[0], &lzsize, 2);
	write(oxfd[1], &lzoffset, 4);
	write(oxfd[1], &lzsize, 2);

	key.AutoNormalize(0);
	key.Headings(1);
	for (key.Index(0); (!key.Error()); key++) {
		rawdrv->findoffset(key.Testament(), key.Index(), &offset, &size);
		printf("%s: OLD offset: %d; size: %d\n", (const char *)key, offset, size);

		if ((offset == loffset) && (size == lsize)) {
			printf("using previous offset,size\n", size);
			write(oxfd[key.Testament() - 1], &lzoffset, 4);
			write(oxfd[key.Testament() - 1], &lzsize, 2);
		}
		else {
			lsize   = size;
			loffset = offset;

			if (size) {
				tmpbuf = (char *) calloc(size + 1, 1);
				rawdrv->gettext(key.Testament(), offset, size, tmpbuf);
				zobj->Buf(tmpbuf);
				zobj->cryptBuf((unsigned int *)&size);
				free(tmpbuf);
			}
			offset = lseek(ofd[key.Testament() - 1], 0, SEEK_END);
			printf("%s: NEW offset: %d; size: %d\n", (const char *)key, offset, size);
			write(oxfd[key.Testament() - 1], &offset, 4);
			if (size) 
				write(ofd[key.Testament() - 1], zobj->cryptBuf((unsigned int *)&size), size);
			lzoffset = offset;
			write(oxfd[key.Testament() - 1], &size, 2);
			lzsize = size;
		}
	}
	delete zobj;
}
