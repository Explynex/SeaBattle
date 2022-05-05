#include "output.h"
#include "core.h"

//trashpack

void aboutgame()
{
    system("cls");
  //  setColor(Yellow, Black);
    GotoXY((width - 70) / 2+30, (height - 5) / 2 - 7);
    std::cout << "О игре.";
 //   setColor(White, Black);
    GotoXY((width - 70) / 2, (height - 5) / 2-6);
    std::cout << "      «Морской бой» — игра для двух участников, в которой игроки";
    GotoXY((width - 70) / 2, (height - 5) / 2 -5);
    std::cout << "по очереди называют координаты на неизвестной им карте соперника.";
    GotoXY((width - 70) / 2, (height - 5) / 2 -4);
    std::cout << "Если у соперника по этим координатам имеется корабль(координаты заняты),";
    GotoXY((width - 70) / 2, (height - 5) / 2 -3);
    std::cout << "то корабль или его часть «топится», а попавший получает право сделать ";
    GotoXY((width - 70) / 2, (height - 5) / 2 -2);
    std::cout << "ещё один ход. Цель игрока — первым потопить все корабли противника.";
    GotoXY((width - 70) / 2+32, (height - 5) / 2 );
  //  setColor(Yellow, Black);
    std::cout << "FAQ";
   // setColor(White, Black);
    GotoXY((width - 70) / 2, (height - 5) / 2 +1);
    std::cout << " • Как добавлять корабли? - Начать новую игру и выбрать: «Расставить вручную».";
    GotoXY((width - 70) / 2+3, (height - 5) / 2 +2);
    std::cout << "После нажатия кнопки 1-4 нужно ввести координаты. Пример: «1» «J2».";
    GotoXY((width - 70) / 2, (height - 5) / 2 +3);
    std::cout << " • Как сохранить расстановку? - Расставить вручную или сгенерировать автоматически.";
    GotoXY((width - 70) / 2+3, (height - 5) / 2 +4);
    std::cout << "Нажать кнопку «y» для сохранения или «n» чтобы пропустить момент сохранения.";
    GotoXY((width - 70) / 2, (height - 5) / 2 +5);
    std::cout << " • Как загрузить расстановку? - Начать новую игру и выбрать: «Загрузить расстановку».";
    GotoXY((width - 70) / 2+3, (height - 5) / 2+6);
    std::cout << "Листать сохранения на «W,S», для загрузки - «Enter», для удаления - «Del» + «y\\n».";
    GotoXY((width - 70) / 2, (height - 5) / 2 + 7);
    std::cout << " • Для возврата в меню из «Конструктора», »Загрузчика» и «Генератора расстановок» - «Esc».";
    GotoXY((width - 70) / 2, (height - 5) / 2 + 8);
    std::cout << " • Для возврата в меню во время игры стоит написать вместо координат «00» ";
  //  setColor(LightRed, Black);
    GotoXY((width - 20) / 2 , (height - 5) / 2 + 10);
    std::cout << " >> Вернуться в меню";
   //setColor(Black, Black);
    system("pause");

}

//end trashpack

void mainMenu() {
    while (true) {
        system("cls");
        short wdh = width / 2 - 37, hgh = height / 2 - 14;
        setColor(LIGHTCYAN, BLACK);
        writeTitle(wdh, hgh, "seabattle");
        std::string Menu[4] = { " » Создать новую игру"," » Настройки", " » О игре", " » Выйти" };
        COORD button = setConsoleButton(
            (width - 25) / 2, (height - 6) / 2, 25, 3, 1, 4,
            VK_LBUTTON, DARKGRAY, LIGHTCYAN, 0, true, 1, LIGHTCYAN, BLACK, Menu, 1, BLACK
        );
        Sleep(80);
        if (button.Y == 0 || button.Y == 4) return;
        else if (button.Y == 3) aboutgame();
        else if (button.Y == 1) newGameSubMenu();
        Sleep(80);
    }
}


void newGameSubMenu() {
    while (true) {
        system("cls");
        setColor(LIGHTCYAN, BLACK);
        writeTitle(width / 2 - 37, height / 2 - 14, "seabattle");
        std::string Menu[4] = { "» Расставить вручную","» Загрузить расстановку", "» Сгенерировать случайно", "» В главное меню" };
        COORD button = setConsoleButton(
            (width - 27) / 2, (height - 6) / 2, 27, 3, 1, 4,
            VK_LBUTTON, DARKGRAY, LIGHTCYAN, 0, true, 1, LIGHTCYAN, BLACK, Menu, 2, BLACK
        );
        if (button.Y == 0 || button.Y == 4) return;
        else if (button.Y == 1) AI("constructor");
        else if (button.Y == 2) AI("fromfile");
        else if (button.Y == 3) AI("random");
        Sleep(80);
    }
}