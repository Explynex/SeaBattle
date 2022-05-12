#pragma once
#ifndef _OUTPUT_H_
#define _OUTPUT_H_
#define _FILESYSTEM_USE_
#include "..\DevAttribute\devattribute.h"
#include <iostream>

void mainMenu();
void newGameSubMenu();
void writeTitle(short width, short height, std::string title);
void shipCountAnim(short x, short y, bool* active,short count=4);
extern short width, height;
#endif // !_MENU_H_

