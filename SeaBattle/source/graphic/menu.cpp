#include "output.h"
#include "core.h"

void aboutgame()
{
    system("cls");
    GotoXY((width - 70) / 2+30, (height - 5) / 2 - 7, "О игре.",LIGHTCYAN,BLACK);
    GotoXY((width - 70) / 2, (height - 5) / 2-6, "      «Морской бой» — игра для двух участников, в которой игроки");
    GotoXY((width - 70) / 2, (height - 5) / 2 -5, "по очереди называют координаты на неизвестной им карте соперника.");
    GotoXY((width - 70) / 2, (height - 5) / 2 -4, "Если у соперника по этим координатам имеется корабль(координаты заняты),");
    GotoXY((width - 70) / 2, (height - 5) / 2 -3, "то корабль или его часть «топится», а попавший получает право сделать ");
    GotoXY((width - 70) / 2, (height - 5) / 2 -2, "ещё один ход. Цель игрока — первым потопить все корабли противника.");
    GotoXY((width - 70) / 2+32, (height - 5) / 2,"FAQ",LIGHTCYAN,BLACK );
    GotoXY((width - 70) / 2, (height - 5) / 2 +1, " • Как расставлять корабли? - Начать новую игру и выбрать: «Расставить вручную».");
    GotoXY((width - 70) / 2+3, (height - 5) / 2 +2, "После нажатия кнопки выбора длины нужно кликнуть ЛКМ в нужном месте на поле для установки блока корабля.");
    GotoXY((width - 70) / 2, (height - 5) / 2 +3, " • Как сохранить расстановку? - Расставить вручную , сгенерировать автоматически или загрузить из файла.");
    GotoXY((width - 70) / 2+3, (height - 5) / 2 +4, "Нажать кнопку «yes» для сохранения или «no» чтобы пропустить момент сохранения.");
    GotoXY((width - 70) / 2, (height - 5) / 2 +5, " • Как загрузить расстановку? - Начать новую игру и выбрать: «Загрузить расстановку».");
    GotoXY((width - 70) / 2+3, (height - 5) / 2+6, "Листать сохранения на «W,S», для загрузки - «Enter», для удаления - «Backspace» + «y\\n».");
    GotoXY((width - 70) / 2, (height - 5) / 2 + 7, " • Для возврата основное в меню из любого места требуется нажать «Esc».");
    GotoXY((width - 20) / 2 , (height - 5) / 2 + 9, " >> Вернуться в меню",LIGHTRED,BLACK);
    pause();

}

void mainMenu() {
    short wdh = width / 2 - 37, hgh = height / 2 - 14;
    std::string Menu[4] = { " » Создать новую игру"," » Настройки", " » О игре", " » Выйти" };
    while (true) {
        system("cls");
        writeTitle(wdh, hgh, "seabattle");
        GotoXY(wdh+24, hgh +8, "Победы: " + std::to_string(wins) + " ◂▸ Поражения: " + std::to_string(losses),BROWN,BLACK);
        COORD button = setConsoleButton(
            (width - 25) / 2, (height - 6) / 2, 25, 3, 1, 4,
            VK_LBUTTON, DARKGRAY, LIGHTCYAN, correctY, correctX, true, 1, LIGHTCYAN, BLACK, Menu, 1, BLACK
        );
        Sleep(80);
        if (button.Y == 0 || button.Y == 4) return;
        else if (button.Y == 3) aboutgame();
        else if (button.Y == 2) optionsSubMenu();
        else if (button.Y == 1) newGameSubMenu();
        Sleep(80);
    }
}

void newGameSubMenu() {
    std::string Menu[4] = { "» Расставить вручную","» Загрузить расстановку", "» Сгенерировать случайно", "» В главное меню" };
    while (true) {
        system("cls");
        writeTitle(width / 2 - 37, height / 2 - 14, "seabattle");
        GotoXY(width / 2 - 13, height / 2 - 6, "Победы: " + std::to_string(wins) + " ◂▸ Поражения: " + std::to_string(losses), BROWN, BLACK);
        COORD button = setConsoleButton(
            (width - 27) / 2, (height - 6) / 2, 27, 3, 1, 4,
            VK_LBUTTON, DARKGRAY, LIGHTCYAN, correctY, correctX, true, 1, LIGHTCYAN, BLACK, Menu, 2, BLACK
        );
        if (button.Y == 0 || button.Y == 4) return;
        else if (button.Y == 1) AI("constructor");
        else if (button.Y == 2) AI("fromfile");
        else if (button.Y == 3) AI("random");
        Sleep(80);
    }
}

void optionsSubMenu() {
    system("cls");
    while (true) {
        std::string Menu[3] = { "» Сложность: " + curdifficulty,"» Калибровка курсора","» В главное меню" };
        writeTitle(width / 2 - 36, height / 2 - 14, "options");
        COORD button = setConsoleButton(
            (width - 25) / 2, (height - 6) / 2, 27, 3, 1, 3,
            VK_LBUTTON, DARKGRAY, LIGHTCYAN, correctY, correctX, true, 1, LIGHTCYAN, BLACK, Menu, 2, BLACK
        );
        if (button.Y == 0 || button.Y == 3) {
            propManager(true);
            return;
        }
        else if (button.Y == 1) {
            if (curdifficulty == "Easy") curdifficulty = "Normal";
            else if (curdifficulty == "Normal") curdifficulty = "Hard";
            else if (curdifficulty == "Hard") curdifficulty = "Suicide";
            else if (curdifficulty == "Suicide") curdifficulty = "Easy";
        }
        else if (button.Y == 2) {
            while (true) {
                std::string Menu[2] = { "X: "+std::to_string(correctX),"Y: " + std::to_string(correctY)};
                COORD button = setConsoleButton(
                    (width+33) / 2, (height - 2) / 2, 10, 3, 1, 2,
                    VK_LBUTTON, DARKGRAY, LIGHTCYAN, correctY,correctX, true, 1, LIGHTCYAN, BLACK, Menu, 3, BLACK, VK_RBUTTON
                );
                if (button.Y == 0) {
                    cleaning((width + 31) / 2, (height - 3) / 2, 12, 10);
                    propManager(true);
                    break;
                }
                if (button.Y == 1) correctX >5 ? 0 : correctX++;
                if (button.Y == -1) correctX < -5 ? 0 : correctX--;
                if (button.Y == 2) correctY > 5 ? 0 : correctY++;
                if (button.Y == -2) correctY < -5 ? 0 : correctY--;
                Sleep(80);
            }

        }
        Sleep(80);
    }
}