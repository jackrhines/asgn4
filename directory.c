#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "list.h"

int dirsort(const struct dirent **a, const struct dirent **b) {
    char const *a_name = (*a)->d_name;
    char const *b_name = (*b)->d_name;    

    if ( ((*a)->d_name)[0] == '.') /* If dir a starts with . */
        a_name++;

    if ( ((*b)->d_name)[0] == '.') /* If dir b starts with . */
        b_name++;
        
    return strcoll(a_name, b_name);
}

void print_dir (char *dir_name, char *layer, char *cur_path, int hidden, int access) {
    int n; /* Used to keep track of number of subdirectories and files */
    int i; /* Used to iterate through namelist */
    /* int new_i;  Used to store new index after removing . files from dir */
    struct stat struct_stat;
    struct dirent **namelist; 
	/* TODO: Should we malloc to allow for unlimited number of files and subdirectories? */
    
	char pathbuf[256];
	char *path;
	path = strdup(cur_path);
	strncat(path, "/", 1);
	strncat(path, dir_name, strlen(dir_name));
	
	chdir(dir_name);

    getcwd(pathbuf, 256);
    printf("Current working directory: %s\n", pathbuf);

	if ( lstat(dir_name, &struct_stat) == -1 ) {
        perror(dir_name);
    	exit(-1);
	}
    if (((struct_stat.st_mode) & 61440) == 16384) { /* Directory */

        /* Scan directory */
        if (hidden)
            n = scandir(dir_name, &namelist, NULL, dirsort);

        else
            n = scandir(dir_name, &namelist, NULL, alphasort);

        if (n < 0)
            perror("scandir");

        /* Print directory */
		if (strlen(layer) > 0) {
        	printf("%s", (layer + 4));
			printf("|-- ");
		}

        /* if (access) {
 *             printf("[]")
 *                     } */
        printf("%s\n", dir_name);
        /* Print subdirectories and files recursively */
        for (i=0; i<n; i++) {
            char *sub_name = (namelist[i])->d_name;
		 /* TODO: Should we malloc to allow for unlimited number of files and subdirectories? */

            /* Skip . & .. and any hidden files if hidden flag is low */ 
            if ( strcmp(sub_name, ".") && strcmp(sub_name, "..")) {
                if (sub_name[0] != '.' || hidden) {
                    char *tmp = strdup(layer);
				 /* TODO: Should we malloc to allow for unlimited number of files and subdirectories? */
                    strncat(tmp, "|   ", 4); /* Add additional layer */
                   /*  printf("Sub: %s\n", (namelist[i])->d_name); */
                    print_dir((namelist[i])->d_name, tmp, path, hidden, access);
                    free(tmp);
                }
            }
        }
    }
    else { /* All other file types */
        printf("%s|-- %s\n", (layer + 4), dir_name);
    }
   
    return;
}
