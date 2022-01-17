#include <Windows.h>
#include <iostream>
#include "GotoXY.h"
#include "core.h"
#include "newGameMenu.h"


int newGameMenu() {
    HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
    int height = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;
    int width = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left+1 ;
	std::string Menu[4] = { " Расставить вручную\n", " Загрузить расстановку\n", " Сгенерировать случайно\n", " Вернуться в главное меню\n"};
	int point = 0;
    while (true)
    {
        int m = 0;
        system("cls");
        GotoXY((width - 34)/2, (height - 7) / 2 + m++);
        std::cout << "Меню расстановки кораблей на поле\n";
        GotoXY((width - 38) / 2, (height - 7) / 2 + m++);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        std::cout << "╔═══════════════════════════════════╗" << std::endl;
        for (int i = 0; i < 4; ++i)
        {
            if (i == point)
            {
                GotoXY((width - 38) / 2, (height - 7) / 2 + m + i);
                std::cout << "║";
                GotoXY((width - 38) / 2+36, (height - 7) / 2 + m + i);
                std::cout << "║";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                GotoXY((width - 38) / 2+1, (height - 7) / 2 + m + i);
                std::cout << " >> " << Menu[i];
                GotoXY(width / 2 - 51, (height - 7) / 2 + m + i);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                GotoXY((width - 38) / 2, (height - 7) / 2 + m + i);
                std::cout << "║" << Menu[i];
                GotoXY((width - 38) / 2+36, (height - 7) / 2 + m + i);
                std::cout << "║";
            }
        }
        GotoXY((width - 38) / 2, (height - 7) / 2 + m + 4);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        std::cout << "╚═══════════════════════════════════╝" << std::endl;

        while (GetAsyncKeyState(VK_RETURN) == 0)
        {
            if (GetAsyncKeyState(0x57) != 0)
            {
                point -= 1;
                if (point == -1)
                {
                    point = 3;
                }
                break;
            }
            if (GetAsyncKeyState(0x53) != 0)
            {
                point += 1;
                if (point == 4)
                {
                    point = 0;
                }
                break;
            }
            else if (GetAsyncKeyState(VK_RETURN) != 0) {
                switch (point) {
                case 0: {
                    AI("constructor");
                    return 0;
                }
                case 1: {
                    AI("fromfile");
                    return 0;
                }
                case 2: {
                    AI("random");
                    return 0;
                }
                case 3: {
                    return 0;
                }
                }
            }
        }
        Sleep(110);
    }
    return 0;
}