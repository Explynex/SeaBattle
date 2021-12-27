#include <Windows.h>
#include <iostream>
#include "GotoXY.h"
#include "AI.h"
#include "newGameMenu.h"


int newGameMenu() {
	std::string Menu[4] = { " Расставить вручную\n", " Загрузить расстановку\n", " Сгенерировать случайно\n", " Вернуться в главное меню\n"};
	int point = 0;
    while (true)
    {
        system("cls");
        GotoXY(5, 1);
        std::cout << "  Меню расстановки кораблей на поле\n";
        GotoXY(5, 2);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        std::cout << "╔═══════════════════════════════════╗" << std::endl;
        for (int i = 0; i < 4; ++i)
        {
            if (i == point)
            {
                GotoXY(5, i + 3);
                std::cout << "║";
                GotoXY(41, i + 3);
                std::cout << "║";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                GotoXY(6, i + 3);
                std::cout << " >> " << Menu[i];
                GotoXY(37, i + 3);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                GotoXY(5, i + 3);
                std::cout << "║" << Menu[i];
                GotoXY(41, i + 3);
                std::cout << "║";
            }
        }
        GotoXY(5, 7);
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