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
		print_dir(".", NULL, hidden, access);
	} else {
		for ( i = optind; i < argc; ++i) {
			print_dir(argv[i], NULL, hidden, access);
		}
	}


	return 0;
}
