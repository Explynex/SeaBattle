#include <iostream>
#include <time.h>
#include "windows.h"
using namespace std;
HANDLE hConsole;
HANDLE hOut;
COORD Pos;
bool d1 = true, d2 = true, d3 = true, d4 = true, shOnfire = false;
int xOld = 0, yOld = 0, dx1 = 1, dx2 = 1, dx3 = 1, dx4 = 1, direction, currAmofShips;//����� ������� ��������� �� ������� ���� �� ������ 1 ����� + ��������� �� ����������� � ������ �������
const int maxamountOfShips = 5;
const char drownSh = 'X', missed = '#', aliveSh = 'H', boarder = '*', ocean = ' ';
class ship {
public:
    int length;
    int hp;
    int x[4], y[4];
};
ship sh[5];
const int sz = 12, szx = 12;
char field[sz][szx];
void fieldBoarder() {
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
void horOutput(int i)
{
    for (int k = 0; k < szx - 1; k++)
    {
        if (field[i][k] == boarder)
            SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | FOREGROUND_BLUE);
        else if (field[i][k] == ocean)
            SetConsoleTextAttribute(hConsole, 240);
        else if (field[i][k] == aliveSh)
            SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | FOREGROUND_GREEN);
        else if (field[i][k] == drownSh)
            SetConsoleTextAttribute(hConsole, BACKGROUND_RED | FOREGROUND_RED);
        else
            SetConsoleTextAttribute(hConsole, 240);
        for (int m = 0; m < 6; m++)
            cout << field[i][k];
        if (k <= szx - 2 && k != 0)
        {
            SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | FOREGROUND_BLUE);
            cout << boarder << boarder;
        }
    }

}
void kletochki(int i)
{
    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | FOREGROUND_BLUE);
    for (int i = 0; i < szx * 6 + 14; i++)
        cout << boarder;
    SetConsoleTextAttribute(hConsole, 15);
    if (i != sz - 2)
        cout << endl;
}
void showField() {
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Pos.X = 0;
    Pos.Y = 0;
    SetConsoleCursorPosition(hOut, Pos);
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FlushConsoleInputBuffer(hConsole);
    for (int i = 0; i < sz - 1; i++)
    {
        horOutput(i);
        SetConsoleTextAttribute(hConsole, 15);
        cout << endl;
        horOutput(i);
        SetConsoleTextAttribute(hConsole, 15);
        cout << endl;
        horOutput(i);
        SetConsoleTextAttribute(hConsole, 15);
        cout << endl;
        if (i != sz - 1 && i != 0)
            kletochki(i);
    }
}
void shipDrown(int shipNum) {//������� ���������� �������
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
void hitShip(int x, int y) {//������� ������ �� � ������� ��� ���������
    for (int k = 0; k < maxamountOfShips; k++)
    {
        for (int i = 0; i < sh[k].length; i++)
        {
            if (sh[k].x[i] == x && sh[k].y[i] == y)
            {

                sh[k].hp--;
                //cout<<"Current ship hp "<<sh[k].hp<<endl;
                if (sh[k].hp == 0)
                {
                    //   cout<<"game over"<<endl;
                    shipDrown(k);
                }
            }
        }
    }
}
void shipOnfire() {//������� �� ��� ����������� ��� �� ��������� �������
    int x = xOld, y = yOld;
    //  cout<<"Ship on fire"<<endl;
    while (shOnfire)
    {
        while (shOnfire)//��������� ����������� ��� ������ ��������
        {
            srand(time(NULL));
            direction = rand() % 4 + 1;
            // cout<<"generated dir "<<direction<<endl;
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
        if (field[y][x] != aliveSh)//�� �����
        {
            //  cout<<d1<<d2<<d3<<d4<<" "; ���� �����������
            field[y][x] = missed;
            //���������� ����������� � ������� ��� ������ �������
            if (direction == 1)
                d1 = false;
            if (direction == 2)
                d2 = false;
            if (direction == 3)
                d3 = false;
            if (direction == 4)
                d4 = false;
            showField();
            Sleep(3000);
            // cout<<d1<<d2<<d3<<d4<<endl; ���� �����������
            break;
        }
        else//�����
        {
            field[y][x] = drownSh;
            if (direction == 1 || direction == 3)//��� �� � ��� � ��� ���������
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
            hitShip(x, y);
        }
        showField();
        Sleep(3000);
    }
}
void aiPlayer()//�������� ������� �� ��� ���
{
    int x, y;
    if (shOnfire)//� ������� ��� ������ �� ������� �� �� ����������
    {
        shipOnfire();
    }
    else
    {
        srand(time(NULL));
        while (true)//������ ��������� �������
        {
            x = rand() % (sz - 1) + 1;
            y = rand() % (sz - 1) + 1;
            if (field[y][x] != missed && field[y][x] != drownSh && field[y][x] != boarder)
                break;
        }
        if (field[y][x] == aliveSh)//���� �����
        {
            hitShip(x, y);
            field[y][x] = drownSh;
            xOld = x;
            yOld = y;
            shOnfire = true;
            showField();
            Sleep(3000);
            shipOnfire();

        }
        else//���� �� ����� ������ ���������
            field[y][x] = missed;
        showField();
        Sleep(3000);
    }
}
void shipAdd() {
    int length, x, y;
    currAmofShips++;
    cout << endl << "Welcome to the ship placement program" << endl;
    cout << "Enter length of new ship : ";
    cin >> length;
    for (int i = 0; i < length; i++)
    {
        cout << "Enter x" << i << " and y" << i << " : ";
        cin >> sh[currAmofShips - 1].x[i] >> sh[currAmofShips - 1].y[i];
        field[sh[currAmofShips - 1].y[i]][sh[currAmofShips - 1].x[i]] = aliveSh;
    }
    sh[currAmofShips - 1].length = length;
    sh[currAmofShips - 1].hp = length;
    showField();
}
void AI()
{
    /*HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD crd = { 100, 100 };
    SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
    SetConsoleWindowInfo(out_handle, true, &src);
    SetConsoleScreenBufferSize(out_handle, crd);
    */
    string mode;
    int m;
    fieldBoarder();
    field[5][5] = aliveSh;
    field[5][4] = aliveSh;
    field[5][3] = aliveSh;
    sh[0].length = 3;
    sh[0].hp = 3;
    sh[0].x[0] = 5;
    sh[0].y[0] = 5;
    sh[0].x[1] = 4;
    sh[0].y[1] = 5;
    sh[0].x[2] = 3;
    sh[0].y[2] = 5;

    field[2][5] = aliveSh;
    field[2][4] = aliveSh;
    field[2][3] = aliveSh;
    field[2][2] = aliveSh;
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
    while (mode != "/exit") {
        cout << endl << "'/game' - чтобы начать игру,'/construct' - перейти в конструктор кораблей\n";
        cin >> mode;
        if (mode == "/exit")
            break;
        if (mode == "/construct")
        {
            while (mode != "/stop") {
                system("cls");
                showField();
                std::cout << std::endl << " '/add' - чтобы добавить еще,'/stop' - чтобы выйти" << std::endl;
                cin >> mode;
                if (mode == "/stop")
                    break;
                if (mode == "/add") {
                    shipAdd();
                    system("cls");
                    showField();
                }
            }
        }
        /*while (mode == "debug")
        {
            aiPlayer();
            //showField();
            //system("pause");
        }*/
        while (mode == "/game")
        {
            aiPlayer();
        }
    }

}
