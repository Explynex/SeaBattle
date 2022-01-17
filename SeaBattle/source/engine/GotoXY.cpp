#include <Windows.h>
#include <cstdio>
#include <iostream>
#include "GotoXY.h"
#include <conio.h>
#include "newGameMenu.h"
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

bool in_range(char* buff, const char* max) 
{
    int lb = strlen(buff), lm = strlen(max);
    return (lb != lm) ? (lb < lm) : strcmp(max, buff) >= 0;
}

bool try_input(const char* title, int& value, int minKey, int maxKey, const char* countSymb) //контроль диапазона ввода
{
    char key, buffer[256] = { 0 };
    char* ptr = buffer;
    memset(buffer, 0, sizeof(buffer));

    do
    {
        printf("\r%s%s", title, buffer); // вывод на консоль того, что натыкано
        key = getch();

        if (key >= minKey && key <= maxKey)
        {
            *ptr = key; // добавление к буферу справа
            if (in_range(buffer, countSymb)) ptr++; // проверка диапазона
            else *ptr = 0; // удаление (превышен диапазон)      
        }
        if (key == VK_BACK && ptr > buffer)
        {
            *--ptr = 0;
            printf("\b ");
        }
        // ввод (enter)
        if (key == VK_RETURN && strlen(buffer))
            return (sscanf(buffer, "%d", &value));
        if (key == VK_ESCAPE) {
            return false;
        }
    } while (key != VK_ESCAPE);

    return false;
}


bool try_input_char(const char* title, char& value, int minKey, int maxKey, const char* countSymb) //контроль диапазона ввода
{
    char key, buffer[256] = { 0 };
    char* ptr = buffer;
    memset(buffer, 0, sizeof(buffer));

    do
    {
        printf("\r%s%s", title, buffer); // вывод на консоль того, что натыкано
        key = getch();

        if (key >= minKey && key <= maxKey)
        {
            *ptr = key; // добавление к буферу справа
            if (in_range(buffer, countSymb)) ptr++; // проверка диапазона
            else *ptr = 0; // удаление (превышен диапазон)      
        }
        if (key == VK_BACK && ptr > buffer)
        {
            *--ptr = 0;
            printf("\b ");
        }

        // ввод (enter)
        if (key == VK_RETURN && strlen(buffer))
            return (sscanf(buffer, "%c", &value));
    } while (key != VK_ESCAPE);

    return false;
}