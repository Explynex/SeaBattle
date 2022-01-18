#include <iostream>
#include <windows.h>
#include <fstream>  
#include "core.h"
#include "GotoXY.h"
#include <Lmcons.h>
#include <filesystem>
#include "newGameMenu.h"
#include <thread>
#include <future>
#include <mutex>


HANDLE hConsole;
HANDLE hOut;
COORD Pos;

bool ExitFlag = false;
int  someVariable = 0;
std::mutex threadMutex;

int width, height;
bool d1 = true, d2 = true, d3 = true, d4 = true, shOnfire = false, player = false;
int xOld = 0, yOld = 0, dx1 = 1, dx2 = 1, dx3 = 1, dx4 = 1, direction, currAmofShips=0; //точка первого попадания по кораблю если он больше
const int maxamountOfShips = 10;
const char aroundSh = '.', drownSh = 'X', missed = '#', aliveSh = 'H', boarder = '*', ocean = ' ';
class ship {
public:
    int length = { 0 };
    int hp=0;
    int x[4], y[4];
};
ship sh[maxamountOfShips * 2], shgen[maxamountOfShips];
char fieldPlayer[sz][szx], fieldBot[sz][szx],genField[sz][sz];


void humanPlayer()
{
    int m = 0;
    player = true;
    showField(fieldBot);
    GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + m++);
    std::cout << "                    ██ ██ ████  ███                  ";
    GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + m++);
    std::cout << "                     ███  █  █  █ █                  ";
    GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + m++);
    std::cout << "                      █   █  █  █ █                  ";
    GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + m++);
    std::cout << "                     ███  █  █ █████                 ";
    GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + m++);
    std::cout << "                    ██ ██ ████ █   █                 ";
    GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + m++);
    std::cout << "                                                     ";
    GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + m++);
    std::cout << "         █  █ ███ ████ ████ █  █ ████                         ";
    GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + m++);
    std::cout << "         █  █ █   █  █ █  █ █ █  █  █                    ";
    GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + m++);
    std::cout << "         █ ██ █   ████ █  █ ██   ████                    ";
    GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + m++);
    std::cout << "         ██ █ █   █    █  █ █ █  █  █                         ";
    GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + m++);
   // GotoXY(width / 2 + 24, height / 2 - 12);
    std::cout << "         █  █ █   █    ████ █  █ █  █                    ";
    GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + m++);
    std::cout << "                                                         ";
    char x;
    int y, x1;
    while (true)
    {

        GotoXY((width - 142) / 2 + 95, (height - 43) / 2 + m+6);
        //GotoXY(width / 2 + 20, height / 2 - 5);
        std::cout << "Координаты выстрела:                      ";
        GotoXY((width - 142) / 2 + 116, (height - 43) / 2 + m + 6);
        //GotoXY(width / 2 + 41, height / 2 - 5);
        std::cin >> x >> y;
        x1 = x - '@';
        if (x1 > 10)
            x1 = x1 - 32;
        if (fieldBot[y][x1] == aliveSh)
        {
            fieldBot[y][x1] = drownSh;
            hitShip(x1, y, fieldBot);
            showField(fieldBot);
        }
        else
        {
            GotoXY((width - 142) / 2 + 116, (height - 43) / 2 + m + 6);
            std::cout << "Промах!";
            fieldBot[y][x1] = missed;
            showField(fieldBot);
            break;
        }
    }
}
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
            setColor(LightBlue, LightBlue);
        else if (field[i][k] == ocean || field[i][k] == aliveSh && player)
            setColor(White, White);
        else if (field[i][k] == aliveSh)
            setColor(LightGreen, LightGreen);
        else if (field[i][k] == drownSh)
            setColor(Red, Red);
        else
            SetConsoleTextAttribute(hConsole, 240);
        if (ifboarder || field[i][k] != boarder)
            for (int m = 0; m < 6; m++)
                std::cout << field[i][k];
        else if (boarder && field[i][k] == boarder)
        {
            for (int m = 0; m < 6; m++)
            {
                if (m == 3 || i / 10 > 0 && m == 2)
                {
                    setColor(White, LightBlue);
                    if (i != 0)
                        std::cout << i;
                    else if (k != 0)
                        std::cout << (char)(letter + k);
                    else
                        std::cout << " ";
                    if (i / 10 > 0)
                        m++;
                }
                else
                {
                    setColor(LightBlue, LightBlue);
                    std::cout << field[i][k];
                }

            }
        }

        if (k <= szx - 2 && k != 0)
        {
            setColor(LightBlue, LightBlue);
            std::cout << boarder << boarder;
        }
    }

}
void kletochki(int i)
{
    setColor(LightBlue, LightBlue);
    for (int i = 0; i < szx * 6 + 14; i++)
        std::cout << boarder;
    SetConsoleTextAttribute(hConsole, 15);
    if (i != sz - 2)
        std::cout << std::endl;
}
void showField(char field[sz][szx]) {
    int m=0;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //Pos.X = (width-150)/2;
    //Pos.Y = (height - 45) / 2;
    //SetConsoleCursorPosition(hOut, Pos);
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FlushConsoleInputBuffer(hConsole);
    for (int i = 0; i < sz - 1; i++)
    {
        GotoXY((width-142)/2,(height - 43) / 2+m++);
        horOutput(i, true, field);
        SetConsoleTextAttribute(hConsole, 15);
      //  std::cout << std::endl;
        GotoXY((width - 142) / 2, (height - 43) / 2 + m++);
        horOutput(i, false, field);//if false - std::cout grid number
        SetConsoleTextAttribute(hConsole, 15);
      //  std::cout << std::endl;
        GotoXY((width - 142) / 2, (height - 43) / 2 + m++);
        horOutput(i, true, field);
        SetConsoleTextAttribute(hConsole, 15);
      //  std::cout << std::endl;
        if (i != sz - 1 && i != 0)
        {
            GotoXY((width - 142) / 2, (height - 43) / 2 + m++);
            kletochki(i);
        }
            
    }
}
void shipDrown(int shipNum, char field[sz][szx]) { //функция затопления корабля
    if (!player)
    {
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
    }
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
    if (!player)
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
                        shipDrown(k, field);
                    }
                }
            }
        }
    else
        for (int k = maxamountOfShips; k < maxamountOfShips * 2; k++)
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
                        shipDrown(k, field);
                    }
                }
            }
        }
}
void shipOnfire(char field[sz][szx]) {//функция ии для продолжения боя по найденому кораблю
    int x = xOld, y = yOld;
    //  std::cout<<"Ship on fire"<<std::endl;
    player = false;
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
            hitShip(x, y, field);
        }
        showField(field);
        Sleep(3000);
    }
    if (!shOnfire)
        aiPlayer(field);
}
void aiPlayer(char field[sz][szx]) //основная функция ии для боя
{
    int m = 0;
    setColor(White, Black);
    GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + m++);
    std::cout << "                    ██ ██ ████  ███                  ";
    GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + m++);
    std::cout << "                     ███  █  █  █ █                  ";
    GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + m++);
    std::cout << "                      █   █  █  █ █                  ";
    GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + m++);
    std::cout << "                     ███  █  █ █████                 ";
    GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + m++);
    std::cout << "                    ██ ██ ████ █   █                 ";
    GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + m++);
    std::cout << "                                                     ";
    GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + m++);
    std::cout << "█  █ ████ █   █ ████ █    █  ██  ███ ███ ████ ████     ";
    GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + m++);
    std::cout << "█ █  █  █ ██ ██ █  █ █    █ █  █  █  █   █  █ █  █     ";
    GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + m++);
    std::cout << "██   █  █ █ █ █ █  █ ████ ████ █  █  ███ ████ ████     ";
    GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + m++);
    std::cout << "█ █  █  █ █   █ █  █ █  █ █ █  █  █  █   █    █  █     ";
    GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + m++);
    std::cout << "█  █ ████ █   █ █  █ ████ █  ██   █  ███ █    █  █     ";
    GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + m++);
    std::cout << "                                                         ";

    player = false;
    showField(field);
    int x, y;
    if (shOnfire) //в прошлый раз попали по кораблю но не уничтожили
    {
        GotoXY((width - 142) / 2 + 95, (height - 43) / 2 + m + 6);
        std::cout << "Ожидание хода компьютера...       ";
        shipOnfire(field);
    }
    else
    {
        m:srand(time(NULL));
        while (true) //первый рандомный выстрел
        {
            GotoXY((width - 142) / 2 + 95, (height - 43) / 2 + m +6);
            std::cout << "Ожидание хода компьютера...       ";
            cleaning();
            Sleep(1000);
            x = rand() % (sz - 1) + 1;
            y = rand() % (sz - 1) + 1;
            if (field[y][x] != missed && field[y][x] != drownSh && field[y][x] != boarder)
                break;
        }
        if (field[y][x] == aliveSh) //если попал
        {
            field[y][x] = drownSh;
            xOld = x;
            yOld = y;
            shOnfire = true;
            hitShip(x, y, field);
            showField(field);
            Sleep(1000);
            shipOnfire(field);
            if (!shOnfire)
            {
                goto m;
            }

        }
        else //если не попал первым выстрелом
            field[y][x] = missed;
        Sleep(1000);
        showField(field);
    }
}
void shipConstructor(char field[sz][szx]) {
    char choice;
    int length,counter1 = 0, counter2 = 0, counter3 = 0, counter4 = 0,m;
    for (int counter = 0; counter < 2; counter++) {
        system("cls");
        showField(fieldPlayer);
        m = 0;
        GotoXY((width-142)/2 + 94, (height-43)/2+m++);
        std::cout << "█  █ ████ █  █ ████ ███ ████ █ █ █  █ ███ ████ ████";
        GotoXY((width - 142) / 2 + 94, (height - 43) / 2 + m++);
        std::cout << "█ █  █  █ █  █ █  █  █  █  █ █ █ █ █   █  █  █ █  █";
        GotoXY((width - 142) / 2 + 94, (height - 43) / 2 + m++);
        std::cout << "██   █  █ ████ █     █  ████ ███ ██    █  █  █ ████";
        GotoXY((width - 142) / 2 + 94, (height - 43) / 2 + m++);
        std::cout << "█ █  █  █ █  █ █  █  █  █      █ █ █   █  █  █ █";
        GotoXY((width - 142) / 2 + 94, (height - 43) / 2 + m++);
        std::cout << "█  █ ████ █  █ ████  █  █    ███ █  █  █  ████ █";
        m++;
        GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + m++);
        std::cout << "	   		           ▀▀";
        GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + m++);
        std::cout << "█  █ ████ ████ ████ ████   ██ ███ █  █";
        GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + m++);
        std::cout << "█ █  █  █ █  █ █  █ █     █ █ █   █  █";
        GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + m++);
        std::cout << "██   █  █ ████ ████ ████ █  █ ███ █ ██";
        GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + m++);
        std::cout << "█ █  █  █ █    █  █ █  █ █  █ █   ██ █";
        GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + m++);
        std::cout << "█  █ ████ █    █  █ ████ █  █ ███ █  █";
        char x;
        cleaning();
        currAmofShips++;
            do {
             m: setColor(White, Black);
                GotoXY((width - 142) / 2 + 96, (height - 43) / 2+10+m);
                if (try_input("\t\t\t\t\t\t\t\t\t\t\t\t\t\tВведите размерность корабля: ", length, 49, 52, "4") == false) {
                    newGameMenu();
                    return;
                }
                cleaning();
                if (length==1 && counter1 > 3) { //проверка количества корабликов размерности 1
                    GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + 10 + m);
                    setColor(LightRed, Black);
                    std::cout << "Максимальное количество кораблей размерностью 1 - 4 шт.\n";
                    Sleep(1500);
                    cleaning();
                    goto m; //если проверка не прошла возвращаемся в начало
                }
                else if (length == 1) {//если проверка прошла то ++ к счетчику корабликов 1
                    counter1++;
                }
                if (length == 2 && counter2 > 2) { //проверка количества корабликов размерности 2
                    GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + 10 + m);
                    setColor(LightRed, Black);
                    std::cout << "Максимальное количество кораблей размерностью 2 - 3 шт.\n";
                    Sleep(1500);
                    cleaning();
                    goto m; //если проверка не прошла возвращаемся в начало
                }
                else if (length == 2) {//если проверка прошла то ++ к счетчику корабликов 2
                    counter2++;
                }
                if (length == 3 && counter3 > 1) { //проверка количества корабликов размерности 3
                    GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + 10 + m);
                    setColor(LightRed, Black);
                    std::cout << "Максимальное количество кораблей размерностью 3 - 2 шт.\n";
                    Sleep(1500);
                    cleaning();
                    goto m; //если проверка не прошла возвращаемся в начало
                }
                else if (length == 3) {//если проверка прошла то ++ к счетчику корабликов 3
                    counter3++;
                }
                if (length == 4 && counter4 > 0) { //проверка количества корабликов размерности 3
                    GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + 10 + m);
                    setColor(LightRed, Black);
                    std::cout << "Максимальное количество кораблей размерностью 4 - 1 шт.\n";
                    Sleep(1500);
                    cleaning();
                    goto m; //если проверка не прошла возвращаемся в начало
                }
                else if (length == 4) {//если проверка прошла то ++ к счетчику корабликов 3
                    counter4++;
                }
            } while (length > 4 || length != 1 && length != 2 && length != 3 && length != 4);
        for (int i = 0; i < length; i++)
        {
        n: setColor(White, Black);
                GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + 10 + m + i);
                std::cout << "Enter x" << i << " and y" << i << " :                                ";
                GotoXY((width - 142) / 2 + 117, (height - 43) / 2 + 10 + m + i);
                std::cin >> x >> sh[currAmofShips - 1].y[i];
                    if (x >= 65 && x <= 74)
                        sh[currAmofShips - 1].x[i] = x - 64;
                    else if (x >= 97 && x <= 106)
                        sh[currAmofShips - 1].x[i] = x - 96;
                    if (field[sh[currAmofShips - 1].y[i]][sh[currAmofShips - 1].x[i]] == ocean) {
                        field[sh[currAmofShips - 1].y[i]][sh[currAmofShips - 1].x[i]] = aliveSh;
                    }
                    else if( field[sh[currAmofShips - 1].y[i]][sh[currAmofShips - 1].x[i]] != ocean || std::cin.fail()) { // проверка правильности ввода 
                        std::cin.clear();
                        std::cin.ignore(32767, '\n');
                        
                        GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + 22);
                        std::cout << "                                                                       ";
                        showField(fieldPlayer);
                        setColor(LightRed, Black);
                        GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + 10 + m + i);
                        std::cout << "Ошибка! Некорректные данные.\n";
                        Sleep(1000);
                        cleaning();
                        goto n;
                    }
        }
        sh[currAmofShips - 1].length = length;
        sh[currAmofShips - 1].hp = length;
    }
    showField(fieldPlayer);
    cleaning();
    GotoXY(width / 2 + 28, height / 2);
    try_input_char("\t\t\t\t\t\t\t\t\t\t\t\t\t\tСохранить расстановку? y / n: ", choice, 49, 130, "z");
    GotoXY(width / 2 + 56, height / 2);
    switch (choice) {
    case'y':
        saveInFile();
        break;
    case'Y':
        saveInFile();
        break;
    }
    cleaning();
    showField(fieldPlayer);
        while (true) {
        aiPlayer(fieldPlayer);
        Sleep(1500);
        humanPlayer();
        Sleep(1500);
    }
}
void saveInFile() { //сохранениие поля игрока в файл
    std::string name;
    do {
        GotoXY(width / 2 + 28, height / 2 + 1);
        setColor(White, Black);
        std::cout << "Название файла:                          ";
        GotoXY(width / 2 + 44, height / 2 + 1);
        std::cin >> name;
        if (size(name) > 12) {
            GotoXY(width / 2 + 28, height / 2 + 1);
            setColor(LightRed, Black);
            std::cout << "Слишком длинное название!                        ";
            Sleep(1000);
        }
    } while (size(name) > 12);
    std::string name1 = name + ".save";
    std::ofstream fout(createFolders()+"\\Saves\\" + name1);
    char x;
    for (int i = 0; i < maxamountOfShips; i++)
    {
        fout << sh[i].length<<" ";
        for (int j = 0; j < sh[i].length; j++)
        {
            x = sh[i].x[j] + 64;
            fout << x << sh[i].y[j];
        }
        fout<<" ";
    }
    GotoXY(width / 2 + 28, height / 2 + 2);
    setColor(LightGreen, Black);
    std::cout << "Сохранено под названием: " << name << ".save";
    Sleep(2000);
}
std::string createFolders() {
    char buff[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetUserName(buff, &username_len);
    std::string userName = buff;
    std::string folderPath = "C:\\Users\\" + userName + "\\Documents\\SeaBattle";
    CreateDirectory(data(folderPath), NULL);
    std::string savePath = folderPath + "\\Saves\\";
    CreateDirectory(data(savePath), NULL);
    return folderPath;
}
std::vector<std::string> file_name_list(const std::string& path_to_dir)
{
    namespace fs = std::filesystem;

    if (fs::is_directory(path_to_dir))
    {
        std::vector<std::string> file_names;

        for (const auto& entry : fs::directory_iterator(path_to_dir))
            if (entry.is_regular_file()) file_names.push_back(fs::absolute(entry.path()).string());

        return file_names;
    }

    else return {};
}
std::string Sub(const std::string& s1, const std::string& s2)
{
    int pos1 = s1.find(s2);

    std::string res = s1.substr(0, pos1 - 1) + s1.substr(pos1 + s2.size(), std::string::npos);

    return res;
}
void loadFromFile() { //загрузка
        system("cls");
        char x;
        char buff[UNLEN + 1];
        DWORD username_len = UNLEN + 1;
        GetUserName(buff, &username_len);
        std::string userName = buff;
        std::string name;
        const std::string directory = "C:\\Users\\"+userName+"\\Documents\\SeaBattle\\Saves";
        int counter = 0;
        GotoXY(1, 1);
        std::cout << "╔══════════════════════╗";
        GotoXY(1, 2);
        std::cout << "║  Список сохранений   ║";
        GotoXY(1, 3);
        std::cout << "╠══════════════════════╣";
        for (std::string& fname : file_name_list(directory)) {
            counter++;
            std::string del = userName;
            std::string del1 = "Users";
            std::string del2 = "SeaBattle";
            std::string del3 = "Documents";
            std::string del4 = ":";
            std::string del5 = "Saves";
            std::string del6 = "save";
            fname = Sub(fname, del);
            fname = Sub(fname, del5);
            fname = Sub(fname, del2);
            fname = Sub(fname, del3);
            fname = Sub(fname, del1);
            fname = Sub(fname, del4);
            fname = Sub(fname, del6);
            if (counter < 10) {
                GotoXY(5, 3 + counter);
                std::cout << fname << '\n';
                GotoXY(24, 3 + counter);
                std::cout << "║";
            }
            else if (counter >= 10 && counter <= 40) {
                GotoXY(6, 3 + counter);
                std::cout << fname << '\n';
                GotoXY(24, 3 + counter);
                std::cout << "║";
            }
            GotoXY(1, 3 + counter);
            std::cout << "║ " << counter << ". ";
        }
        GotoXY(1, 4 + counter);
        std::cout << "╚══════════════════════╝";
        std::ifstream fin;
        do {
            setColor(White, Black);
            GotoXY(3, 5 + counter);
            std::cout << "Введите название:                      ";
            GotoXY(21, 5 + counter);
            std::cin >> name;
            fin.open(createFolders() + "\\Saves\\" + name + ".save");
            if (!fin.is_open())
            {
                GotoXY(3, 5 + counter);
                setColor(LightRed, Black);
                std::cout << "Ошибка открытия файла!";
                Sleep(1000);
            }
        } while (!fin.is_open());
        for (int i = 0; i < maxamountOfShips; i++)
        {
            fin >> sh[i].length;
            sh[i].hp = sh[i].length;
            for (int j = 0; j < sh[i].length; j++)
            {
                fin >> x >> sh[i].y[j];
                if (x >= 65 && x <= 74)
                    sh[i].x[j] = x - 64;
                else if (x >= 97 && x <= 106)
                    sh[i].x[j] = x - 96;
                fieldPlayer[sh[i].y[j]][sh[i].x[j]] = aliveSh;
            }
        }
        GotoXY(3, 6 + counter);
        setColor(LightGreen, Black);
        std::cout << "Расстановка '" << name << "' успешно загружена.Начало игры...";
        setColor(White, Black);
        Sleep(1000);
        system("cls");
        while (!false) {
            aiPlayer(fieldPlayer);
            Sleep(1500);
            humanPlayer();
            Sleep(1500);
        }
    
}
void cleaning() {
    GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + 22 );
    std::cout << "                                                               ";  //очистка ввода
    GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + 23);
    std::cout << "                                            ";
    GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + 24);
    std::cout << "                                            ";
    GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + 25);
    std::cout << "                                            ";
}
void randFieldIntegratorBot()
{
    for (int i = 0; i < sz; i++)
    {
        for (int k = 0; k < sz; k++)
        {
            if (genField[i][k] == aroundSh)
                genField[i][k] = ocean;
            fieldBot[i][k] = genField[i][k];
        }
    }
    for (int i = 10; i < 20; i++)
    {
        sh[i].length = shgen[i - 10].length;
        sh[i].hp = shgen[i - 10].length;
        for (int k = 0; k < shgen[i - 10].length; k++)
        {
            sh[i].x[k] = shgen[i - 10].x[k];
            sh[i].y[k] = shgen[i - 10].y[k];
        }

    }
}
void randFieldIntegratorPlayer()
{
    for (int i = 0; i < sz; i++)
    {
        for (int k = 0; k < sz; k++)
        {
            if (genField[i][k] == aroundSh)
                genField[i][k] = ocean;
            fieldPlayer[i][k] = genField[i][k];
        }
    }
    for (int i = 0; i < 10; i++)
    {
        sh[i].length = shgen[i].length;
        sh[i].hp = shgen[i].length;
        for (int k = 0; k < shgen[i].length; k++)
        {
            sh[i].x[k] = shgen[i].x[k];
            sh[i].y[k] = shgen[i].y[k];
        }

    }
}
void shiparound(int shipNum)
{
    for (int i = 0; i < shgen[shipNum].length; i++)
    {
        for (int m = -1; m <= 1; m++)
        {
            for (int n = -1; n <= 1; n++)
            {
                if (genField[shgen[shipNum].y[i] + m][shgen[shipNum].x[i] + n] != aliveSh && genField[shgen[shipNum].y[i] + m][shgen[shipNum].x[i] + n] != boarder)
                {
                    genField[shgen[shipNum].y[i] + m][shgen[shipNum].x[i] + n] = aroundSh;
                }
            }
        }
    }
}
void generator(int shipNum)
{
    int direction = 0, x, y, dx1 = 1, dx2 = 1, dx3 = 1, dx4 = 1, xOld, yOld;
    bool d1 = true, d2 = true, d3 = true, d4 = true;
    for (int i = 0; i < shgen[shipNum].length; i++)
    {
        while (i == 0)
        {
            x = rand() % (sz - 1) + 1;
            y = rand() % (sz - 1) + 1;
            if (genField[y][x] != aroundSh && genField[y][x] != aliveSh && genField[y][x] != boarder)
            {
                xOld = x;
                yOld = y;
                genField[y][x] = aliveSh;
                break;
            }
        }
        if (i > 0)
        {
            while (true)
            {
                srand(time(NULL));
                direction = rand() % 4 + 1;
                if (direction == 1 && d1 && (genField[yOld - dx1][xOld] != aroundSh && genField[yOld - dx1][xOld] != boarder))
                {
                    y = yOld - dx1;
                    break;
                }
                if (direction == 2 && d2 && (genField[yOld][xOld + dx2] != aroundSh && genField[yOld][xOld + dx2] != boarder))
                {
                    x = xOld + dx2;
                    break;
                }
                if (direction == 3 && d3 && (genField[yOld + dx3][xOld] != aroundSh && genField[yOld + dx3][xOld] != boarder))
                {
                    y = yOld + dx3;
                    break;
                }
                if (direction == 4 && d4 && (genField[yOld][xOld - dx4] != aroundSh && genField[yOld][xOld - dx4] != boarder))
                {
                    x = xOld - dx4;
                    break;
                }
            }
            if (genField[y][x] != ocean)
            {

                if (direction == 1)
                    d1 = false;
                if (direction == 2)
                    d2 = false;
                if (direction == 3)
                    d3 = false;
                if (direction == 4)
                    d4 = false;
            }
            else
            {
                genField[y][x] = aliveSh;

                if (direction == 1 || direction == 3)
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
            }
        }
        shgen[shipNum].x[i] = x;
        shgen[shipNum].y[i] = y;
        // cout<<shgen[shipNum].x[i]<<" "<<shgen[shipNum].y[i]<<" "<<i+1<<" dx^"<<dx1<<dx2<<dx3<<dx4<<endl;
        if (i + 1 == shgen[shipNum].length)
        {
            shiparound(shipNum);
        }
    }
}
void randomgen(std::string whose)
{
    int curSh = 0;
    fieldBoarder(genField);
    for (int i = 4; i > 0; i--)
    {
        for (int k = 0; k < 5 - i; k++)
        {
            shgen[curSh].length = i;
            generator(curSh);
            curSh++;
        }
    }
    if (whose == "player")
        randFieldIntegratorPlayer();
    else
        randFieldIntegratorBot();
}
void progress(int sleeptime) {
    for (int i = 0; i <= 100; ++i) {  //рисование прогресс бара псевдо-загрузки для того чтоб картинка не накладывалась друг на друга
   //GotoXY(width / 2 - 20, height - 20);
        GotoXY((width - 54) / 2, (height - 7) / 2 + 8);
        draw_progress_bar(i);
        Sleep(sleeptime);
    }
    GotoXY((width - 32) / 2, (height - 7) / 2 + 10);
    system("pause");
}
void animation() {
    while (true) {
        Sleep(80);
        GotoXY((width - 16) / 2, (height - 7) / 2 + 8);
        std::cout << "Генерация поля /";
        Sleep(80);
        GotoXY((width - 16) / 2, (height - 7) / 2 + 8);
        std::cout << "Генерация поля \\";
        Sleep(80);
        GotoXY((width - 16) / 2, (height - 7) / 2 + 8);
        std::cout << "Генерация поля —";
        bool needExit = false;
        threadMutex.lock();
        needExit = ExitFlag;
        threadMutex.unlock();
        if (needExit) {
            setColor(LightGreen, Black);
            GotoXY((width - 20) / 2, (height - 7) / 2 + 8);
            std::cout << "Успешно сгенерировано.";
            setColor(White, Black);
            break;
        }
    }
}
void AI(std::string mode)
{
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
    height = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;
    width = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left;
    fieldBoarder(fieldPlayer);
    fieldBoarder(fieldBot);
    /*fieldBot[5][5] = aliveSh;
    fieldBot[5][4] = aliveSh;
    fieldBot[5][3] = aliveSh;
    sh[10].length = 3;
    sh[10].hp = 3;
    sh[10].x[0] = 5;
    sh[10].y[0] = 5;
    sh[10].x[1] = 4;
    sh[10].y[1] = 5;
    sh[10].x[2] = 3;
    sh[10].y[2] = 5;
    fieldBot[2][5] = aliveSh;
    fieldBot[2][4] = aliveSh;
    fieldBot[2][3] = aliveSh;
    fieldBot[2][2] = aliveSh;
    sh[11].length = 4;
    sh[11].hp = 4;
    sh[11].x[0] = 2;
    sh[11].y[0] = 2;
    sh[11].x[1] = 3;
    sh[11].y[1] = 2;
    sh[11].x[2] = 4;
    sh[11].y[2] = 2;
    sh[11].x[3] = 5;
    sh[11].y[3] = 2;*/
    if (mode == "constructor") {
        std::thread th(randomgen, "bot");
        progress(3);
        shipConstructor(fieldPlayer);
        th.join();
    }
    if (mode == "fromfile") {
        std::thread th(randomgen, "bot");
        progress(3);
        loadFromFile();
        th.join();
    }
    if (mode == "random")
    {
        auto f = std::async(std::launch::async, animation);
        randomgen("player");
        randomgen("bot"); 
        threadMutex.lock();
        ExitFlag = true;
        threadMutex.unlock();
        GotoXY((width - 30) / 2, (height - 7) / 2 + 10);
        system("pause");
        system("cls");
        showField(fieldPlayer);
        char choice;
        GotoXY(width / 2 + 28, height / 2);
        try_input_char("\t\t\t\t\t\t\t\t\t\t\t\t\t\tСохранить расстановку? y / n: ", choice, 49, 130, "z");
        GotoXY(width / 2 + 56, height / 2);
        switch (choice) {
        case'y':
            saveInFile();
            break;
        case'Y':
            saveInFile();
            break;
        }
        cleaning();
        while (true) {
            aiPlayer(fieldPlayer);
            Sleep(1500);
            humanPlayer();
            Sleep(1500);
        }
    }
}