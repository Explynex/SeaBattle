#pragma once
#ifndef _CORE_H_
#define _CORE_H_
const int sz = 12, szx = 12;

void AI(std::string mode);
void cleaning(int iterCount);
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
void progress(int sleeptime);
void shipCountAnim(std::string str, int posY, int shipCounter);
void gameCycle();
int gameoverchecker();
#endif // !_CORE_H_
