#pragma once
#ifndef _GOTO_XY_H_
#define _GOTO_XY_H_
enum Color { Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue = 9, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };
//1366х768 1366/8.533 || 768/16
void GotoXY(int X, int Y);
void draw_progress_bar(int percents);
void setColor(Color text, Color background);
/*bool in_range(char* buff, const char* max);
bool try_input(const char* title, int& value, int minKey, int maxKey, const char* countSymb);
bool try_input_char(const char* title, char& value, int minKey, int maxKey, const char* countSymb);*/
#endif // !_GOTO_XY_H_



