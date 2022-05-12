#include "core.h"

HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

enum difficulty { easy, normal, hard, suicide };
class ship {
public:
    int length{};
    int hp = 0;
    int x[4]{}, y[4]{};
};

bool d1 = true, d2 = true, d3 = true, d4 = true, shOnfire = false, player = false, game;
int xOld = 0, yOld = 0, dx1 = 1, dx2 = 1, dx3 = 1, dx4 = 1, direction, currAmofShips = 0; //точка первого попадания по кораблю если он больше
const int maxamountOfShips = 10;
const char aroundSh = '.', drownSh = '#', missed = 'X', aliveSh = 'H', boarder = '*', ocean = ' ';
ship sh[maxamountOfShips * 2], shgen[maxamountOfShips];
char fieldPlayer[sz][szx], fieldBot[sz][szx];
COORD genPosArr[100], shootPosArr[100];
int genPosAm = 100, shootPosAm = 100;
int currdifficulty = normal;
int misscounter = 0;

//need refactoring
void gameoverchecker()
{
    if (sh[0].hp + sh[1].hp + sh[2].hp + sh[3].hp + sh[4].hp + sh[5].hp + sh[6].hp + sh[7].hp + sh[8].hp + sh[9].hp == 0)
    {
        system("cls");
        setColor(WHITE, BLACK);
        writeTitle(width, height, "aiwin");
        GotoXY((width - 34) / 2 + 3, (height - 11) / 2 + 10);
        std::cout << "Нажмите любую кнопку для продолжения ...";
        setColor(BLACK, BLACK);
        system("pause");
        setColor(WHITE, BLACK);
        game = false;
    }

    if (sh[10].hp + sh[11].hp + sh[12].hp + sh[13].hp + sh[14].hp + sh[15].hp + sh[16].hp + sh[17].hp + sh[18].hp + sh[19].hp == 0)
    {
        system("cls");
        setColor(WHITE, BLACK);
        writeTitle(width, height, "playerwin");
        GotoXY((width - 34) / 2 + 3, (height - 11) / 2 + 10);
        std::cout << "Нажмите любую кнопку для продолжения ...";
        setColor(BLACK, BLACK);
        system("pause");
        setColor(WHITE, BLACK);
        game = false;
    }
}

//refactoring complete
void gameProcess()
{
    shootPosAm = 100;
    freePosCrdFiller(shootPosArr);
    COORD shoot{};
    bool hit = false;
    cleaning((width - 142) / 2 + 95, (height - 43) / 2 + 21, 50, 3);
    while (true && game)
    {
        writeTitle(width, height, "playermove");
        player = true;
        showField(fieldBot);
        cleaning((width - 142) / 2 + 95, (height - 43) / 2 + 18, 20, 1);
        setColor(LIGHTCYAN, BLACK);
        GotoXY((width - 142) / 2 + 95, (height - 43) / 2 + 18, "Клик по клетке для выстрела!");
        do {
            shoot = setConsoleButton(width / 2 - 65, height / 2 - 19, 6, 3, 10, 10, VK_LBUTTON, NUL, NUL, 0);
            if (shoot.Y == 0 || shoot.X == 0) {
                game = false;
                return;
            }
        } while (fieldBot[shoot.Y][shoot.X] == drownSh || fieldBot[shoot.Y][shoot.X] == missed);
        if (fieldBot[shoot.Y][shoot.X] == aliveSh){
            GotoXY((width - 142) / 2 + 95, (height - 43) / 2 + 18, "Попадание!                   ",LIGHTGREEN,BLACK);
            fieldBot[shoot.Y][shoot.X] = drownSh;
            hitShip(shoot.X, shoot.Y, fieldBot);
            Sleep(800);
            hit = true;
        }
        else {
            GotoXY((width - 142) / 2 + 95, (height - 43) / 2 + 18,"Промах!                     ", LIGHTRED, BLACK);
            fieldBot[shoot.Y][shoot.X] = missed;
            hit = false;
        }
        if (hit == false) {
            showField(fieldBot);
            Sleep(1200);
            aiPlayer(fieldPlayer);
            Sleep(1200);
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
            setColor(LIGHTBLUE, LIGHTBLUE);
        else if (field[i][k] == ocean || field[i][k] == aliveSh && player || field[i][k] == aroundSh)
            setColor(WHITE, WHITE);
        else if (field[i][k] == aliveSh)
            setColor(LIGHTGREEN, LIGHTGREEN);
        else if (field[i][k] == drownSh)
            setColor(RED, RED);
        else
            setColor(BLACK, WHITE);

        if (ifboarder || field[i][k] != boarder)
            for (int m = 0; m < 6; m++)
                std::cout << field[i][k];
        else if (boarder && field[i][k] == boarder)
        {
            for (int m = 0; m < 6; m++)
            {
                if (m == 3 || i / 10 > 0 && m == 2)
                {
                    setColor(WHITE, LIGHTBLUE);
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
                    setColor(LIGHTBLUE, LIGHTBLUE);
                    std::cout << field[i][k];
                }

            }
        }

        if (k <= szx - 2 && k != 0)
        {
            setColor(LIGHTBLUE, LIGHTBLUE);
            std::cout << boarder << boarder;
        }
    }

}

void kletochki(int i){
    setColor(LIGHTBLUE, LIGHTBLUE);
    for (int i = 0; i < szx * 6 + 14; i++)
        std::cout << boarder;
    setColor(WHITE, BLACK);
    if (i != sz - 2)
        std::cout << std::endl;
}

void showField(char field[sz][szx]) {
    int m = 0;
    for (int i = 0; i < sz - 1; i++)
    {
        GotoXY((width - 142) / 2, (height - 43) / 2 + m++);
        horOutput(i, true, field);
        GotoXY((width - 142) / 2, (height - 43) / 2 + m++);
        horOutput(i, false, field);//if false - std::cout grid number
        GotoXY((width - 142) / 2, (height - 43) / 2 + m++);
        horOutput(i, true, field);
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
                    if (!player)
                        shootPosAm = freePosCrdDeleter(sh[shipNum].x[i] + n, sh[shipNum].y[i] + m, shootPosArr, shootPosAm);
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
                    if (sh[k].hp == 0)
                    {
                        shipDrown(k, field);
                    }
                    showField(field);
                    gameoverchecker();
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
                    if (sh[k].hp == 0)
                    {
                        shipDrown(k, field);
                    }
                    showField(field);
                    gameoverchecker();
                }
            }
        }
}

void shipOnfire(char field[sz][szx]) {//функция ии для продолжения боя по найденому кораблю
    int x = xOld, y = yOld;
    player = false;
    while (shOnfire)
    {
        while (shOnfire) //генерация направления для нового выстрела
        {

            direction = rand() % 4 + 1;
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
        }
        if (field[y][x] != aliveSh) //не попал
        {
            field[y][x] = missed;
            shootPosAm = freePosCrdDeleter(x, y, shootPosArr, shootPosAm);
            if (direction == 1)
                d1 = false;
            if (direction == 2)
                d2 = false;
            if (direction == 3)
                d3 = false;
            if (direction == 4)
                d4 = false;
            showField(field);
            break;
        }
        else //попал
        {
            Sleep(400);
            field[y][x] = drownSh;
            shootPosAm = freePosCrdDeleter(x, y, shootPosArr, shootPosAm);
            //
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
            if (!game)
                return;
        }
        showField(field);
    }
    if (!shOnfire)
        aiPlayer(field);
}

void aiPlayer(char field[sz][szx]) //основная функция ии для боя
{
    setColor(WHITE, BLACK);
    writeTitle(width, height, "aimove");
    player = false;
    showField(field);
    int x, y;
    if (shOnfire && currdifficulty != easy) //в прошлый раз попали по кораблю но не уничтожили
    {
        Sleep(400);
        GotoXY((width - 142) / 2 + 95, (height - 43) / 2 + 12 + 6, "Ожидание хода компьютера...       ", LIGHTCYAN, BLACK);
        shipOnfire(field);
    }
    else
    {
    esmark: while (true) //первый рандомный выстрел
    {
        GotoXY((width - 142) / 2 + 95, (height - 43) / 2 + 12 + 6);
        std::cout << "Ожидание хода компьютера...       ";
        // cleaning(8);
        int idx = rand() % shootPosAm;
        x = shootPosArr[idx].X;
        y = shootPosArr[idx].Y;
        if ((currdifficulty == hard && misscounter >= 8) || (currdifficulty == suicide && misscounter >= 3))
        {
            while (field[y][x] != aliveSh)
            {
                idx = rand() % shootPosAm;
                x = shootPosArr[idx].X;
                y = shootPosArr[idx].Y;
            }
        }

        if (field[y][x] != missed && field[y][x] != drownSh && field[y][x] != boarder)
        {
            shootPosAm = freePosCrdDeleter(x, y, shootPosArr, shootPosAm);
            break;
        }
    }
    if (field[y][x] == aliveSh) //если попал
    {
        Sleep(400);
        misscounter = 0;
        field[y][x] = drownSh;
        xOld = x;
        yOld = y;
        shOnfire = true;
        hitShip(x, y, field);
        if (!game)
            return;
        if (currdifficulty != easy)
            shipOnfire(field);
        else
        {
            showField(field);
            goto esmark;
        }
    }
    else //если не попал первым выстрелом
    {
        misscounter++;
        field[y][x] = missed;
    }
    showField(field);
    }
}

void shiparoundC(int shipNum, char field[sz][szx]) {
    for (int i = 0; i < sh[shipNum].length; i++)
        for (int m = -1; m <= 1; m++)
            for (int n = -1; n <= 1; n++)
                if (field[sh[shipNum].y[i] + m][sh[shipNum].x[i] + n] != aliveSh && field[sh[shipNum].y[i] + m][sh[shipNum].x[i] + n] != boarder)
                         field[sh[shipNum].y[i] + m][sh[shipNum].x[i] + n] = aroundSh;
}

bool trueship(int curramofblocks)
{
    if (curramofblocks == 1)
        return true;
    int ok = 0;
    bool paraleltoOX = false, paraleltoOY = false;
    for (int i = 0; i < curramofblocks - 1; i++)
    {
        if ((sh[currAmofShips - 1].x[i] - sh[currAmofShips - 1].x[i + 1]) == 0 && abs(sh[currAmofShips - 1].y[i] - sh[currAmofShips - 1].y[i + 1]) == 1 && !paraleltoOX)
        {
            paraleltoOY = true;
            ok++;
        }
        if ((sh[currAmofShips - 1].y[i] - sh[currAmofShips - 1].y[i + 1]) == 0 && abs(sh[currAmofShips - 1].x[i] - sh[currAmofShips - 1].x[i + 1]) == 1 && !paraleltoOY)
        {
            paraleltoOX = true;
            ok++;
        }
    }
    if (ok == curramofblocks - 1)
        return true;
    else
        return false;
}

void shipCountAnim(short x, short y, bool* active, short count) {
    short tempX = x;
    for (USHORT i = 0; i < count; i++) {
        if (active[count - 1] == true)
            cleaning(tempX, y, 6, 3, LIGHTCYAN);
        else
            cleaning(tempX, y, 6, 3, DARKGRAY);
        tempX += 8;
    }
    if (count == 1) return;
    else  shipCountAnim(x, y+4, active, count - 1);
}

//refactoring complete
void shipConstructor(char field[sz][szx]) {
    COORD pos{};
    short length = 0,len1=4,len2=3,len3=2,len4=1;
    std::string nums[4] = { "1x","2x","3x","4x" };
    bool active[4] = { 1,1,1,1 };
    system("cls");
    showField(fieldPlayer);
    writeTitle(width, height, "construct");
    for (int counter = 0; counter < 10; counter++) {
        GotoXY(width / 2 + 33, height / 2 -3, "Выберите тип корабля.");
        shipCountAnim(width / 2 + 32, height / 2, active);
        do{
            pos = setConsoleButton(width / 2 + 24, height / 2, 6, 3, 1, 4, VK_LBUTTON, DARKGRAY, LIGHTCYAN, 0, true, 1, LIGHTCYAN, BLACK, nums, 2, BLACK);
            if (nums[pos.Y - 1] == "0x") Sleep(100);
        }while (nums[pos.Y-1] == "0x");
        if (pos.Y == 0) return;
        else if (pos.Y == 1) {
            len4--;
            if (len4 == 0) active[3] = false;
            nums[pos.Y - 1] = std::to_string(len4) + "x";
            length = 4;
        }
        else if (pos.Y == 2) {
            len3--;
            if (len3 == 0) active[2] = false;
            nums[pos.Y - 1] = std::to_string(len3) + "x";
            length = 3;
        }
        else if (pos.Y == 3) {
            len2--;
            if (len2 == 0) active[1] = false;
            nums[pos.Y - 1] = std::to_string(len2) + "x";
            length = 2;
        }
        else if (pos.Y == 4) {
            len1--;
            if (len1 == 0) active[0] = false;
            nums[pos.Y - 1] = std::to_string(len1) + "x";
            length = 1;
        }
        currAmofShips++;
        for (int i = 0;i<length ;i++){
            pos = setConsoleButton(width / 2 - 65, height / 2 - 19, 6, 3, 10, 10, VK_LBUTTON, NUL, NUL, 0);
            sh[currAmofShips - 1].x[i] = pos.X;
            sh[currAmofShips - 1].y[i] = pos.Y;
            if (field[sh[currAmofShips - 1].y[i]][sh[currAmofShips - 1].x[i]] == ocean && trueship(i + 1)) {
                field[sh[currAmofShips - 1].y[i]][sh[currAmofShips - 1].x[i]] = aliveSh;
                showField(fieldPlayer);
            }
            else  i--;
            Sleep(100);
        }
        sh[currAmofShips - 1].length = length;
        sh[currAmofShips - 1].hp = length;
        shiparoundC(currAmofShips - 1, fieldPlayer);
    }
    cleaning(width / 2 + 23, height / 2 - 3, 40, 20);

    for (int i = 0; i < sz; i++)
        for (int k = 0; k < sz; k++)
            if (fieldPlayer[i][k] == aroundSh) fieldPlayer[i][k] = ocean;

    GotoXY(width / 2 + 28, height / 2,"Сохранить расстановку? y\\n",LIGHTCYAN,BLACK);
    wchar_t choice = _getwch();
    if(choice == 'Y' || choice == 'y' || choice == L'Н' || choice == L'н') saveInFile();
}

//refactoring complete
void saveInFile() { //сохранениие поля игрока в файл
    showConsoleCursor(TRUE);
    std::string name;
    char x;
    GotoXY(width / 2 + 28, height / 2 + 2,"Название файла : ", LIGHTCYAN, BLACK);
    name = printFilter(12,getConsoleCursorPosition().X, height / 2 + 2,"str"," ","ґ") + ".save";
    if (name == "0.save") {
        GotoXY(width / 2 + 28, height / 2 + 3,"Сохранение отменено.            ", LIGHTRED, BLACK);
        Sleep(1500);
        return;
    }
    std::ofstream fout(createFolders() + "\\Saves\\" + name);
    for (int i = 0; i < maxamountOfShips; i++)
    {
        fout << sh[i].length << " ";
        for (int j = 0; j < sh[i].length; j++)
        {
            x = sh[i].x[j] + 64;
            fout << x << sh[i].y[j];
        }
        fout << " ";
    }
    showConsoleCursor(FALSE);
    GotoXY(width / 2 + 28, height / 2 + 3, "Сохранено под названием: " + name,LIGHTGREEN,BLACK);
    Sleep(1500);
}

//refactoring complete
std::string createFolders() {
    std::string userName = utf.getPath("username");
    std::string folderPath = "C:\\Users\\" + userName + "\\Documents\\SeaBattle";
    CreateDirectoryA(data(folderPath), NULL);
    std::string savePath = folderPath + "\\Saves\\";
    CreateDirectoryA(data(savePath), NULL);
    return folderPath;
}

void menuNavigateHelper(wchar_t& key) {
    if (key == L'ц' || key == L'Ц' || key == 'W') {
        key = 'w'; 
        return;
    }
    if (key == L'Ы' || key == L'ы' || key == L'і' || key == L'І' || key == 'S')
        key = 's';
}

void predprosmotr(std::string menu, int pointer, int counter)
{
    char x;
    std::ifstream fin;
    fieldBoarder(fieldPlayer);
    fin.open(createFolders() + "\\Saves\\" + menu + ".save");
    for (int i = 0; i < 10; i++) {
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
    fin.close();
    for (int i = 0; i < sz; i++)
    {
        GotoXY((width - 54) / 2 + 36, (height - 12) / 2 + i);
        for (int k = 0; k < szx; k++)
        {
            if (fieldPlayer[i][k] == boarder)
                setColor(LIGHTBLUE, LIGHTBLUE);
            else if (fieldPlayer[i][k] == ocean)
                setColor(WHITE, WHITE);
            else if (fieldPlayer[i][k] == aliveSh)
                setColor(LIGHTGREEN, LIGHTGREEN);
            std::cout << fieldPlayer[i][k] << fieldPlayer[i][k];
            setColor(WHITE, BLACK);
        }
    }

}

// refactoring complete
void loadFromFile() { 
    system("cls");
    const std::string directory = "C:\\Users\\" + utf.getPath("username") + "\\Documents\\SeaBattle\\Saves\\";
    std::vector<std::string> menu = utf.fileNameList(1, directory, ".save");
    char x;
    wchar_t key{};
    int pointer = 0, indent = 0, counter = 0;
    while (true) {
        counter = menu.size();
        if (counter < 10) indent = 4;
        else indent = 5;
        setColor(WHITE, BLACK);
        GotoXY((width - 54) / 2, (height - 4 - counter) / 2,"╭────────────────────────╮",LIGHTCYAN,BLACK);
        GotoXY((width - 54) / 2, (height - 4 - counter) / 2 + 1,"│",LIGHTCYAN,BLACK);
        std::cout << "   Список сохранений    ";
        setColor(LIGHTCYAN, BLACK);
        std::cout << "│" << std::endl;
        GotoXY((width - 54) / 2, (height - 4 - counter) / 2 + 2, "├────────────────────────┤",LIGHTCYAN,BLACK);
        for (int i = 0; i < counter; i++) {
            if (i == pointer) { //если равно строке на которой находится пользователь
                GotoXY((width - 54) / 2 + indent, (height - 4 - counter) / 2 + 3 + i, " >> " + menu[i], LIGHTCYAN, BLACK);
                GotoXY((width - 54) / 2, (height - 4 - counter) / 2 + 3 + i, "│ ", LIGHTCYAN, BLACK);
                std::cout << i + 1 << ".";
                GotoXY((width - 54) / 2 + 25, (height - 4 - counter) / 2 + 3 + i, "│", LIGHTCYAN, BLACK);
            }
            else { //выводит то что не выбрано
                setColor(WHITE, BLACK);
                GotoXY((width - 54) / 2 + indent + 1, (height - 4 - counter) / 2 + 3 + i, menu[i] + "       ");
                GotoXY((width - 54) / 2, (height - 4 - counter) / 2 + 3 + i, "│ ", LIGHTCYAN, BLACK);
                std::cout << i + 1 << ".";
                GotoXY((width - 54) / 2 + 25, (height - 4 - counter) / 2 + 3 + i, "│", LIGHTCYAN, BLACK);
            }
        }
        GotoXY((width - 54) / 2, (height - 4 - counter) / 2 + 3 + counter, "╰────────────────────────╯",LIGHTCYAN,BLACK);
        while (true) {
            if (counter != 0) predprosmotr(menu[pointer], pointer, counter);
            key = _getwch();
            menuNavigateHelper(key);
            if (key == 'w') {
                pointer -= 1;
                if (pointer == -1) pointer = counter - 1;
                break;
            }
            if (key == 's') {
                pointer += 1;
                if (pointer == counter) pointer = 0;
                break;
            }
            else if (key == VK_ESCAPE) {
                game = false;
                return;
            }
            else if (key == VK_RETURN) {
                std::ifstream fin;
                fin.open(createFolders() + "\\Saves\\" + menu[pointer] + ".save");
                for (int i = 0; i < 10; i++) {
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
                fin.close();
                GotoXY((width - 54) / 2 + 36, (height - 12) / 2 + 13,
                    "Расстановка '" + menu[pointer] + "' успешно загружена. Начало игры...", LIGHTGREEN, BLACK);
                Sleep(1000);
                return;
            }
            else if (key == VK_BACK) {
                std::string FN = createFolders() + "\\Saves\\" + menu[pointer] + ".save";
                GotoXY((width - 54) / 2 + 2, (height - 4 - counter) / 2 + 7 + counter,
                    "Вы уверены что хотите удалить расстановку '" + menu[pointer] + "'? y\\n",LIGHTRED,BLACK);
                key = _getwch();
                if(key == 'y' || key == 'Y' || key == L'Н' || key == L'н'){
                    remove(FN.c_str());
                    GotoXY((width - 54) / 2 + 2, (height - 4 - counter) / 2 + 7 + counter,
                        "Расстановка '" + menu[pointer] + "' успешно удалена.                     ",LIGHTGREEN,BLACK);
                    menu[pointer].erase();
                    break;
                }
                else {
                    cleaning((width - 54) / 2 + 2, (height - 4 - counter) / 2 + 7 + counter, 50 + menu[pointer].length(), 1);
                    break;
                }
            }
        }
    }
}

//refactoring complete
void AI(std::string mode)
{
    game = true;
    player = false;
    fieldBoarder(fieldPlayer);
    fieldBoarder(fieldBot);
    randomgen("bot", fieldBot);

    if (mode == "constructor") shipConstructor(fieldPlayer);
    if (mode == "fromfile")  loadFromFile();
    if (mode == "random"){
        randomgen("player", fieldPlayer);
        system("cls");
        showField(fieldPlayer);
        std::string choice[2] = {"Yes","No"};
        GotoXY(width / 2 + 28, height / 2, "Сохранить расстановку?",LIGHTCYAN,BLACK);
        COORD button = setConsoleButton(
            (width / 2)+53, height / 2, 5, 1, 2, 1,
            VK_LBUTTON, DARKGRAY, LIGHTCYAN, 0, true, 1, LIGHTCYAN, BLACK, choice, 1, BLACK );
        if (button.X == 0) return;
        else if (button.X == 1) saveInFile();
    }
    gameProcess();
}


void randFieldIntegrator(char genField[sz][szx], int start)
{
    int m = 0;
    for (int i = 0; i < sz; i++)
    {
        for (int k = 0; k < sz; k++)
        {
            if (genField[i][k] == aroundSh)
                genField[i][k] = ocean;
        }
    }
    for (int i = start; i < start + 10; i++)
    {
        sh[i].length = shgen[m].length;
        sh[i].hp = shgen[m].length;
        for (int k = 0; k < shgen[m].length; k++)
        {
            sh[i].x[k] = shgen[m].x[k];
            sh[i].y[k] = shgen[m].y[k];
        }
        m++;

    }
}
void shiparound(int shipNum, char genField[sz][szx])
{
    for (int i = 0; i < shgen[shipNum].length; i++)
        for (int m = -1; m <= 1; m++)
            for (int n = -1; n <= 1; n++)
                if (genField[shgen[shipNum].y[i] + m][shgen[shipNum].x[i] + n] != aliveSh && genField[shgen[shipNum].y[i] + m][shgen[shipNum].x[i] + n] != boarder)
                {
                    genField[shgen[shipNum].y[i] + m][shgen[shipNum].x[i] + n] = aroundSh;
                    genPosAm = freePosCrdDeleter(shgen[shipNum].x[i] + n, shgen[shipNum].y[i] + m, genPosArr, genPosAm);
                }
}
void testgen(char genField[sz][szx]) {
    for (int i = 0; i < sz; i++)
    {
        for (int k = 0; k < szx; k++)
        {
            std::cout << genField[i][k];
        }
        std::cout << "\n";
    }

}
int generator(std::string whose,int shipNum, char genField[sz][szx])
{
    int direction = 0, x, y, dx1 = 1, dx2 = 1, dx3 = 1, dx4 = 1, xOld, yOld,lagfinder=0;
    bool d1 = true, d2 = true, d3 = true, d4 = true;
    for (int i = 0; i < shgen[shipNum].length; i++)
    {
        //testgen(genField);
        while (i == 0)
        {
            int idx = rand() % genPosAm;
            xOld = genPosArr[idx].X;
            yOld = genPosArr[idx].Y;
            x = genPosArr[idx].X;
            y = genPosArr[idx].Y;
            if (genField[yOld][xOld] != aroundSh && genField[yOld][xOld] != aliveSh && genField[yOld][xOld] != boarder)
            {
                genField[y][x] = aliveSh;
                genPosAm = freePosCrdDeleter(xOld, yOld, genPosArr, genPosAm);
                break;
            }
        }
        if (i > 0)
        {
            lagfinder = 0;
            while (true)
            {
                lagfinder++;
                direction = rand() % 4 + 1;
                if (direction == 1 && d1 && (genField[yOld - dx1][xOld] != aroundSh && genField[yOld - dx1][xOld] != boarder))
                {
                    y = yOld - dx1;
                    break;
                }
                else if (direction == 2 && d2 && (genField[yOld][xOld + dx2] != aroundSh && genField[yOld][xOld + dx2] != boarder))
                {
                    x = xOld + dx2;
                    break;
                }
                else if (direction == 3 && d3 && (genField[yOld + dx3][xOld] != aroundSh && genField[yOld + dx3][xOld] != boarder))
                {
                    y = yOld + dx3;
                    break;
                }
                else if (direction == 4 && d4 && (genField[yOld][xOld - dx4] != aroundSh && genField[yOld][xOld - dx4] != boarder))
                {
                    x = xOld - dx4;
                    break;
                }
                if(lagfinder>=500)
                {
                    //system("pause");
                    randomgen(whose, genField);
                    return -1;
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
                genPosAm = freePosCrdDeleter(x, y, genPosArr, genPosAm);
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
        //std::cout<<shgen[shipNum].x[i]<<" "<<shgen[shipNum].y[i]<<" "<<i+1<<" dx^"<<dx1<<dx2<<dx3<<dx4<<std::endl;
        if (i + 1 == shgen[shipNum].length)
        {
            shiparound(shipNum, genField);
        }
        //testgen(genField);
        //freePosCrdShow(genPosArr, genPosAm);
    }
    return 0;
}
void randomgen(std::string whose, char genField[sz][szx])
{
    int curSh = 0;
    fieldBoarder(genField);
    freePosCrdFiller(genPosArr);
    genPosAm = 100;
    for (int i = 4; i > 0; i--)
    {
        for (int k = 0; k < 5 - i; k++)
        {
            shgen[curSh].length = i;
            if (generator(whose, curSh, genField) == -1)
            {
                return;
            }
            //testgen(genField);
            curSh++;
        }
    }
    if (whose == "player")
        randFieldIntegrator(genField, 0);
    else
        randFieldIntegrator(genField, 10);
}
void freePosCrdShow(COORD* freePosCrdArr, int freePosCrdAm)
{
    for (int i = 0; i < freePosCrdAm; i++)
    {

        std::cout << "\n List : " << freePosCrdArr[i].X << "\t" << freePosCrdArr[i].Y;

    }
}
void freePosCrdFiller(COORD* freePosCrdArr)
{
    for (int i = 0; i < sz - 2; i++)
    {
        for (int k = 0; k < szx - 2; k++)
        {
            freePosCrdArr[k + i * 10].X = k + 1;
            freePosCrdArr[k + i * 10].Y = i + 1;
        }
    }
}
int freePosCrdDeleter(int x, int y, COORD* freePosCrdArr, int freePosCrdAm)
{
    int delindex;
    for (int i = 0; i < freePosCrdAm; i++)
    {
        if (freePosCrdArr[i].X == x && freePosCrdArr[i].Y == y)
        {
            delindex = i;
            for (int k = delindex; k < freePosCrdAm; k++)
            {
                freePosCrdArr[k].X = freePosCrdArr[k + 1].X;
                freePosCrdArr[k].Y = freePosCrdArr[k + 1].Y;
            }
            return --freePosCrdAm;
        }
    }
    return freePosCrdAm;

}
