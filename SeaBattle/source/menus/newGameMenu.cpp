#include <Windows.h>
#include <iostream>
#include "GotoXY.h"
#include "core.h"
#include "newGameMenu.h"


int newGameMenu() {
	std::string Menu[4] = { " Расставить вручную\n", " Загрузить расстановку\n", " Сгенерировать случайно\n", " Вернуться в главное меню\n"};
	int point = 0;
    while (true)
    {
        system("cls");
        GotoXY(width /2 -11, height - 28);
        std::cout << "Меню расстановки кораблей на поле\n";
        GotoXY(width / 2 - 13, height - 27);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        std::cout << "╔═══════════════════════════════════╗" << std::endl;
        for (int i = 0; i < 4; ++i)
        {
            if (i == point)
            {
                GotoXY(width / 2 - 13, height - 26 + i);
                std::cout << "║";
                GotoXY(width / 2 + 23, height - 26 + i);
                std::cout << "║";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                GotoXY(width / 2 - 12, height - 26 + i);
                std::cout << " >> " << Menu[i];
                GotoXY(width / 2 - 51, height - 26 + i);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                GotoXY(width / 2 - 13, height - 26 + i);
                std::cout << "║" << Menu[i];
                GotoXY(width / 2 + 23, height - 26 + i);
                std::cout << "║";
            }
        }
        GotoXY(width / 2 - 13, height - 22);
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
                    AI();
                    return 0;
                }
                case 1: {
                    std::cout << "\nComing soon..." << std::endl;
                    break;
                }
                case 2: {
                    std::cout << "\nComing soon..." << std::endl;
                    break;
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