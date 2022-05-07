#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "list.h"

void open_directory(char *name, int layers, int hidden, int access) {
	DIR *dirp;
	struct dirent *cur = NULL;
	char *temp;
	name_list *root = NULL;		

	dirp = opendir(name);
	if (dirp == NULL) {
		perror("Directory DNE");
		return;
	}

	printf("opened directory!\n");
	/* read contents of directory into a sorted linked list */	
	while ((cur = readdir(dirp)) != NULL) {
		temp = strdup(cur->d_name);	
		add_node(&root, temp, cur->d_type);
	}

	print_list(root);

	/* print directory contents in tree-like structure */

	/* close the directory! */
	return;
}
