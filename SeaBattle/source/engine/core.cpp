#include <iostream>
#include <windows.h>
#include <fstream>  
#include "core.h"
#include "GotoXY.h"

HANDLE hConsole;
HANDLE hOut;
COORD Pos;
bool d1 = true, d2 = true, d3 = true, d4 = true, shOnfire = false, player = false;
int xOld = 0, yOld = 0, dx1 = 1, dx2 = 1, dx3 = 1, dx4 = 1, direction, currAmofShips; //точка первого попадания по кораблю если он больше
const int maxamountOfShips = 10;
const char drownSh = 'X', missed = '#', aliveSh = 'H', boarder = '*', ocean = ' ';
class ship {
public:
    int length = { 0 };
    int hp=0;
    int x[4], y[4];
};
ship sh[maxamountOfShips * 2];
char fieldPlayer[sz][szx], fieldBot[sz][szx];

void humanPlayer()
{
    player = true;
    showField(fieldBot);
    GotoXY(width / 2 + 19, height / 2 - 23);
    std::cout << "                    ██ ██ ████  ███                  ";
    GotoXY(width / 2 + 19, height / 2 - 22);
    std::cout << "                     ███  █  █  █ █                  ";
    GotoXY(width / 2 + 19, height / 2 - 21);
    std::cout << "                      █   █  █  █ █                  ";
    GotoXY(width / 2 + 19, height / 2 - 20);
    std::cout << "                     ███  █  █ █████                 ";
    GotoXY(width / 2 + 19, height / 2 - 19);
    std::cout << "                    ██ ██ ████ █   █                 ";
    GotoXY(width / 2 + 24, height / 2 - 17);
    std::cout << "                                                     ";
    GotoXY(width / 2 + 24, height / 2 - 16);
    std::cout << "         █  █ ███ ████ ████ █  █ ████                         ";
    GotoXY(width / 2 + 24, height / 2 - 15);
    std::cout << "         █  █ █   █  █ █  █ █ █  █  █                    ";
    GotoXY(width / 2 + 24, height / 2 - 14);
    std::cout << "         █ ██ █   ████ █  █ ██   ████                    ";
    GotoXY(width / 2 + 24, height / 2 - 13);
    std::cout << "         ██ █ █   █    █  █ █ █  █  █                         ";
    GotoXY(width / 2 + 24, height / 2 - 12);
    std::cout << "         █  █ █   █    ████ █  █ █  █                    ";
    char x;
    int y, x1;
    while (true)
    {
        GotoXY(width / 2 + 20, height / 2 - 5);
        std::cout << "Координаты выстрела:                      ";
        GotoXY(width / 2 + 41, height / 2 - 5);
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
            GotoXY(width / 2 + 20, height / 2 - 4);
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
}
void aiPlayer(char field[sz][szx]) //основная функция ии для боя
{
    GotoXY(width / 2 + 19, height / 2 - 23);
    std::cout << "                    ██ ██ ████  ███                  ";
    GotoXY(width / 2 + 19, height / 2 - 22);
    std::cout << "                     ███  █  █  █ █                  ";
    GotoXY(width / 2 + 19, height / 2 - 21);
    std::cout << "                      █   █  █  █ █                  ";
    GotoXY(width / 2 + 19, height / 2 - 20);
    std::cout << "                     ███  █  █ █████                 ";
    GotoXY(width / 2 + 19, height / 2 - 19);
    std::cout << "                    ██ ██ ████ █   █                 ";
    GotoXY(width / 2 + 24, height / 2 - 17);
    std::cout << "                                                     ";
    GotoXY(width / 2 + 24, height / 2 - 16);
    std::cout << "█  █ ████ █   █ ████ █    █  ██  ███ ███ ████ ████     ";
    GotoXY(width / 2 + 24, height / 2 - 15);
    std::cout << "█ █  █  █ ██ ██ █  █ █    █ █  █  █  █   █  █ █  █     ";
    GotoXY(width / 2 + 24, height / 2 - 14);
    std::cout << "██   █  █ █ █ █ █  █ ████ ████ █  █  ███ ████ ████     ";
    GotoXY(width / 2 + 24, height / 2 - 13);
    std::cout << "█ █  █  █ █   █ █  █ █  █ █ █  █  █  █   █    █  █     ";
    GotoXY(width / 2 + 24, height / 2 - 12);
    std::cout << "█  █ ████ █   █ █  █ ████ █  ██   █  ███ █    █  █     ";
    player = false;
    showField(field);
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
            GotoXY(width / 2 + 20, height / 2 - 5);
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
            hitShip(x, y, field);
            field[y][x] = drownSh;
            xOld = x;
            yOld = y;
            shOnfire = true;
            showField(field);
            Sleep(1000);
            shipOnfire(field);

        }
        else //если не попал первым выстрелом
            field[y][x] = missed;
        Sleep(1000);
        showField(field);
    }
}
void shipConstructor(char field[sz][szx]) {
    char choice;
    int length, counter1 = 0, counter2 = 0, counter3 = 0, counter4 = 0,m;
    for (int counter = 0; counter < 10; counter++) {
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
        std::cout << "	   		               ▀▀";
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
                std::cout << "   Введите размерность корабля:                      ";
                GotoXY((width - 142) / 2 + 128, (height - 43) / 2 + 10 + m);
                std::cin >> length;
                if (length > 4) {
                    GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + 10 + m);
                    setColor(LightRed, Black);
                    std::cout << "Максимальный размер корабля - 4 клетки!";
                    Sleep(1000);
                    cleaning();
                }
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + 10 + m);
                    setColor(LightRed, Black);
                    std::cout << "Ошибка! Некорректные данные.\n";
                    Sleep(1000);
                    cleaning();
                }
                if (length==1 && counter1 > 3) { //проверка количества корабликов размерности 1
                    GotoXY((width - 142) / 2 + 96, (height - 43) / 2 + 10 + m);
                    setColor(LightRed, Black);
                    std::cout << "Ошибка! Максимальное количество корабликов размерностью 1 - 4 шт.\n";
                    Sleep(1500);
                    cleaning();
                    goto m; //если проверка не прошла возвращаемся в начало
                }
                else if (length == 1) {//если проверка прошла то ++ к счетчику корабликов 1
                    counter1++;
                }
                if (length == 2 && counter2 > 2) { //проверка количества корабликов размерности 2
                    GotoXY((width - 142) / 2 + 96, (height - 43) / 2 + 10 + m);
                    setColor(LightRed, Black);
                    std::cout << "Ошибка! Максимальное количество корабликов размерностью 2 - 3 шт.\n";
                    Sleep(1500);
                    cleaning();
                    goto m; //если проверка не прошла возвращаемся в начало
                }
                else if (length == 2) {//если проверка прошла то ++ к счетчику корабликов 2
                    counter2++;
                }
                if (length == 3 && counter3 > 1) { //проверка количества корабликов размерности 3
                    GotoXY((width - 142) / 2 + 96, (height - 43) / 2 + 10 + m);
                    setColor(LightRed, Black);
                    std::cout << "Ошибка! Максимальное количество корабликов размерностью 3 - 2 шт.\n";
                    Sleep(1500);
                    cleaning();
                    goto m; //если проверка не прошла возвращаемся в начало
                }
                else if (length == 3) {//если проверка прошла то ++ к счетчику корабликов 3
                    counter3++;
                }
                if (length == 4 && counter4 > 0) { //проверка количества корабликов размерности 3
                    GotoXY((width - 142) / 2 + 96, (height - 43) / 2 + 10 + m);
                    setColor(LightRed, Black);
                    std::cout << "Ошибка! Максимальное количество корабликов размерностью 4 - 1 шт.\n";
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
                std::cout << "Enter x" << i << " and y" << i << " :            ";
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
                        GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + 10 + m + i);
                        setColor(LightRed, Black);
                        std::cout << "Ошибка! Некорректные данные.\n";
                        Sleep(1000);
                        cleaning();
                        goto n;
                    }
        }
        sh[currAmofShips - 1].length = length;
        sh[currAmofShips - 1].hp = length;
    }
    cleaning();
    showField(fieldPlayer);

    /*GotoXY(width / 2 + 20, height / 2 - 5);
      std::cout << "Сохранить расстановку? y" << R"(\n: )" << "                     ";
      GotoXY(width / 2 + 48, height / 2 - 5);
      std::cin >> choice;
      switch (choice) {
      case'y':
          saveInFile();
          loadFromFile();
          showField(fieldPlayer);
          break;
      }
      system("pause");
      */
    while (true) {
        aiPlayer(fieldPlayer);
        Sleep(1500);
        humanPlayer();
        Sleep(1500);
    }
}
void saveInFile() { //сохранениие поля игрока в файл
    std::ofstream fout("out.bin", std::ios_base::binary);
    for (int i = 0; i < (sz); i++)
    {
        for (int j = 0; j < (szx); j++)
        {
            fout << fieldPlayer[i][j] << " ";
            std::cout<< fieldPlayer[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Succes!";
    system("pause");
}
void loadFromFile() { //загрузка
    std::ifstream fin("out.bin", std::ios_base::binary);
    for (int i = 0; i < (sz); i++)
    {
        for (int j = 0; j < (szx); j++)
        {
            fin >> fieldPlayer[i][j];
        }
    }
    std::cout << "Succes!";
}
void cleaning() {
    GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + 22 );
    std::cout << "                                                                   ";  //очистка ввода
    GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + 23);
    std::cout << "                                            ";
    GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + 24);
    std::cout << "                                            ";
    GotoXY((width - 142) / 2 + 99, (height - 43) / 2 + 25);
    std::cout << "                                            ";
}
void AI()
{
    /*HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD crd = { 100, 100 };
    SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
    SetConsoleWindowInfo(out_handle, true, &src);
    SetConsoleScreenBufferSize(out_handle, crd);
    */
    fieldBoarder(fieldPlayer);
    fieldBoarder(fieldBot);

    fieldBot[5][5] = aliveSh;
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
    sh[11].y[3] = 2;


    std::string mode;
    for (int i = 0; i <= 100; ++i) {  //рисование прогресс бара псевдо-загрузки для того чтоб картинка не накладывалась друг на друга
        GotoXY(width / 2 - 20, height - 20);
        draw_progress_bar(i);
        Sleep(3);
    }
    GotoXY(width / 2 - 10, height - 18);
    system("pause");
   /* loadFromFile();
    showField(fieldPlayer);
    Sleep(1500);
    while (true) {
        aiPlayer(fieldPlayer);
        Sleep(1500);
        humanPlayer();
        Sleep(1500);
    }*/
    shipConstructor(fieldPlayer);

}