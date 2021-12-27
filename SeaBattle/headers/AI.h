#pragma once
#ifndef _AI_H_
#define _AI_H_
const int sz = 12, szx = 12;

void AI();
void aiPlayer(char field[sz][szx]);
void fieldBoarder(char field[sz][szx]);
void hitShip(int x, int y, char field[sz][szx]);
void horOutput(int i, bool ifboarder, char field[sz][szx]);
void kletochki(int i);
void shipAdd(char field[sz][szx]);
void shipDrown(int shipNum, char field[sz][szx]);
void shipOnfire(char field[sz][szx]);
void showField(char field[sz][szx]);
#endif // !_AI_H_
