#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <menu.h>

struct MenuItem createMenuItem (int x, int y, int width, int height) {
	struct MenuItem mi =  { .x = x, .y = y, .width = width, .height = height, .initialized = 1 };
	return mi;
}

struct MenuItem * createMenu(struct MenuItem *mi[], size_t size) {
	printf("In the createMenu function\n");
	struct MenuItem *current = mi[0];

	printf("size: %lu\n", size);
	for (int i = 1; i < size; i++) {
		current->nextItem = mi[i];
		current = current->nextItem;
	}

	return mi[0];
}
