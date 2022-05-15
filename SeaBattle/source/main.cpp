#include "output.h"

std::string curdifficulty = "Easy";
short width, height, correctX = 0, correctY = 0, wins = 0, losses = 0;

int main() {
	utf.setUtfLocale();
	setConsoleFullscreen();
	Sleep(100);
	srand(time(NULL));
	setConsoleNoSelection(TRUE);
	width = getConsoleSize("width");
	height = getConsoleSize("height");
	propManager();
	mainMenu();
}