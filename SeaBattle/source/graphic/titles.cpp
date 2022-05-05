#include "output.h"

void writeTitle(short width, short height, std::string title) {
    if (title == "seabattle") {
        GotoXY(width, height++, " ██████╗███████╗ █████╗   ██████╗  █████╗ ████████╗████████╗██╗     ███████╗");
        GotoXY(width, height++, "██╔════╝██╔════╝██╔══██╗  ██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║     ██╔════╝");
        GotoXY(width, height++, "██║     ██║════╝██╔══██║  ██╔══██║██╔══██║   ██║      ██║   ██║     ██║════╝");
        GotoXY(width, height++, "╚█████╗ █████╗  ███████║  ██████╦╝███████║   ██║      ██║   ██║     █████╗  ");
        GotoXY(width, height++, " ╚═══██╗██╔══╝  ██╔══██║  ██╔══██╗██╔══██║   ██║      ██║   ██║     ██╔══╝  ");
        GotoXY(width, height++, "██████╔╝███████╗██║  ██║  ██████╦╝██║  ██║   ██║      ██║   ███████╗███████╗");
        GotoXY(width, height++, "╚═════╝ ╚══════╝╚═╝  ╚═╝  ╚═════╝ ╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚══════╝╚══════╝");
        std::cout << std::endl;
        return;
    }
    if (title == "aimove") {
        GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + 1);
        std::cout << "                    ██ ██ ████  ███                  ";
        GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + 2);
        std::cout << "                     ███  █  █  █ █                  ";
        GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + 3);
        std::cout << "                      █   █  █  █ █                  ";
        GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + 4);
        std::cout << "                     ███  █  █ █████                 ";
        GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + 5);
        std::cout << "                    ██ ██ ████ █   █                 ";
        GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + 6);
        std::cout << "                                                     ";
        GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + 7);
        std::cout << "█  █ ████ █   █ ████ █    █  ██  ███ ███ ████ ████     ";
        GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + 8);
        std::cout << "█ █  █  █ ██ ██ █  █ █    █ █  █  █  █   █  █ █  █     ";
        GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + 9);
        std::cout << "██   █  █ █ █ █ █  █ ████ ████ █  █  ███ ████ ████     ";
        GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + 10);
        std::cout << "█ █  █  █ █   █ █  █ █  █ █ █  █  █  █   █    █  █     ";
        GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + 11);
        std::cout << "█  █ ████ █   █ █  █ ████ █  ██   █  ███ █    █  █     ";
        GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + 12);
        std::cout << "                                                         ";
    }
    if (title == "playermove") {
        GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + 1);
        std::cout << "                    ██ ██ ████  ███                  ";
        GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + 2);
        std::cout << "                     ███  █  █  █ █                  ";
        GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + 3);
        std::cout << "                      █   █  █  █ █                  ";
        GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + 4);
        std::cout << "                     ███  █  █ █████                 ";
        GotoXY((width - 142) / 2 + 93, (height - 43) / 2 + 5);
        std::cout << "                    ██ ██ ████ █   █                 ";
        GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + 6);
        std::cout << "                                                     ";
        GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + 7);
        std::cout << "         █  █ ███ ████ ████ █  █ ████                         ";
        GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + 8);
        std::cout << "         █  █ █   █  █ █  █ █ █  █  █                    ";
        GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + 9);
        std::cout << "         █ ██ █   ████ █  █ ██   ████                    ";
        GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + 10);
        std::cout << "         ██ █ █   █    █  █ █ █  █  █                         ";
        GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + 11);
        std::cout << "         █  █ █   █    ████ █  █ █  █                    ";
        GotoXY((width - 142) / 2 + 98, (height - 43) / 2 + 12);
        std::cout << "                                                         ";
    }
    if (title == "aiwin") {
        GotoXY((width - 45) / 2, (height - 11) / 2 - 3);
        std::cout << "█  █ ████ █   █ ████ █    █  ██  ███ ███ ████";
        GotoXY((width - 45) / 2, (height - 11) / 2 + 1 - 3);
        std::cout << "█ █  █  █ ██ ██ █  █ █    █ █  █  █  █   █  █";
        GotoXY((width - 45) / 2, (height - 11) / 2 + 2 - 3);
        std::cout << "██   █  █ █ █ █ █  █ ████ ████ █  █  ███ ████";
        GotoXY((width - 45) / 2, (height - 11) / 2 + 3 - 3);
        std::cout << "█ █  █  █ █   █ █  █ █  █ █ █  █  █  █   █   ";
        GotoXY((width - 45) / 2, (height - 11) / 2 + 4 - 3);
        std::cout << "█  █ ████ █   █ █  █ ████ █  ██   █  ███ █   ";
        GotoXY((width - 34) / 2, (height - 11) / 2 + 6 - 3);
        std::cout << "████ ████ ████ ███  ███  █  █   ██";
        GotoXY((width - 34) / 2, (height - 11) / 2 + 7 - 3);
        std::cout << "█  █ █  █ █    █    █ █  █  █  █ █";
        GotoXY((width - 34) / 2, (height - 11) / 2 + 8 - 3);
        std::cout << "█  █ █  █ ████ ███  █ █  █ ██ █  █";
        GotoXY((width - 34) / 2, (height - 11) / 2 + 9 - 3);
        std::cout << "█  █ █  █ █  █ █   █████ ██ █ █  █";
        GotoXY((width - 34) / 2, (height - 11) / 2 + 10 - 3);
        std::cout << "█  █ ████ ████ ███ █   █ █  █ █  █";
    }
    if (title == "playerwin") {
        GotoXY((width - 34) / 2, (height - 11) / 2 - 3);
        std::cout << "      █  █ ███ ████ ████ █  █";
        GotoXY((width - 34) / 2, (height - 11) / 2 + 1 - 3);
        std::cout << "      █  █ █   █  █ █  █ █ █ ";
        GotoXY((width - 34) / 2, (height - 11) / 2 + 2 - 3);
        std::cout << "      █ ██ █   ████ █  █ ██  ";
        GotoXY((width - 34) / 2, (height - 11) / 2 + 3 - 3);
        std::cout << "      ██ █ █   █    █  █ █ █ ";
        GotoXY((width - 34) / 2, (height - 11) / 2 + 4 - 3);
        std::cout << "      █  █ █   █    ████ █  █";
        GotoXY((width - 34) / 2, (height - 11) / 2 + 6 - 3);
        std::cout << "████ ████ ████ ███  ███  █  █   ██";
        GotoXY((width - 34) / 2, (height - 11) / 2 + 7 - 3);
        std::cout << "█  █ █  █ █    █    █ █  █  █  █ █";
        GotoXY((width - 34) / 2, (height - 11) / 2 + 8 - 3);
        std::cout << "█  █ █  █ ████ ███  █ █  █ ██ █  █";
        GotoXY((width - 34) / 2, (height - 11) / 2 + 9 - 3);
        std::cout << "█  █ █  █ █  █ █   █████ ██ █ █  █";
        GotoXY((width - 34) / 2, (height - 11) / 2 + 10 - 3);
        std::cout << "█  █ ████ ████ ███ █   █ █  █ █  █";
    }
    if (title == "title")
    {
        GotoXY(width / 2 - 26, (height - 5) / 4);
        std::cout << "                                ██               ██ ";
        GotoXY(width / 2 - 26, (height - 6) / 4 + 1);
        std::cout << "█   █ ████ ████ ████ █  █ ████ █  █   ████ ████ █  █";
        GotoXY(width / 2 - 26, (height - 6) / 4 + 2);
        std::cout << "██ ██ █  █ █  █ █  █ █ █  █  █ █  █   █    █  █ █  █";
        GotoXY(width / 2 - 26, (height - 6) / 4 + 3);
        std::cout << "█ █ █ █  █ ████ █    ██   █  █ █ ██   ████ █  █ █ ██";
        GotoXY(width / 2 - 26, (height - 6) / 4 + 4);
        std::cout << "█   █ █  █ █    █  █ █ █  █  █ ██ █   █  █ █  █ ██ █";
        GotoXY(width / 2 - 26, (height - 6) / 4 + 5);
        std::cout << "█   █ ████ █    ████ █  █ ████ █  █   ████ ████ █  █";
    }
}

