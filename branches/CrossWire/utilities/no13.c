#include <fcntl.h>
#include <stdio.h>

main(int argc, char **argv)
{
	int fd, loop;
	char ch;
	char breakcnt = 0;

	if (argc != 2) {
		fprintf(stderr, "This program writes to stdout, so to be useful,\n\tit should be redirected (e.g no13 bla > bla.dat)\nusage: %s <filename>\n", argv[0]);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	while (read(fd, &ch, 1) == 1) {
		if (ch == 0x0d) {	// CR
			breakcnt++;
			continue;
		}
		if (ch == 0x1a)	// Ctrl-Z
			continue;

		if (ch != 0x0a) {	// LF
			if (breakcnt > 1) {
				for (loop = breakcnt; loop > 0; loop--)
					putchar(0x0d);
				putchar(0x0a);
			}
			breakcnt=0;
		}
		putchar(ch);
	}
	close(fd);
}
