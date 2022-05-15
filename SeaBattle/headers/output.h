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
void propManager(bool save = false);
void optionsSubMenu();
void timer();
extern short width, height,correctX,correctY,wins,losses;
extern std::string curdifficulty;
#endif // !_MENU_H_

