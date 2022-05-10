#include <sys/stat.h>
#include <dirent.h>

void print_dir (char *, char *, int, int);
int dirsort(const struct dirent **, const struct dirent **);
int sort(const struct dirent **, const struct dirent **);
void print_permissions(struct stat *);
