#pragma once
#ifndef _CORE_H_
#define _CORE_H_
#include "output.h"

const int sz = 12, szx = 12;

void AI(std::string mode);
void aiPlayer(char field[sz][szx]);
void fieldBoarder(char field[sz][szx]);
void hitShip(int x, int y, char field[sz][szx]);
void horOutput(int i, bool ifboarder, char field[sz][szx]);
void gameProcess();
void kletochki(int i);
int shipConstructor(char field[sz][szx]);
void shipDrown(int shipNum, char field[sz][szx]);
void randomgen(std::string whose, char genField[sz][szx]);
void shipOnfire(char field[sz][szx]);
void showField(char field[sz][szx]);
void saveInFile();
void loadFromFile();
std::string createFolders();
void gameoverchecker();
void freePosCrdFiller(COORD* freePosCrdArr);
int freePosCrdDeleter(int x, int y, COORD* freePosCrdArr, int freePosCrdAm);
void freePosCrdShow(COORD* freePosCrdArr, int freePosCrdAm);
#endif // !_CORE_H_
