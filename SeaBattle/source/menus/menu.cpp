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
        GotoXY(width/2-1, height - 28);
        std::cout << "Морской бой\n";
        GotoXY(width/2-13, height - 27);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        std::cout << "╔═══════════════════════════════════╗" << std::endl;
        for (int i = 0; i < 3; ++i)
        {
            if (i == pointer)
            {
                GotoXY(width/2-13, height-26+i);
                std::cout << "║";
                GotoXY(width/2+23, height - 26 + i);
                std::cout << "║";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                GotoXY(width/2-12, height - 26 + i);
                std::cout << " >> " << Menu[i];
                GotoXY(width/2-51, height - 26 + i);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                GotoXY(width/2-13, height - 26 + i);
                std::cout << "║" << Menu[i];
                GotoXY(width/2+23, height - 26 + i);
                std::cout << "║";
            }
        }
        GotoXY(width/2-13, height - 23);
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