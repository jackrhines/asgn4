#include <dirent.h>

int dirsort(const struct dirent **, const struct dirent **);
void print_dir (char *dir_name, char *layer, char *cur_path, int hidden, int access);
