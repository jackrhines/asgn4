#define _POSIX_C_SOURCE 2 
#include <stdio.h>
#include <unistd.h>
#include "directory.h"

int main(int argc, char *argv[]) {
	int opt, i = 0;
	int hidden = 0, access = 0;

	 while ((opt = getopt(argc, argv, "al")) != -1) {
		switch (opt) {
			case 'a':
				hidden = 1;
				break;
			case 'l':
				access = 1;
				break;
		}
	}

	if (argv[optind] == NULL) {
		printf("open current directory\n");
		open_directory(".", 1, hidden, access);
	} else {
		for ( i = optind; i < argc; ++i) {
			printf("open %s\n", argv[i]);
			open_directory(argv[i], 1, hidden, access);
		}
	}


	return 0;
}