#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
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
	chdir(name);

	printf("opened directory!\n");
	/* read contents of directory into a sorted linked list */	
	while ((cur = readdir(dirp)) != NULL) {
		/* printf("directory item: %s\n", cur->d_name);*/
		if ((strcmp(cur->d_name, ".") != 0) && (strcmp(cur->d_name, "..") != 0)) {
			temp = strdup(cur->d_name);	
			/*printf("name: %s\n", temp);*/
			add_node(&root, temp, cur->d_type);
		}
	}

	print_list(root);

	/* print directory contents in tree-like structure */
	print_tree(root, layers, hidden, access);
	/* close the directory! */
	return;
}

int dirsort(const struct dirent **a, const struct dirent **b) {
    char const *a_name = (*a)->d_name;
    char const *b_name = (*b)->d_name;    

    if ( ((*a)->d_name)[0] == '.') /* If dir a starts with . */
        a_name++;

    if ( ((*b)->d_name)[0] == '.') /* If dir b starts with . */
        b_name++;
        
    return strcoll(a_name, b_name);
}
