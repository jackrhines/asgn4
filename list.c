#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void add_node(name_list **root, char *name, unsigned char type) {
	name_list *new = NULL, *temp = NULL, *prev = NULL;
	int comp;

	new = (name_list *)malloc(sizeof(name_list));
	new->name = name;
	new->type = type;

	if ((*root) == NULL) {
		*root = new;
		return;
	}

	temp = *root;
	while (temp != NULL) {
		if ((comp = strcmp(name, temp->name)) < 0) {
			new->next = temp;
			
			if (prev == NULL) {
				root = &temp;
			} else {
				prev->next = new;
			}
			
			return;
		}

	}
	return;
}

void print_list(name_list *root) {
	name_list *cur;
	cur = root;
	while (cur != NULL) {
		printf("name: %s, type: %c", cur->name, cur->type);
		cur = cur->next;
	}
}
