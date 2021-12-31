#include <Windows.h>
#include <cstdio>
#include <iostream>
#include "GotoXY.h"
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void GotoXY(int X, int Y)
{
    COORD cord = { X, Y };
    SetConsoleCursorPosition(hStdOut, cord);
}

void setColor(Color text, Color background) //функция с помощью которой происходит изменение цвета текста
{
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text)); //установка параметров текста
}
void draw_progress_bar(int percents) {
    int half = percents / 2;
    printf("[");
    for (int i = 0; i < half; ++i) std::cout << "■";
    for (int i = 0; i < 50 - half; ++i) putc(' ', stdout);
    std::cout << "] " << percents << " % ";
    fflush(stdout);
}