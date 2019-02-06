#ifndef __menu_h_LEBLANC_ONG__
#define __menu_h_LEBLANC_ONG__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*Structures */

//Action type
typedef struct {
	char* nameaction;
	void(*p)();
}action_t;

//Item type
typedef enum{
	action,
	submenu,
}itemtype;

typedef union {
	struct menu_t* itemsubmenu;
	action_t itemact;
}itemchoice;

typedef struct {
	itemtype type;
	itemchoice choice;
}item_t;

//Menu type
struct menu_t {
	struct menu_t* parentmenu;
	char* namemenu;
	item_t tab[9];
	int nb;
};

typedef struct menu_t menu_t;

/*Fonctions du Menu*/
menu_t* createMenu(const char* text);
void addMenuAction(menu_t* m, const char* text, void(*f)());
void addSubMenu(menu_t* m, menu_t* sm);
void deleteMenu(menu_t* m);
void launchMenu(menu_t* m);
void freebuffer();
void quit();

#endif