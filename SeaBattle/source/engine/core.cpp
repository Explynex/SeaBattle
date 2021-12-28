#include <iostream>
#include <windows.h>
#include "core.h"
#include "GotoXY.h"

HANDLE hConsole;
HANDLE hOut;
COORD Pos;
bool d1 = true, d2 = true, d3 = true, d4 = true, shOnfire = false;
int xOld = 0, yOld = 0, dx1 = 1, dx2 = 1, dx3 = 1, dx4 = 1, direction, currAmofShips; //точка первого попадания по кораблю если он больше
const int maxamountOfShips = 5;
const char drownSh = 'X', missed = '#', aliveSh = 'H', boarder = '*', ocean = ' ';
class ship {
public:
    int length;
    int hp;
    int x[4], y[4];
};
ship sh[5];
char fieldPlayer[sz][szx], fieldBot[sz][szx];

void fieldBoarder(char field[sz][szx]) {
    for (int i = 0; i < sz; i++)
    {
        for (int k = 0; k < szx; k++)
        {
            if (i == 0 || k == 0 || k == szx - 1 || i == sz - 1)
                field[i][k] = boarder;
            else
                field[i][k] = ocean;
        }
    }
}
void horOutput(int i, bool ifboarder, char field[sz][szx])
{
    char letter = '@';
    for (int k = 0; k < szx - 1; k++)
    {
        if (field[i][k] == boarder)
            SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        else if (field[i][k] == ocean)
            SetConsoleTextAttribute(hConsole, 240);
        else if (field[i][k] == aliveSh)
            SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        else if (field[i][k] == drownSh)
            SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_RED);
        else
            SetConsoleTextAttribute(hConsole, 240);
        if (ifboarder|| field[i][k] != boarder)
            for (int m = 0; m < 6; m++)
                std::cout << field[i][k];
        else if(boarder&&field[i][k]==boarder)
        {      
            for (int m = 0; m < 6; m++)
            {
                if (m == 3|| i / 10 > 0&&m==2)
                {
                    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    if (i != 0)
                        std::cout << i;
                    else if (k != 0)
                        std::cout << (char)(letter+k);
                    else
                        std::cout << " ";
                    if (i / 10 > 0)
                        m++;
                }
                else
                {
                    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    std::cout << field[i][k];
                }
                    
            }
        }

        if (k <= szx - 2 && k != 0)
        {
            SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            std::cout << boarder << boarder;
        }
    }

}
void kletochki(int i)
{
    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE| BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    for (int i = 0; i < szx * 6 + 14; i++)
        std::cout << boarder;
    SetConsoleTextAttribute(hConsole, 15);
    if (i != sz - 2)
        std::cout << std::endl;
}
void showField(char field[sz][szx]) {
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Pos.X = 0;
    Pos.Y = 0;
    SetConsoleCursorPosition(hOut, Pos);
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FlushConsoleInputBuffer(hConsole);
    for (int i = 0; i < sz - 1; i++)
    {
        horOutput(i, true,field);
        SetConsoleTextAttribute(hConsole, 15);
        std::cout << std::endl;
        horOutput(i, false, field);//if false - std::cout grid number
        SetConsoleTextAttribute(hConsole, 15);
        std::cout << std::endl;
        horOutput(i, true, field);
        SetConsoleTextAttribute(hConsole, 15);
        std::cout << std::endl;
        if (i != sz - 1 && i != 0)
            kletochki(i);
    }
}
void shipDrown(int shipNum, char field[sz][szx]) { //функция затопления корабля
    d1 = 1;
    d2 = 1;
    d3 = 1;
    d4 = 1;
    xOld = 0;
    yOld = 0;
    dx1 = 1;
    dx2 = 1;
    dx3 = 1;
    dx4 = 1;
    shOnfire = false;
    for (int i = 0; i < sh[shipNum].length; i++)
    {
        for (int m = -1; m <= 1; m++)
        {
            for (int n = -1; n <= 1; n++)
            {
                if (field[sh[shipNum].y[i] + m][sh[shipNum].x[i] + n] != drownSh && field[sh[shipNum].y[i] + m][sh[shipNum].x[i] + n] != boarder)
                {
                    field[sh[shipNum].y[i] + m][sh[shipNum].x[i] + n] = missed;
                }
            }
        }
    }
}
void hitShip(int x, int y, char field[sz][szx]) { //функция снятия хп у корабля при попадании
    for (int k = 0; k < maxamountOfShips; k++)
    {
        for (int i = 0; i < sh[k].length; i++)
        {
            if (sh[k].x[i] == x && sh[k].y[i] == y)
            {

                sh[k].hp--;
                //std::cout<<"Current ship hp "<<sh[k].hp<<std::endl;
                if (sh[k].hp == 0)
                {
                    //   std::cout<<"game over"<<std::endl;
                    shipDrown(k,field);
                }
            }
        }
    }
}
void shipOnfire(char field[sz][szx]) {//функция ии для продолжения боя по найденому кораблю
    int x = xOld, y = yOld;
    //  std::cout<<"Ship on fire"<<std::endl;
    while (shOnfire)
    {
        while (shOnfire) //генерация направления для нового выстрела
        {
            srand(time(NULL));
            direction = rand() % 4 + 1;
            // std::cout<<"generated dir "<<direction<<std::endl;
            if (direction == 1 && d1 && (field[yOld - dx1][xOld] != missed && field[yOld - dx1][xOld] != drownSh && field[yOld - dx1][xOld] != boarder))
            {
                y = yOld - dx1;
                break;
            }
            if (direction == 2 && d2 && (field[yOld][xOld + dx2] != missed && field[yOld][xOld + dx2] != drownSh && field[yOld][xOld + dx2] != boarder))
            {
                x = xOld + dx2;
                break;
            }
            if (direction == 3 && d3 && (field[yOld + dx3][xOld] != missed && field[yOld + dx3][xOld] != drownSh && field[yOld + dx3][xOld] != boarder))
            {
                y = yOld + dx3;
                break;
            }
            if (direction == 4 && d4 && (field[yOld][xOld - dx4] != 'M' && field[yOld][xOld - dx4] != 'D' && field[yOld][xOld - dx4] != '*'))
            {
                x = xOld - dx4;
                break;
            }
            Sleep(1000);
        }
        if (field[y][x] != aliveSh) //не попал
        {
            //  std::cout<<d1<<d2<<d3<<d4<<" "; тест направлений
            field[y][x] = missed;
            //отсеивание направлений в котором нет блоков корабля
            if (direction == 1)
                d1 = false;
            if (direction == 2)
                d2 = false;
            if (direction == 3)
                d3 = false;
            if (direction == 4)
                d4 = false;
            showField(field);
            Sleep(3000);
            // std::cout<<d1<<d2<<d3<<d4<<std::endl; тест направлений
            break;
        }
        else //попал
        {
            field[y][x] = drownSh;
            if (direction == 1 || direction == 3) //лок по х или у при попадании 
            {
                if (direction == 1)
                    dx1++;
                if (direction == 3)
                    dx3++;
                d2 = false;
                d4 = false;
            }
            else
            {
                if (direction == 2)
                    dx2++;
                if (direction == 4)
                    dx4++;
                d1 = false;
                d3 = false;
            }
            hitShip(x, y,field);
        }
        showField(field);
        Sleep(3000);
    }
}
void aiPlayer(char field[sz][szx]) //основная функция ии для боя
{
    while (true) {
        int x, y;
        if (shOnfire) //в прошлый раз попали по кораблю но не уничтожили
        {
            shipOnfire(field);
        }
        else
        {
            srand(time(NULL));
            while (true) //первый рандомный выстрел
            {
                x = rand() % (sz - 1) + 1;
                y = rand() % (sz - 1) + 1;
                if (field[y][x] != missed && field[y][x] != drownSh && field[y][x] != boarder)
                    break;
            }
            if (field[y][x] == aliveSh) //если попал
            {
                hitShip(x, y, field);
                field[y][x] = drownSh;
                xOld = x;
                yOld = y;
                shOnfire = true;
                showField(field);
                Sleep(3000);
                shipOnfire(field);

            }
            else //если не попал первым выстрелом
                field[y][x] = missed;
            showField(field);
            Sleep(3000);
        }
    }
}
void shipConstructor(char field[sz][szx]) {
    while (true) {
        system("cls");
        showField(fieldPlayer);
        GotoXY(width / 2 + 20, height / 2 - 23);
        std::cout << "█  █ ████ █  █ ████ ███ ████ █ █ █  █ ███ ████ ████";
        GotoXY(width / 2 + 20, height / 2 - 22);
        std::cout << "█ █  █  █ █  █ █  █  █  █  █ █ █ █ █   █  █  █ █  █";
        GotoXY(width / 2 + 20, height / 2 - 21);
        std::cout << "██   █  █ ████ █     █  ████ ███ ██    █  █  █ ████";
        GotoXY(width / 2 + 20, height / 2 - 20);
        std::cout << "█ █  █  █ █  █ █  █  █  █      █ █ █   █  █  █ █";
        GotoXY(width / 2 + 20, height / 2 - 19);
        std::cout << "█  █ ████ █  █ ████  █  █    ███ █  █  █  ████ █";
        GotoXY(width / 2 + 25, height / 2 - 17);
        std::cout << "	   		           ▀▀";
        GotoXY(width / 2 + 25, height / 2 - 16);
        std::cout << "█  █ ████ ████ ████ ████   ██ ███ █  █";
        GotoXY(width / 2 + 25, height / 2 - 15);
        std::cout << "█ █  █  █ █  █ █  █ █     █ █ █   █  █";
        GotoXY(width / 2 + 25, height / 2 - 14);
        std::cout << "██   █  █ ████ ████ ████ █  █ ███ █ ██";
        GotoXY(width / 2 + 25, height / 2 - 13);
        std::cout << "█ █  █  █ █    █  █ █  █ █  █ █   ██ █";
        GotoXY(width / 2 + 25, height / 2 - 12);
        std::cout << "█  █ ████ █    █  █ ████ █  █ ███ █  █";
        int length;
        char x;
        currAmofShips++;
        GotoXY(width / 2 + 20, height / 2 - 4);
        std::cout << "                                ";  //очистка ввода
        GotoXY(width / 2 + 20, height / 2 - 3);
        std::cout << "                                ";
        GotoXY(width / 2 + 20, height / 2 - 2);
        std::cout << "                                ";
        GotoXY(width / 2 + 20, height / 2 - 1);
        std::cout << "                                ";
        do {
            GotoXY(width / 2 + 20, height / 2 - 5);
            std::cout << "Введите размерность корабля:                      ";
            GotoXY(width / 2 + 49, height / 2 - 5);
            std::cin >> length;
            if (length > 4) {
                GotoXY(width / 2 + 20, height / 2 - 4);
                std::cout << "Максимальный размер корабля - 4 клетки!";
                std::cin.ignore();
                std::cin.get();
                GotoXY(width / 2 + 20, height / 2 - 4);
                std::cout << "                                         ";
            }
        } while (length > 4);
        for (int i = 0; i < length; i++)
        {
            GotoXY(width / 2 + 20, height / 2 - 4 + i);
            std::cout << "Enter x" << i << " and y" << i << " : ";
            std::cin >> x >> sh[currAmofShips - 1].y[i];
            if (x >= 65 && x <= 74)
                sh[currAmofShips - 1].x[i] = x - 64;
            else if (x >= 97 && x <= 106)
                sh[currAmofShips - 1].x[i] = x - 96;
            field[sh[currAmofShips - 1].y[i]][sh[currAmofShips - 1].x[i]] = aliveSh;
            GotoXY(width / 2 + 20, height / 2 - 4 + i);
        }
        sh[currAmofShips - 1].length = length;
        sh[currAmofShips - 1].hp = length;
        shipConstructor(fieldPlayer);
    }
}
void AI()
{
    /*HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD crd = { 100, 100 };
    SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
    SetConsoleWindowInfo(out_handle, true, &src);
    SetConsoleScreenBufferSize(out_handle, crd);
    */
    int m;
    fieldBoarder(fieldPlayer);
    fieldBoarder(fieldBot);
    fieldPlayer[5][5] = aliveSh;
    fieldPlayer[5][4] = aliveSh;
    fieldPlayer[5][3] = aliveSh;
    sh[0].length = 3;
    sh[0].hp = 3;
    sh[0].x[0] = 5;
    sh[0].y[0] = 5;
    sh[0].x[1] = 4;
    sh[0].y[1] = 5;
    sh[0].x[2] = 3;
    sh[0].y[2] = 5;
    fieldPlayer[2][5] = aliveSh;
    fieldPlayer[2][4] = aliveSh;
    fieldPlayer[2][3] = aliveSh;
    fieldPlayer[2][2] = aliveSh;
    sh[1].length = 4;
    sh[1].hp = 4;
    sh[1].x[0] = 2;
    sh[1].y[0] = 2;
    sh[1].x[1] = 3;
    sh[1].y[1] = 2;
    sh[1].x[2] = 4;
    sh[1].y[2] = 2;
    sh[1].x[3] = 5;
    sh[1].y[3] = 2;
    currAmofShips = 2;
    std::string mode;
    for (int i = 0; i <= 100; ++i) {  //рисование прогресс бара псевдо-загрузки для того чтоб картинка не накладывалась друг на друга
        GotoXY(width / 2-20, height - 20);
        draw_progress_bar(i);
        Sleep(3);
    }
    GotoXY(width / 2 - 10, height - 18);
        system("pause");
        shipConstructor(fieldPlayer);
    
}
        