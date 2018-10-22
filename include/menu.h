#ifndef __MENU__
#define __MENU__

struct MenuItem {
	int x;
	int y;
	int width;
	int height;
	bool initialized;
	struct MenuItem *nextItem;
};

struct MenuItem createMenuItem(int x, int y, int width, int height);

struct MenuItem * createMenu(struct MenuItem *mi[], size_t size);

#endif
