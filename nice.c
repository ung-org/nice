#define _XOPEN_SOURCE 700
#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NICE_UTILITY_NOT_FOUND		127
#define NICE_UTILITY_NOT_INVOKED	126

int main(int argc, char *argv[])
{
	int increment = 0;
	int c;

	setlocale(LC_ALL, "");

	while ((c = getopt(argc, argv, "n:")) != -1) {
		switch (c) {
		case 'n':
			increment = atoi(optarg);
			break;

		default:
			return 1;
		}
	}

	argv += optind;

	errno = 0;
	if (nice(increment) == -1 && errno != 0) {
		perror("nice");
	}

	execvp(argv[0], argv);

	perror("nice");

	if (errno == ENOENT) {
		return NICE_UTILITY_NOT_FOUND;
	}

	return NICE_UTILITY_NOT_INVOKED;
}
