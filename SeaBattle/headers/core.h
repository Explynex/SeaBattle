#pragma once
#ifndef _CORE_H_
#define _CORE_H_
const int sz = 12, szx = 12;

void AI(std::string mode);
void cleaning();
void aiPlayer(char field[sz][szx]);
void fieldBoarder(char field[sz][szx]);
void hitShip(int x, int y, char field[sz][szx]);
void horOutput(int i, bool ifboarder, char field[sz][szx]);
void kletochki(int i);
void shipConstructor(char field[sz][szx]);
void shipDrown(int shipNum, char field[sz][szx]);
void shipOnfire(char field[sz][szx]);
void showField(char field[sz][szx]);
void saveInFile();
void loadFromFile();
std::string createFolders();
#endif // !_CORE_H_
