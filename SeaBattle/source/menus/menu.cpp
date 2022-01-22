#include <iostream>
#include <windows.h>
#include "newGameMenu.h"
#include "GotoXY.h"
#include "titles.h"
#include <conio.h>

BOOL ShowConsoleCursor(BOOL bShow)
{
    CONSOLE_CURSOR_INFO cci;
    HANDLE hStdOut;
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE)
        return FALSE;
    if (!GetConsoleCursorInfo(hStdOut, &cci))
        return FALSE;
    cci.bVisible = bShow;
    if (!SetConsoleCursorInfo(hStdOut, &cci))
        return FALSE;
    return TRUE;
}
void aboutgame(int height, int width)
{
    system("cls");
    setColor(Yellow, Black);
    GotoXY((width - 70) / 2+30, (height - 5) / 2 - 7);
    std::cout << "О игре.";
    setColor(White, Black);
    GotoXY((width - 70) / 2, (height - 5) / 2-6);
    std::cout << "      «Морской бой» — игра для двух участников, в которой игроки";
    GotoXY((width - 70) / 2, (height - 5) / 2 -5);
    std::cout << "по очереди называют координаты на неизвестной им карте соперника.";
    GotoXY((width - 70) / 2, (height - 5) / 2 -4);
    std::cout << "Если у соперника по этим координатам имеется корабль(координаты заняты),";
    GotoXY((width - 70) / 2, (height - 5) / 2 -3);
    std::cout << "то корабль или его часть «топится», а попавший получает право сделать ";
    GotoXY((width - 70) / 2, (height - 5) / 2 -2);
    std::cout << "ещё один ход. Цель игрока — первым потопить все корабли противника.";
    GotoXY((width - 70) / 2+32, (height - 5) / 2 );
    setColor(Yellow, Black);
    std::cout << "FAQ";
    setColor(White, Black);
    GotoXY((width - 70) / 2, (height - 5) / 2 +1);
    std::cout << " • Как добавлять корабли? - Начать новую игру и выбрать: «Расставить вручную».";
    GotoXY((width - 70) / 2+3, (height - 5) / 2 +2);
    std::cout << "После нажатия кнопки 1-4 нужно ввести координаты. Пример: «1» «J2».";
    GotoXY((width - 70) / 2, (height - 5) / 2 +3);
    std::cout << " • Как сохранить расстановку? - Расставить вручную или сгенерировать автоматически.";
    GotoXY((width - 70) / 2+3, (height - 5) / 2 +4);
    std::cout << "Нажать кнопку «y» для сохранения или «n» чтобы пропустить момент сохранения.";
    GotoXY((width - 70) / 2, (height - 5) / 2 +5);
    std::cout << " • Как загрузить расстановку? - Начать новую игру и выбрать: «Загрузить расстановку».";
    GotoXY((width - 70) / 2+3, (height - 5) / 2+6);
    std::cout << "Листать сохранения на «W,S», для загрузки - «Enter», для удаления - «Del» + «y\\n».";
    GotoXY((width - 70) / 2, (height - 5) / 2 + 7);
    std::cout << " • Для возврата в меню из «Конструктора», »Загрузчика» и «Генератора расстановок» - «Esc».";
    GotoXY((width - 70) / 2, (height - 5) / 2 + 8);
    std::cout << " • Для возврата в меню во время игры стоит написать вместо координат «00» ";
    setColor(LightRed, Black);
    GotoXY((width - 20) / 2 , (height - 5) / 2 + 10);
    std::cout << " >> Вернуться в меню";
    setColor(Black, Black);
    system("pause");

}
int menu() {
    ShowConsoleCursor(FALSE);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
    int height = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;
    int width = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
    std::string Menu[3] = { " Создать новую игру\n", " О игре\n", " Выйти\n" };
    int pointer = 0;

    while (true)
    {
        int m = 0;
        system("cls");
        GotoXY((width - 37) / 2, (height - 6) / 2 + m++);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        std::cout << "╔═══════════════════════════════════╗" << std::endl;
        for (int i = 0; i < 3; ++i)
        {
            setColor(White, Black);
            WriteTitle(width, height, "title");
            GotoXY((width - 12) / 2 - 1, (height - 6) / 2 -1);
            std::cout << "Главное меню\n";
            if (i == pointer)
            {
                GotoXY((width - 37) / 2, (height - 6) / 2 + m + i);
                std::cout << "║";
                GotoXY(width / 2 + 17, (height - 6) / 2 + m + i);
                std::cout << "║";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                GotoXY((width - 37) / 2 + 2, (height - 6) / 2 + m + i);
                std::cout << " >> " << Menu[i];
                GotoXY(width / 2 - 51, (height - 6) / 2 + m + i);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                GotoXY((width - 37) / 2, (height - 6) / 2 + m + i);
                std::cout << "║" << Menu[i];
                GotoXY(width / 2 + 17, (height - 6) / 2 + m + i);
                std::cout << "║";
            }
        }
        GotoXY((width - 37) / 2, (height - 6) / 2 + m + 3);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        std::cout << "╚═══════════════════════════════════╝" << std::endl;

        while (GetAsyncKeyState(VK_RETURN) == 0)
        {
            if (GetAsyncKeyState(0x57) != 0)
            {
                pointer -= 1;
                if (pointer == -1)
                {
                    pointer = 2;
                }
                break;
            }
            if (GetAsyncKeyState(0x53) != 0)
            {
                pointer += 1;
                if (pointer == 3)
                {
                    pointer = 0;
                }
                break;
            }
            else if (GetAsyncKeyState(VK_RETURN) != 0) {
                switch (pointer) {
                case 0: {
                    newGameMenu();
                    break;
                }
                case 1: {
                    aboutgame(height, width);
                    break;
                }
                case 2: {
                    return 0;
                }
                }
            }
        }

        Sleep(110);
    }
    return 0;
}