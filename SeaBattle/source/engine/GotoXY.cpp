#include <Windows.h>
void GotoXY(int X, int Y)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cord = { X, Y };
    SetConsoleCursorPosition(hStdOut, cord);
}