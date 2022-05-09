#include <sys/stat.h>
#include <dirent.h>

void open_directory(char *name, int layers, int hidden, int access);
void print_dir (char *, char *, int, int);
int dirsort(const struct dirent **, const struct dirent **);
void print_permissions(struct stat *);
