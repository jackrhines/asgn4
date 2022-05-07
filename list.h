typedef struct name_list {
	char *name;
	unsigned char type;
	struct name_list *next;
} name_list;

void add_node(name_list **root, char *name, unsigned char type);
void print_list(name_list *root);
