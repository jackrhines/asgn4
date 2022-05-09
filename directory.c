#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "list.h"
#include "directory.h"

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

void print_dir (char *dir_name, char *layer, int hidden, int access) {
    int n; /* Used to keep track of number of subdirectories and files */
    int i; /* Used to iterate through namelist */
    struct stat struct_stat;
    struct dirent **namelist; /* TODO: Should we malloc to allow for unlimited number of files and subdirectories? */
    char *tmp; /* Used to store temporary layer string for recursive calls */

    /* If directory doesn't exist */
    if ( lstat(dir_name, &struct_stat) == -1 ) {
        perror(dir_name);
        exit(-1);
    }

    if (((struct_stat.st_mode) & S_IFMT) == S_IFDIR) { /* Directory */

        /* Scan directory */
        if (hidden)
            n = scandir(dir_name, &namelist, NULL, dirsort);

        else
            n = scandir(dir_name, &namelist, NULL, alphasort);

        if (n < 0)
            perror("scandir");
        
        /* Print directory */
        if (layer == NULL) { /* if root directory */
            layer = ""; /* Set layer to empty for following subdirectories */
            tmp = ""; /* Set tmp layer to empty */
        }
        else { /* if NOT root directory */
            printf("%s|-- ", layer);
            tmp = strdup(layer);
            strncat(tmp, "|   ", 4); /* Add additional layer */
        }

        if (access) {
            printf("[");
            print_permissions(&struct_stat);
            printf("] ");
        }
        printf("%s\n", dir_name);

        /* Change directory to inside the current dir */
        chdir(dir_name);
        /* Print subdirectories and files recursively */
        for (i=0; i<n; i++) { 
            char *sub_name = (namelist[i])->d_name; /* TODO: Should we malloc to allow for unlimited number of files and subdirectories? */

            /* Skip . & .. and any hidden files if hidden flag is low */ 
            if ( strcmp(sub_name, ".") && strcmp(sub_name, "..")) {
                if (sub_name[0] != '.' || hidden) {
                    /* printf("Sub: %s\n", (namelist[i])->d_name); */
                    print_dir( (namelist[i])->d_name, tmp, hidden, access);
                }
            }
        }
        /* Change directory to outside the current dir */
        chdir("..");

        /* Free tmp */
        if (strcmp(tmp, "")) /* If tmp == "", space was not malloced for it */
            free(tmp);
    }
    else { /* All other file types */
        printf("%s|-- ", layer);
        if (access) {
            printf("[");
            print_permissions(&struct_stat);
            printf("] ");
        }
        printf("%s\n", dir_name);
    }

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

void print_permissions(struct stat *struct_stat) {
    /* Print file type */
    switch ((*struct_stat).st_mode & S_IFMT) {
        case S_IFBLK:  printf("b");  break;
        case S_IFCHR:  printf("c");  break;
        case S_IFDIR:  printf("d");  break;
        case S_IFIFO:  printf("p");  break;
        case S_IFLNK:  printf("l");  break;
        case S_IFREG:  printf("-");  break;
        case S_IFSOCK: printf("s");  break;
        default:       printf("$");  break;
    }

    /* Print access permissions */
    printf( ((*struct_stat).st_mode & S_IRUSR) ? "r" : "-");
    printf( ((*struct_stat).st_mode & S_IWUSR) ? "w" : "-");
    printf( ((*struct_stat).st_mode & S_IXUSR) ? "x" : "-");
    printf( ((*struct_stat).st_mode & S_IRGRP) ? "r" : "-");
    printf( ((*struct_stat).st_mode & S_IWGRP) ? "w" : "-");
    printf( ((*struct_stat).st_mode & S_IXGRP) ? "x" : "-");
    printf( ((*struct_stat).st_mode & S_IROTH) ? "r" : "-");
    printf( ((*struct_stat).st_mode & S_IWOTH) ? "w" : "-");
    printf( ((*struct_stat).st_mode & S_IXOTH) ? "x" : "-");
}


