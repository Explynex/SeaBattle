#include <iostream>
#include <windows.h>
#include "newGameMenu.h"
#include "GotoXY.h"


int menu() {
    std::string Menu[3] = { " Создать новую игру\n", " Как играть\n", " Выйти\n" };
    int pointer = 0;

    while (true)
    {
        system("cls");
        GotoXY(5, 1);
        std::cout << "             Морской бой\n";
        GotoXY(5, 2);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        std::cout << "╔═══════════════════════════════════╗" << std::endl;
        for (int i = 0; i < 3; ++i)
        {
            if (i == pointer)
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
        GotoXY(5, 6);
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
                    std::cout << "\nComing soon..." << std::endl;
                    break;
                }
                case 2: {
                    return 0;
                    break;
                }
                }
            }
        }

        Sleep(110);
    }
    return 0;
}