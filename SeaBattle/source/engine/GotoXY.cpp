#include <Windows.h>
#include <cstdio>
#include <iostream>
void GotoXY(int X, int Y)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cord = { X, Y };
    SetConsoleCursorPosition(hStdOut, cord);
}

void draw_progress_bar(int percents) {
    int half = percents / 2;
    printf("[");
    for (int i = 0; i < half; ++i) std::cout << "■";
    for (int i = 0; i < 50 - half; ++i) putc(' ', stdout);
    std::cout << "] " << percents << " % ";
    fflush(stdout);
}