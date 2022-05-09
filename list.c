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
	new->next = NULL;

	if ((*root) == NULL) {
		*root = new;
		return;
	}

	temp = *root;
	while (temp != NULL) {

		/* compare new name to name at current spot */
		if ((comp = strcmp(name, temp->name)) < 0) {
			new->next = temp;
			
			if (prev == NULL) {
				root = &temp;
			} else {
				prev->next = new;
			}
			
			return;
		}
		prev = temp;
		temp = temp->next;
	}
	prev->next = new;
	return;
}

void print_tree(name_list *root, int layers, int hidden, int access) {
	char *base = "|   ", *indent = "", *temp = NULL;
	int count = layers - 1;

	while (count > 0) {
		temp = strcat(indent, base);
		indent = temp;
		temp = NULL;
		count--;
	}

	temp = strcat(indent, "|-- ");
	indent = temp;
	temp = NULL;

	printf("%s\n", indent);	
	

	return;
}

void print_list(name_list *root) {
	name_list *cur;
	cur = root;
	while (cur != NULL) {
		printf("name: %s, type: %d\n", cur->name, cur->type);
		cur = cur->next;
	}
}
